// 10-SocketClient01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")


using std::cin;
using std::cout;
using std::endl;

#define nSerPort 10080
#define nBufMaxSize 1024


void debugLog(char* logStr) {
    cout << logStr << WSAGetLastError() << endl;

}

BOOL InitSocket() {


    WSADATA wsaData;
    SOCKET hServer;
    WORD wVerSion = MAKEWORD(2, 2);
    if (WSAStartup(wVerSion, &wsaData)) {
        //如果启动失败
        debugLog((char*)"initSocket->WSAStartup error");
        return FALSE;
    };

    return TRUE;


}


//关闭一个链接
BOOL CloseConnect(SOCKET sd) {

    //首先发送一个TCP FIN分段，向对方表明已经完成数据发送
    if (shutdown(sd, SD_SEND) == SOCKET_ERROR) {

        debugLog((char*)"CloseConnect - > ShutDown error");
        return FALSE;
    }
    char buf[nBufMaxSize];
    int nRetByte;

    do {
        nRetByte = recv(sd, buf, nBufMaxSize, 0);
        if (nRetByte == SOCKET_ERROR) {
            debugLog((char*)"closeconnect -> recv error");
            break;
        }
        else if (nRetByte > 0) {

            debugLog((char*)"closeconnect 错误的接收数据");
            break;
        }

    } while (nRetByte != 0);

    if (closesocket(sd) == SOCKET_ERROR) {
        debugLog((char*)"closeconnect -> closesocket error");
        return FALSE;
    }
    return TRUE;
}


SOCKET ConnectSocket() {

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN clientsock_in;
    clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    clientsock_in.sin_family = AF_INET;
    clientsock_in.sin_port = htons(10080);
    connect(clientSocket, (SOCKADDR*)&clientsock_in, sizeof(SOCKADDR));//开始连接

    return clientSocket;
}

int main()
{
    //
    //InitSocket();

    //1.建立流式套接字
    InitSocket();
    //2.建立连接
    SOCKET clientSocket = ConnectSocket();

    char receiveBuf[100];
    while (true) {

        printf("Send:%s\n", "hello world ");
        send(clientSocket, "hello world", strlen("hello world") + 1, 0);

        recv(clientSocket, receiveBuf, 101, 0);
        printf("Recv:%s\n", receiveBuf);

        Sleep(2000);
    }


    send(clientSocket, "hello world 2", strlen("hello world 2") + 1, 0);
    recv(clientSocket, receiveBuf, 101, 0);
    printf("Recv:%s\n", receiveBuf);

    CloseConnect(clientSocket);


    getchar();

    return 0;
}
