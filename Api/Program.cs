using System.Reflection;
using System.Text;
using System.Text.Json;
using System.Xml;
using Fleck;
using lib;
using Service1.Service;
using Websocket_fødselsdag_2;


var builder = WebApplication.CreateBuilder(args);

builder.Services.AddSingleton<DataService>();
DataService dataservice = new DataService();
dataservice.GemteFarver();



var clientEventHandlers = builder.FindAndInjectClientEventHandlers(Assembly.GetExecutingAssembly());

var app = builder.Build();


var server = new WebSocketServer("ws://0.0.0.0:8181");


server.Start(ws =>
{
    ws.OnOpen = () =>
    {


        //Her sendes tiltagere til frontenden ved start
        var echo = new TilføjFarve()
        {
            farver = dataservice.sendList()
        };
        var messageToClient = JsonSerializer.Serialize(echo);
        ws.Send(messageToClient);

    
        CurrentConnections.Connections.Add(ws);
    };
    ws.OnMessage = async message =>
    {
      
        try
        {
           await app.InvokeClientEventHandler(clientEventHandlers, ws, message);

        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    };
});

new MQTT(dataservice).Startup();

Console.ReadLine();





public class TilføjFarve : BaseDto
{
    public List<string> farver { get; set; }
}