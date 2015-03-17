#include <iostream>

#include <Net.h>
#include <string>

int main(int argc, char *argv[])
{
	if (WSANeeded())
		if (!WSAStart())
			return -1;






	if (WSANeeded())
		if (!WSAClose())
			return -1;

	return 0;
}