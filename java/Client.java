// We require the net and io libraries from Java. They come with all JDK installations.
import java.net.*;
import java.io.*;

public class Client {

	/**
	*	main method required in Java
	*	@param args command line arguments for program
	*/
	public static void main(String[] args) {
		
		if (args.length != 2) {
			System.out.println("ERROR: Improper argument count. Proper usage: java Client <IP Address> <Port>");
		}

		// Create the socket with the IP address and port as specified in command line arguments
		// The Socket constructor takes the IP address as a String and the port as an integer
		// The port number is converted to an integer using a built-in Integer data type method parseInt()
		// Sockets are required by the Java API to be implemented in try/catch statements
		try (Socket socket = new Socket(args[0], Integer.parseInt(args[1]))) {
			// Create a reader and writer object for the socket
			// Reader accepts messages from the server, writer sends messages to the server
			BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
			
			// Send the hello message to the server
			System.out.println("Sending \"Hello in Java\"");
			writer.println("Hello in Java");

			// Read a message from the server. BufferedReader objects, according to the Java API, require
			// try/catch statements for implementation
			try {
				// Read a message from the server into a String s
				String s = reader.readLine();
				// Print the message sent by the server to the console
				System.out.println("Received: \"" + s + "\"");
			}
			// If there is an exception in reading the message, print the exception
			catch (IOException e) {
				System.out.println("ERROR: " + e.getLocalizedMessage() + "\n");
			}
			
			// Clean up the program by closing the Socket
			socket.close();

		}
		// If there is an exception in creating the socket, print the exception
		catch (IOException ex) {
			System.out.println(ex);
		}
	
	}

}
