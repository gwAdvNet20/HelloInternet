# HelloInternet
Say Hello to a remote friend in **all the languages!**

## What to do?
Your task is to write a client and server that talk to each other over a socket connection. Each group in the class must pick a different language. If you wish to write your client and server in different languages that is also acceptable, but they must all be unique!

All of the clients and servers should be interchangeable, despite being written by different groups in different languages. We will acheive that by ensuring that they all follow the same *protocol!*

## Client Protocol
A `helloX` client is a program written in the language X that can connect to a `hellosrv` server (potentially written in a different language). When the client connects, it should send the string `Hello in X` to the server and then attempt to read in a reply. The server's response should be printed to screen and the client should exit.

The client should take the server's hostname/IP and port as command line arguments:
```
# Sample client usage:
./helloC
Sending "Hello in C"
Received: "Goodbye in Python"
```

## Server Protocol
A `hellosrvX` server is a program written in the language X that accepts incoming client requests. For each client that connects it should try to read a message, print that message to the screen, and then send the string "Goodbye in X". It should then close the client connection and get ready to accept a new client.  Keep doing this until the program is killed with `ctrl-c`.

The server should take a port number as a command line argument.

*Challenge mode:* Instead of always responding with "Goodbye in X", make the message vary based on the client's language: "Goodbye Y from X" where Y is the client's language and X is the server's language. Also, make it print the IP of each connected client.

## Files and Folders
You should create your client and server in a folder named for the language you are using (e.g., `java/`). You also must include a `README.md` file with instructions on how to build and run your programs. If any extra software (compilers/libraries) need to be installed, include those in your instructions and provide a `setup.sh` script that installs anything necessary (you can assume Ubuntu is the OS).

The `README.md` also must contain documentation about the key socket functions in the language of your choice. This does not need to be exhaustive, but should describe the basic usage and any special considerations.

See the `python/` directory for a sample. Note that the client and server here do not fully meet the specification, so you may want to create another PR to improve them!

## Getting Started
Once your group has picked a language and ensured there are no duplicates, follow these instructions:

0. Create a GitHub account
1. One group member should create a fork of this repository into their personal account. They then should set the collaboration settings so that other group members can access the forked repository.
2. Use your Cloud 9 environment to clone the repository with a command like: `git clone https://github.com/YOUR_USERNAME/HelloInternet.git`
3. It is a good practice to make code changes in a separate branch. So run `git checkout -b helloX` where `X` is the language you plan to use. Think of a branch as a separate work area in the repository that will only have your changes.
4. Figure out how to write your client and server! You can search to find socket APIs and examples in your chosen language, but be sure you understand any code you copy!
5. Write the required documentation for your client/server.
5. Commit your changes to your local branch using the `git add` and `git commit` commands. If you aren't sure how, ask for help!
6. Push your changes to the GitHub origin repository by using `git push origin helloX` (be sure to fill in your branch name)
7. Create a Pull Request using the GitHub web interface to try to merge your branch with the main HelloInternet repository.
8. Celebrate! (once your PR is merged)
