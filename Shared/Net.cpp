#include "Net.h"

#include <WS2tcpip.h>

bool WSANeeded()
{
#ifdef linux
	return false;
#endif
#ifdef _WIN32
	return true;
#endif
}

bool WSAStart()
{
	WSAData Data;
	return WSAStartup(MAKEWORD(2, 2), &Data) == 0;
}
bool WSAClose()
{
	return WSACleanup() == 0;
}

bool Create(SOCKET &Out)
{
	Out = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Out == -1)
		return false;

	return true;
}

bool Bind(const SOCKET Socket, const unsigned short Port)
{
	sockaddr_in Local;
	Local.sin_family = AF_INET;

#ifdef _WIN32
	Local.sin_addr.S_un.S_addr = INADDR_ANY;
#endif
#ifdef linux
	Local.sin_addr.s_addr = INADDR_ANY;
#endif

	Local.sin_port = htons(Port);

	return bind(Socket, (sockaddr*)&Local, sizeof(Local)) == 0;
}

bool Listen(const SOCKET Socket, const unsigned int Backlog)
{
	return listen(Socket, Backlog) == 0;
}

bool Accept(const SOCKET ServerSocket, SOCKET &Client, std::string *const ClientAddress,
	bool *const AddressIsIPV4, unsigned short *const ClientPort)
{
	sockaddr_in Address;
	int AddressSize = sizeof(Address);
	Client = accept(ServerSocket, (sockaddr *)&Address, &AddressSize);
	if (Client < 0)
		return false;

	if (AddressIsIPV4 != NULL)
	{
		*AddressIsIPV4 = Address.sin_family == AF_INET;
	}
	if (ClientAddress != NULL)
	{
		char Buffer[INET6_ADDRSTRLEN];
		*ClientAddress = std::string(inet_ntop(Address.sin_family, &Address.sin_addr, Buffer, sizeof(Buffer)));
	}
	if (ClientPort != NULL)
	{
		*ClientPort = ntohs(Address.sin_port);
	}

	return true;
}

bool Connect(const SOCKET Socket, const std::string &Address, const bool AddressIsIPV4, const unsigned short &Port)
{
	sockaddr_in Target;
	Target.sin_port = htons(Port);
	Target.sin_family = AddressIsIPV4 ? AF_INET : AF_INET6;

	if (inet_pton(Target.sin_family, Address.c_str(), &Target.sin_addr) < 0)
		return false;

	return connect(Socket, (sockaddr *)&Target, sizeof(Target)) == 0;
}

bool Send(const SOCKET Socket, const char *const Data, const unsigned int Length)
{
	unsigned int Sent = 0;

	while (Sent != Length)
	{
		int Status = send(Socket, Data + Sent, Length - Sent, NULL);
		if (Status < 0)
			return false;
		Sent += Status;
	}

	return true;
}
bool Send(const SOCKET Socket, const unsigned long Data)
{
	unsigned long Network = htonl(Data);
	return Send(Socket, (const char *)&Data, sizeof(unsigned long));
}
bool Send(const SOCKET Socket, const unsigned short Data)
{
	unsigned short Network = htons(Data);
	return Send(Socket, (const char *)&Data, sizeof(unsigned short));
}
bool Send(const SOCKET Socket, const std::string &Data)
{
	if (!Send(Socket, (unsigned long)Data.size()))
		return false;

	return Send(Socket, Data.c_str(), Data.size());
}

bool Receive(const SOCKET Socket, char *const Buffer, const unsigned int Length)
{
	unsigned int Received = 0;

	while (Received != Length)
	{
		int Status = recv(Socket, &Buffer[Received], Length - Received, NULL);
		if (Status < 0)
			return false;
		Received += Status;
	}

	return true;
}
bool ReceiveUlong(const SOCKET Socket, unsigned long *const Out)
{
	bool Result = Receive(Socket, (char* const)Out, sizeof(unsigned long));
	*Out = ntohl(*Out);
	return Result;
}
bool ReceiveUshort(const SOCKET Socket, unsigned short *const Out)
{
	bool Result = Receive(Socket, (char* const)Out, sizeof(unsigned short));
	*Out = ntohs(*Out);
	return Result;
}
bool ReceiveString(const SOCKET Socket, std::string *const Out)
{
	unsigned long Size;
	if (!ReceiveUlong(Socket, &Size))
		return false;

	Out->resize(Size);

	return Receive(Socket, (char *const)&(*Out)[0], Size);
}