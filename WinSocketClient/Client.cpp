#include <iostream>
#include <winsock2.h>

using namespace std;

#define SERVPORT    5050
#define SERVIP      "127.0.0.1"
#define MAXDATASIZE 512
#pragma comment(lib,"ws2_32.lib")

int main(void)
{
    do 
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        SOCKADDR_IN addrServer;
        memset(&addrServer, 0, sizeof(SOCKADDR_IN));
        addrServer.sin_family = AF_INET;
        addrServer.sin_port = htons(SERVPORT);
        addrServer.sin_addr.s_addr = inet_addr(SERVIP);

        if (connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)) == SOCKET_ERROR)
        {
            cout<<"connet failed!"<<endl;
            break;
        }

        char szBuf[MAXDATASIZE] = {};
        int recvBytes = recv(sockClient, szBuf, MAXDATASIZE, 0);
        if (recvBytes == SOCKET_ERROR)
        {
            printf("recv failed!\n");
        }
        else
        {
            szBuf[recvBytes] = '\0';
            printf("%s\n",szBuf);
        }

        closesocket(sockClient);
        WSACleanup();
    } while (0);
    getchar();
    return 0;
}