package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Please provide a port to listen on!!!")
		os.Exit(1)
	}
	port := os.Args[1]
	l, err := net.Listen("tcp", ":"+port)
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}
	fmt.Println("Starting Go helloSer on port " + port)
	for i := 0; ; i++ {
		// Server start to wait for connections
		conn, err := l.Accept()
		if err != nil {
			log.Fatal("Error accepting: ", err.Error())
		}
		// handle a new connection
		go handle(conn)
	}
}

func handle(conn net.Conn) {
	// waiting for upcoming message
	message, err := bufio.NewReader(conn).ReadString('\n')
	if err != nil {
		conn.Close()
		os.Exit(0)
	}
	fmt.Print("Recieved: " + message)

	reply := "GoodBye " + strings.Fields(message)[2] + " from Go\n"
	fmt.Println("Sending: " + reply)

	// send message
	fmt.Fprintf(conn, reply)
	conn.Close()
}
