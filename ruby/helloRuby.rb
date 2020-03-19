require 'socket'
require 'timeout'

# invalid arguments, abort
if ARGV.length < 2
    abort "Usage: helloRuby <host IP> <host port>"
end

# check if the port on the server is open
def is_port_open?(ip, port)
  begin
    Timeout::timeout(1) do
    # test with a timeout the server port
      begin
        s = TCPSocket.new(ip, port)
        s.close
        return true
      rescue Errno::ECONNREFUSED, Errno::EHOSTUNREACH
        return false
      end
    end
  rescue Timeout::Error
  end

  return false
end

hostname = ARGV[0]
port = ARGV[1]

# abort if port is not a number
if port != port.to_i.to_s
        abort "Invalid port number"
end

# abort if server isn't available
if not is_port_open? hostname, port
	abort "Server not available at " + hostname + ":" + port
end

# connect to the open server
soc = TCPSocket.new hostname, port

message = "Hello in Ruby\n"
puts "Sending: " + message
# send messages
soc.puts message

# grab server response
line = soc.gets
puts "Received: " + line
# received, now exit
soc.close
