using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace SocketServer {
    
    class Server {
        static void Main(string[] argvs) {
            // expected to have at least 1 input
            if(argvs.Length != 1) {
                Console.WriteLine("Expect one input:\n The port number");
                return;
            }
            
            // try to convert the port into integer
            try {
                int port = int.Parse(argvs[0]);
                ExecuteServer(port);
            } catch(Exception e) {
                Console.WriteLine("Invalid port number...");
                return;
            }
        }
        
        public static void ExecuteServer(int port) {
            // get local IP address
            // IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
            // IPAddress ipAddr = ipHost.AddressList[0];
            
            // listen to all addresses
            IPAddress ipAddr = IPAddress.Parse("0.0.0.0");
            
            // create local endpoint
            IPEndPoint localEndPoint = new IPEndPoint(ipAddr, port);
            
            // create a new instance of the socket
            Socket listener = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            try {
                // bind the socket with the local endpoint and start listening
                // maximum client is set to 10
                listener.Bind(localEndPoint);
                listener.Listen(10);
                
                // define some variables that will be used in later phase
                byte[] bytes = new Byte[1024];
                string data = null;
                int numByte = 0;
                byte[] message = Encoding.ASCII.GetBytes("Goodbye in C#");
                
                while(true) {
                    // connect to a client
                    Socket clientSocket = listener.Accept();
                    
                    // receive the message send by the client and display it
                    numByte = clientSocket.Receive(bytes);
                    data = Encoding.ASCII.GetString(bytes, 0, numByte);
                    Console.WriteLine(data);
                    
                    // send message back
                    clientSocket.Send(message);
                    Console.WriteLine("Goodbye in C#");
                    
                    // close the client socket connection
                    clientSocket.Shutdown(SocketShutdown.Both);
                    clientSocket.Close();
                }
                
            } catch(Exception e) {
                Console.WriteLine("Connection error...")
                Console.WriteLine(e.ToString());
            }
        }
    }
}
