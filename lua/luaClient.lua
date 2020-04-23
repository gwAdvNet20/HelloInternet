--[[
-- Created on Tue Jan 21 2020:16:49:46
-- Created by Ratnadeep Bhattacharya
--]]
-- [[ function for checking error and printing line ]]
function check_print_line(line_r, err)
	if not err then
		print("\n")
		print("Received: " .. line_r)
	else
		print("Following error occurred: " .. err)
	end
end

local socket = require("socket")
local input = ...
local host, port
if input then
	host, port = arg[1], arg[2]
else
	host, port = "localhost", 8080
end

-- local host, port = "localhost", 8080

local ip = assert(socket.dns.toip(host))
local client = assert(socket.tcp())
assert(client:connect(ip, port))

if client then
	client:settimeout(10)
	print("Sending: Hello in Lua")
	assert(client:send("Hello in Lua"))
	line_r, err = client:receive("*a")
	check_print_line(line_r, err)
	client:close()
else
	print("Connection error")
	client:close()
end
