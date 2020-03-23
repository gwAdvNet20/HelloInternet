# helloJava 

### Contributor Information

Ethan Baron (EthanBaron14)

Catherine Meadows (catherinemeadows)

Benjamin DeVierno (bdevierno1)

### Language

Java

### Build and Run Instructions 

To connect the Java client to a server, ensure that the server is run first before running 'Client.java'. To compile 'Client.java' on command line, use command `javac Client.java`. To run, use command `java Client` while in the directory where 'Client.java' is hosted.   



### Relevant API Information

Java uses Sockets, an endpoint for communication between servers and clients, to handle connections. Each socket has an input stream and an output stream. These take the form of InputStream and OutputStream objects. The PrintWriter object is utilized to print messages sent from the server to an output stream [`writer.println()`]. The BufferedReader object is used to read text from an output stream [`reader.readLine()`]. 




**Sources**

[PrintWriter JavaDocs](https://docs.oracle.com/javase/7/docs/api/java/io/PrintWriter.html)

[Socket JavaDocs](https://docs.oracle.com/javase/7/docs/api/java/net/Socket.html)

[BufferedReader JavaDocs](https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/io/BufferedReader.html) 



