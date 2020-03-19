#!/bin/bash

sudo apt install -y ruby-full
echo

echo "This is the version of ruby you are using:"
ruby -v
echo

echo "Ruby is located at:"
which ruby
echo

echo "Run the client with 'ruby helloRuby.rb <server IP> <port number>'"
echo "Server can be run with 'ruby hellosrvRuby.rb <port number>'"
