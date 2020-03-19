// package com.rpc.server

import java.io.{DataInputStream, DataOutputStream, ObjectInputStream}
import java.net.{ServerSocket, Socket}


object RpcServer {
  
  def main(args: Array[String]): Unit = {
    
    if(args.length != 1) {
      println("the number of arguments of args not equals 1.")
      System.exit(0)
    }
    
    //Set up the server
    
    val listener: ServerSocket = new ServerSocket(args(0).toInt)
    
    println("The server is in service.......")
    
    while (true) {
      //Set up the socket
      val socket: Socket = listener.accept()
      
      // get client ip
      val clientIp = socket.getInetAddress.getHostAddress
      println("Client ip: " + clientIp)
      
      //Set up the input and output stream
      val out = new DataOutputStream(socket.getOutputStream())
      val in =  new DataInputStream(socket.getInputStream())

    
      val buf = new Array[Byte](1024);
      val len: Int = in.read(buf)
      val message = new String(buf,0,len)
      println("Received: " + message)
      val ma: Array[String] = message.trim().split(" ")
      
      val serverLanguage = "Scala"
      val result = "Goodbye " + ma(ma.length - 1) + " from " + serverLanguage
      println("Sending：" + result)
      
      
      //Send the response back to the client
      out.write(result.getBytes("utf8"))

      out.close()
      in.close()
      socket.close()

    }

  }

}
