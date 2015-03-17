#include <iostream>

#include <Net.h>
#include <string>

int main(int argc, char *argv[])
{
	if (WSANeeded())
		if (!WSAStart())
			return -1;
	
	while (true)
	{
		std::string Address;
		std::cout << "Enter address: ";
		std::getline(std::cin, Address);

		SOCKET Client;
		if (!Create(Client) || !Connect(Client, Address, true, 34652))
		{
			std::cout << "Failed to connect." << std::endl;
			continue;
		}

		while (true)
		{
			std::string Message;
			std::cout << "Enter message: ";
			std::getline(std::cin, Message);

			if (!Send(Client, Message))
			{
				std::cout << "Server disconnected" << std::endl;
				break;
			}
		}
	}


	return 0;
}