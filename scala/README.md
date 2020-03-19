### Team member:
Weizhao Li & Zhuolun Gao

### Update

Fixed by Weizhao Li:
+ Follows correct protocol and makes scala client work with official server
+ Prints useful error if server is unavailable
+ Folder is correctly named after language
+ File names follow HelloLanguage spec

Fixed by Zhuolun Gao:
+ Follows correct protocol and makes scala server work with official client
+ Folder is correctly named after language
+ File names follow HelloLanguage spec

### Dependencies:
+ Java JDK
+ scala

### Install dependencies
Step 1:
By default, AWS cloud 9 alrealdy has JAVA JDK, if your environment doesn't have one.
Follow this document below to install the JAVA JDK,

https://docs.aws.amazon.com/cloud9/latest/user-guide/sample-java.html#sample-java-install

Step 2:
Run the setup.sh to install the scala on Ubuntu environment.


### Socket API explanation

Since scala mostly uses JAVA API, most of the API is the same as JAVA.

##### Setup the socket

we can use Socket(InetAddress address, int port) to setup the socket. 
Also, we can setup the socket for the server by using ServerSocket(int port)

##### Sending and Receiving

Utilize input and output stream 
Use DataOutputStream(socket.getOutputStream) to setup output stream, use DataInputStream(socket.getInputStream) to setup input stream.

Use flush() to send the message. Use readUTF() to receive the message.

##### Close

Use close() to close the input and output stream, use close() to close the socket.



### Test Case
#### Test case 1:

Run scala server with scala client, follow the instruction below.

Step A:
Run the server with port number:

```bash
scala hellosrvScala.scala 8080
```

Step B:

On AWS cloud9, click + button, open a new terminal. Run the client with the server's hostname/IP and port like this:

```bash
scala helloScala.scala localhost 8080
```

Result
The client would send "Hello in Scala", once the server receives the message, the server would send back "Goodbye in scala"


#### Test case 2:
Run helloScala client with official python server.

helloScala is the new version of the client that we fixed. Now, this client enables to work with official server, print the error
if server is unavailable, prit error on invalid arguments.

Follow this command to connect with official python server.

Start the python server:

```bash
python hellosrvPython.py
```

Start the scala client:

```bash
scala helloScala.scala localhost 8080
```

Result:
Now you can see the communication results.

#### Test case 3:
Run helloScala server with official python client.

hellosrvScala is the new fixed version of server. Now, it enables to work with official client.

Follow this command to connect with official python client.

Start the scala server: 

```bash
scala hellosrvScala.scala 8080
```

Start the python client:
```bash
python helloPython.py
```

Result:
Now you can see the communication results.
