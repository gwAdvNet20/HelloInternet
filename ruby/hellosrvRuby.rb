require 'socket'                 # Get sockets from stdlib

if ARGV.length < 1
	abort "Usage: ruby hellosrvRuby.rb <port number>"
end

port = ARGV[0]
# check if port is a number
if port != port.to_i.to_s
        abort "Invalid port number"
end

# open at the command line argument
server = TCPServer.open(port)
# Servers run forever
loop {
	# Wait for a client to connect
        client = server.accept

        # grab data from the client (method unpacking similar to python)
	sock_domain, remote_port, remote_hostname, remote_ip = client.peeraddr
        data = client.gets
	puts "Connection from " + remote_ip
	if not data
		puts "No data from client"
		next
	end

        puts data
        client.puts "Goodbye " + data.split.last + " from Ruby"

        # Disconnect from the client
        client.close
}
