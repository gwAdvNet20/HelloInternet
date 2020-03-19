
import java.io.{IOException,PrintWriter, InputStreamReader, BufferedReader}

import java.net.{InetAddress, Socket}


object helloScala {
    def main (args: Array[String]) : Unit = {
        if (args.length != 2) {
            println("Error arguments, scala Client.scala <IP address> <Port>")

        }
        
        //Get the server's IP from the command line
        val ia: InetAddress = InetAddress.getByName(args(0))
        
        //set up the socket, set up inputStream and outputStream
        //PrintWriter prints formatted representations of objects to a text-output stream, and flushes automatically
        try {
            val socket: Socket = new Socket(ia,args(1).toInt)
            val reader: BufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()))
            val writer: PrintWriter = new PrintWriter(socket.getOutputStream(), true)

            println("Sending Hello in Scala")
            writer.println("Hello in Scala")
            
            //Receive the message from inputStream
            try {
                val str: String = reader.readLine();
                println("Received " + str) 

            }

            catch {
                case e: IOException => println("ERROR: " + e)
            }

            socket.close()

        }

        catch {
            case ioe: IOException => println("Error: Had an IOException")
        }
    }
}