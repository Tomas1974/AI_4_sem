   using System.Text;
   using System.Text.Json;
   using lib;
   using MQTTnet;
        using MQTTnet.Client;
        using MQTTnet.Client.Options;
   using Service1.Service;

   namespace Websocket;

public class MQTT ()
{
    public static IMqttClient? mqttClient;
    public static IMqttClientOptions? options;
    
    public async void Startup()
    {
        await connectToBroker();
        await getConnectionToesb_temp();
        await sendMessageToFrontend();
        await closeConnection();
    }


    /**********  Forbindels til broker  **********/
    public async Task connectToBroker()
    {


        string server = "mqtt.flespi.io";
        int port = 1883;

        string user = new(Environment.GetEnvironmentVariable("mqtt_user"));
        string password = "";

       options = new MqttClientOptionsBuilder()
            .WithTcpServer(server, port)
            .WithCredentials(user, password)
            .WithClientId(Guid.NewGuid().ToString())
            .WithCleanSession()
            .Build();

        var factory = new MqttFactory();
        mqttClient = factory.CreateMqttClient();

    }

/**********  Her laves et abonnement på info fra esb/temp  **********/
    public async Task getConnectionToesb_temp()
    {
       
        mqttClient.UseConnectedHandler(async e =>
        {
            await mqttClient.SubscribeAsync(new MqttTopicFilterBuilder().WithTopic("esp/temp").Build());
            Console.WriteLine("Subscribed to esp/temp topic.");
            //Her tilføjes adgang til esp/temp

        });

    }
    
    /**********  Her sendes temperaturne til frontend og skrives i konsolen **********/
    public async Task sendMessageToFrontend()
    {

        mqttClient.UseApplicationMessageReceivedHandler(e =>
        {
            var msg = Encoding.UTF8.GetString(e.ApplicationMessage.Payload);
            Console.WriteLine($"Received message: {msg}");


            var resp = new ServerSendsIOTDataToClients()
            {
                data = msg
            };
            CurrentConnections.Connections.ForEach(e => { e.Send(JsonSerializer.Serialize(resp)); });


        });

    }
    
    public async Task closeConnection()
    {


    /**********  Her er er disconnection til broker   **********/
        
        mqttClient.UseDisconnectedHandler(async e =>
        {
            Console.WriteLine("Disconnected from MQTT broker.");
            await Task.Delay(TimeSpan.FromSeconds(5));
            //Her afbrydes forbindelsen til broker
    
    
            try
            {
                await mqttClient.ConnectAsync(options, CancellationToken.None);
            }
            catch
            {
                Console.WriteLine("Reconnection failed.");
            }
        });

        await mqttClient.ConnectAsync(options, CancellationToken.None);
        
        Console.WriteLine("Press any key to exit.");
        Console.ReadKey();
        
        await mqttClient.DisconnectAsync();

//Her afbrydes forbindelsen
    }

    public async Task sendMessageToBroker()
    {
        {
            // Send a message to the esp/return topic
            var message = new MqttApplicationMessageBuilder()
                .WithTopic("esp/return")
                .WithPayload("Start_Stop")
                .WithQualityOfServiceLevel(MQTTnet.Protocol.MqttQualityOfServiceLevel.AtLeastOnce)
                .Build();

            await mqttClient.PublishAsync(message, CancellationToken.None);
            
        }
    }
    
}

   public class ServerSendsIOTDataToClients : BaseDto
   {
       public string data { get; set; }
   }