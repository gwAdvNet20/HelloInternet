/*
Code modified from https://riptutorial.com/rust/example/4404/a-simple-tcp-client-and-server-application--echo
*/

use std::thread;
use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use std::str::{from_utf8};
use structopt::StructOpt;

// The Opt struct serves as the command-line argument mapping. Research rust macros and structopt
// for more details

#[derive(Debug, StructOpt)]
#[structopt(name = "Hello Internet- Rust", about = "This serves as both the Rust client and server for Hello Internet.")]
struct Opt {
    #[structopt(long, required_unless("server"))]
    client: bool,

    #[structopt(long, required_unless("client"))]
    server: bool, 

    #[structopt(long, required_unless("server"))]
    hostname: Option<String>,

    #[structopt(long, required(true))]   
    port: String,
}

fn handle_client(mut stream: TcpStream) {
    let response = "Goodbye in Rust!";
    let mut data = [0 as u8; 50];
    let size = stream.read(&mut data).unwrap();
    println!("Received from client: {}", from_utf8(&data[0..size]).unwrap());
    stream.write(response.as_bytes()).unwrap();
}

fn server(port: &str) {
    let server_string = format!("0.0.0.0:{}", port);
    let listener = TcpListener::bind(server_string).unwrap();

    println!("Server listening on port {}", port);
    
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                println!("New Connection: {}", stream.peer_addr().unwrap());

                // Create a new thread to handle new connection
                thread::spawn(move || {
                    handle_client(stream)
                });
            }
            Err(e) => {
                println!("Error: {}", e);
            }
        }
    }
    
    drop(listener);
}

fn client(port: &str, hostname: &str){
    let client_string = format!("{}:{}", hostname, port);

    // Match statement means either connection will succeed (and send data) or will fail to connect
    match TcpStream::connect(client_string) {
        Ok(mut stream) => {
            println!("Sending \"Hello in Rust!\"");

            let msg = b"Hello in Rust!";

            stream.write(msg).unwrap();

            let mut data = [0 as u8; 50]; // using 50 byte buffer
            match stream.read(&mut data) {
                Ok(size) => {
                    let text = from_utf8(&data[0..size]).unwrap();
                    println!("Received: {}", text);
                },
                Err(e) => {
                    println!("Failed to receive data: {}", e);
                }
            }
        },
        Err(e) => {
            println!("Failed to connect: {}", e);
        }
    }
    println!("Terminated.");
}

fn main() {
    // get commandline args
    let opt = Opt::from_args();

    if opt.server {
        server(&opt.port);
    } else {
        client(&opt.port, &opt.hostname.unwrap());
    }
}
