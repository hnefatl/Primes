#ifndef _NET_H
#define _NET_H

#include <WinSock2.h>
#include <string>

extern bool WSANeeded();
extern bool WSAStart();
extern bool WSAClose();

extern bool Create(SOCKET &Out);

extern bool Bind(const SOCKET Socket, const unsigned short Port);

extern bool Listen(const SOCKET Socket, const unsigned int Backlog);

extern bool Accept(const SOCKET ServerSocket, SOCKET &Client, std::string *const ClientAddress,
					bool *const AddressIsIPV4, unsigned short *const ClientPort);

extern bool Connect(const SOCKET Socket, const std::string &Address, const bool AddressIsIPV4, const unsigned short *const Port);

extern bool Send(const SOCKET Socket, const char *const Data, const unsigned int Length);
extern bool Send(const SOCKET Socket, const unsigned long Data);
extern bool Send(const SOCKET Socket, const unsigned short Data);
extern bool Send(const SOCKET Socket, const std::string &Data);

extern bool Receive(const SOCKET Socket, char *const Buffer, const unsigned int Length);
extern bool ReceiveUlong(const SOCKET Socket, unsigned long *const Out);
extern bool ReceiveUshort(const SOCKET Socket, unsigned short *const Out);
extern bool ReceiveString(const SOCKET Socket, std::string *const Out);

#endif