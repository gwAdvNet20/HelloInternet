# Readme for the LUA code

## Team Members

Ratnadeep Bhattacharya
Dennis Afanasev

## Prerequisite

```bash
sudo apt install lua5.1
sudo apt install luarocks
sudo luarocks install luasocket
```

## Branches

- `helloLua` for the advanced client and server
- `simplerLua` for the one the works with the class server

## Running the client

```lua
lua luaClient.lua
```

## Lua Socket API

It requires the `socket` library

```lua
local socket = require("socket")
```

### Creating a TCP socket and binding to a port

```lua
server = assert(socket.tcp())
server:bind("*", 8080)
```

### Setting options

```lua
server:setoption("keepalive", true)
```

### Listen for incoming connections, 10 at a time

```lua
local status, errorMessage = server:listen(10)
```

### Connecting to server

```lua
assert(client:connect(ip, port))
```

### Accept connections from client

```lua
local client = server:accept()
client:settimeout(10) -- set connection timeout to 10s
```

### Receive data

```lua
line, err = client:receive()
```

### Send data

```lua
client:send(line .. "\n")
client:send("Goodbye from Lua\n")
```

### Close client connection

```lua
client:close()
```