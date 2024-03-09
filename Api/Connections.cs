using Fleck;

namespace Websocket;

public static class CurrentConnections
{
    public static List<IWebSocketConnection> Connections = new List<IWebSocketConnection>();

}