#include <iostream>

#include <Net.h>
#include <string>

int main(int argc, char *argv[])
{
	if (WSANeeded())
		if (!WSAStart())
			return -1;

	SOCKET ServerSocket;
	if (!Create(ServerSocket))
		return -2;

	if (!Bind(ServerSocket, 34652))
		return -3;

	if (!Listen(ServerSocket, 1))
		return -4;

	while (true)
	{
		SOCKET Client;
		std::string Address;
		bool IsIPV4;
		unsigned short Port;
		if (!Accept(ServerSocket, Client, &Address, &IsIPV4, &Port))
			break;

		while (true)
		{
			std::string Message;
			if (!ReceiveString(Client, &Message))
			{
				std::cout << "Client disconnected" << std::endl;
				break;
			}

			std::cout << Message << std::endl;
		}
	}

	WSAClose();

	return 0;
}