--[[
-- Created on Tue Jan 21 2020:16:46:45
-- Created by Ratnadeep Bhattacharya
--]]
local socket = require("socket") -- master

server = assert(socket.tcp()) -- create tcp socket
server:bind("*", 8080) -- bind to localhost on port 8080

server:setoption("keepalive", true) -- connection is keepalive

local ip, port = server:getsockname()

local status, errorMessage = server:listen(10) -- listen from incoming connections

-- [[ check if successfully listening ]]
if status == 1 then
	print("Server is launched successfully on port " .. port)
else
	print("Server listen failed, error message is " .. errorMessage)
	return
end

-- [[ run server in infinite loop - hit Ctrl+C twice to cancel ]]
while 1 do
	local client = server:accept() -- accept incoming connection
	client:settimeout(10) -- set connection timeout to 10s
	local client_ip, client_port = client:getsockname() -- get client ip and port
	print("Received a new client request from " .. client_ip .. ":" .. client_port .. "\n")
	print("Send 'done' to terminate connection\n")
	line = "" -- declare empty line
	while line ~= "done" do -- run loop to get data from client
		line, err = client:receive() -- returns data from client in line or nil and an error msg
		if not err and line ~= "done" then -- client terminates by sending done
			print(line .. "\n")
			client:send(line .. "\n")
		elseif line == "done" then
			client:send("Goodbye from Lua\n")
		else -- notify of error
			print("Following error occurred: " .. err)
		end
	end
	client:close()
end
