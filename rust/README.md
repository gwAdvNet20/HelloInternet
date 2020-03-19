# Hello Internet, Rust Edition!
This document describes how socket communication works in Rust.

## Team
Pat Cody (@pcodes), James Levy (@jlevy97)

## Compiling
This program requires having Rust and Cargo installed. Check out (https://rustup.rs/) for details on how to do so.
Once Rust has been installed, you can build the program with:

```
cargo build
```

## Running
Due to how Rust organizes programs, we have a single program that can act either as a client _or_ server.
To run both at the same time, use two separate terminal instances (or a terminal multiplexer like [Tmux](https://github.com/tmux/tmux)).

__Client__: 
```
cargo run -- --client --hostname <HOSTNAME> --port <PORT>
```
__Server__: 
```
cargo run -- --server --port <PORT>
```

## Rust Socket Info
### Creating a Socket
To create a socket connection, use the `TcpStream::connect` function.
This will return a `Result<Ok, Err>` type, depending on whether or not the connection is succesful.
A `Result` type is a cool feature of Rust that allows a function to either return a regular value if the function is succesful, or an error if there is a problem.
This pattern can be observed throughout our codebase, wherever you see a block for an `Ok() =>` and `Err(e) =>`.

If you succesfully connect to a server, the `connect()` function will return a stream object.
This object can be used to send and receive data.

### Communicating with a Server
Because Rust guarentees that if you have a stream object you succesfully established a connection with the server, the stream object is how you can send and receive data.
Calling `stream.write()` will send data to the server.
Caling `stream.read(buffer)` will read data into the buffer passed in. See the client function for more details.
