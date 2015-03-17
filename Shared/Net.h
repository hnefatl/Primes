#ifndef _NET_H
#define _NET_H

#include <WinSock2.h>
#include <string>

// Returns true if the current system requires WSAStart and WSAClose to be called (windows).
extern bool WSANeeded();
// Initialises WSA.
// Returns false if WSA failed to start (fatal error).
extern bool WSAStart();
// Performs WSA cleanup.
// Returns false if WSA failed to clean up. Nothing can be done in this situation except note it happened.
extern bool WSAClose();

// Creates a new socket.
// Out: The Socket created.
// Returns false if the socket couldn't be created for any reason.
extern bool Create(SOCKET &Out);

// Binds a socket to a given port. Required before calls to listen.
// Socket: The socket to bind.
// Port: The Port to bind to.
// Returns false if the binding failed for whatever reason.
extern bool Bind(const SOCKET Socket, const unsigned short Port);

// Puts a socket into a listening state with a given backlog.
// Socket: The socket to put into a listening state.
// Backlog: The number of clients waiting for connection before the server starts actively refusing new connections.
// Returns false if listening failed.
extern bool Listen(const SOCKET Socket, const unsigned int Backlog);

// Accepts a single client. Stores additional data about the client in the extra arguments. Pointers can be NULL if data is not wanted.
// ServerSocket: The socket to accept the client from.
// Client: The socket identifying the newly accepted client.
// ClientAddress: If non-NULL, contains the printed format of the client's IP address.
// AddressIsIPV4: If non-NULL, contains whether or not the client's IP is in IPV4 format.
// ClientPort: If non-NULL, contains the port that the client is using to connect.
// Returns false if a client couldn't be accepted. Usually a fatal error.
extern bool Accept(const SOCKET ServerSocket, SOCKET &Client, std::string *const ClientAddress,
					bool *const AddressIsIPV4, unsigned short *const ClientPort);

// Connects to a server with a given address on a given port. Address must be in IPV4/IPV6 form.
// Socket: The socket to connect on.
// Address: The IP address to connect to.
// AddressIsIPV4: Specifies whether the Address is in IPV4 or IPV6 format.
// Port: Specifies what port to connect on. Default value is 0, meaning the connection will be established over any available port.
// Returns false if the connection failed. Usually result of a timeout.
extern bool Connect(const SOCKET Socket, const std::string &Address, const bool AddressIsIPV4, const unsigned short &Port = 0);

// Sends data over a socket.
// Socket: The socket to send data over.
// Data: The buffer to read data from.
// Length: The amount of bytes to send from the buffer.
// Returns false if the Send fails - normally meaning that the connection has been closed.
extern bool Send(const SOCKET Socket, const char *const Data, const unsigned int Length);
// Sends an unsigned long (guaranteed at least 32bits) over a socket.
// Socket: The socket to send the unsigned long over.
// Data: The unsigned long to send.
// Returns false if the Send fails - normally meaning that the connection has been closed.
extern bool Send(const SOCKET Socket, const unsigned long Data);
// Sends an unsigned short (guaranteed at least 16bits) over a socket.
// Socket: The socket to send the unsigned short over.
// Data: The unsigned short to send.
// Returns false if the Send fails - normally meaning that the connection has been closed.
extern bool Send(const SOCKET Socket, const unsigned short Data);
// Sends a std::string over a socket.
// Socket: The socket to send the std::string over.
// Data: The std::string to send.
// Returns false if the Send fails - normally meaning that the connection has been closed.
extern bool Send(const SOCKET Socket, const std::string &Data);

// Receives a number of bytes into a buffer.
// Socket: The socket to receive data over.
// Buffer: The buffer to store the received data in.
// Length: The number of bytes to receive.
// Returns false if the Receive fails - normally meaning that the connection has been closed.
extern bool Receive(const SOCKET Socket, char *const Buffer, const unsigned int Length);
// Receives an unsigned long.
// Socket: The socket to receive data over.
// Out: The unsigned long that was received.
// Returns false if the receive fails - normally meaning that the connection has been closed.
extern bool ReceiveUlong(const SOCKET Socket, unsigned long *const Out);
// Receives an unsigned short.
// Socket: The socket to receive data over.
// Out: The unsigned short that was received.
// Returns false if the receive fails - normally meaning that the connection has been closed.
extern bool ReceiveUshort(const SOCKET Socket, unsigned short *const Out);
// Receives a std::string.
// Socket: The socket to receive data over.
// Out: The std::string that was received.
// Returns false if the receive fails - normally meaning that the connection has been closed.
extern bool ReceiveString(const SOCKET Socket, std::string *const Out);

#endif