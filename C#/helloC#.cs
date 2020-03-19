using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace SocketClient {
    class Client {
        static void Main(string[] argvs) {
            // expected to have two input
            if(argvs.Length != 2) {
                Console.WriteLine("Invalid input, expecting two inputs:\n The IP address\n The port number");
                return;
            }
            client(argvs[0], argvs[1]);
        }
        
        static void client(string ipaddress, string port) {
            int port_int = 0;
            
            // parse the port number into integer
            try {
                port_int = int.Parse(port);
            }
            catch(Exception e) {
                Console.WriteLine("Invalid Port Number...\n");
                // Console.WriteLine(e.ToString());
                return;
            }
            
            // this parse might cause an error if input IP address is invalid
            IPAddress ip_address = null;
            IPEndPoint ServerEndPoint = null;
            try {
                ip_address = IPAddress.Parse(ipaddress);
                ServerEndPoint = new IPEndPoint(ip_address, port_int);
            } catch(FormatException e) {
                Console.WriteLine("Invalid IP address...\n");
                // Console.WriteLine(e.ToString());
                return;
            }

            // create a new instance of the socket
            Socket ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            
            try {
                // connect the client socket to the server
                ClientSocket.Connect(ServerEndPoint);
                
                // send the message
                byte[] message = Encoding.ASCII.GetBytes("Hello in C#");
                ClientSocket.Send(message);
                
                // read in the response from the server and display it
                byte[] bytes = new Byte[1024];
                int length = ClientSocket.Receive(bytes);
                string data = Encoding.ASCII.GetString(bytes, 0, length);
                Console.WriteLine(data);
                
                // shutdown and close
                ClientSocket.Shutdown(SocketShutdown.Both);
                ClientSocket.Close();
                
            } catch(Exception e) {
                Console.WriteLine("Connection error...");
                // Console.WriteLine(e.ToString());
                return;
            }
        }
    }
}