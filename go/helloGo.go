package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Println("Please provide the Host and Port to connect to!!!!!!")
		os.Exit(1)
	}
	host := os.Args[1]
	port := os.Args[2]

	// create connection
	conn, err := net.Dial("tcp", host+":"+port)
	if err != nil {
		log.Fatal(err.Error())
	}
	handle(conn)
}

func handle(conn net.Conn) {
	fmt.Println("Sending: Hello in Go")
	fmt.Fprintf(conn, "Hello in Go\n")

	// waiting for message
	message, _ := bufio.NewReader(conn).ReadString('\n')
	fmt.Print("Recieved: " + message)
	conn.Close()
}
