// 12-SockerServerNoBlock.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"ws2_32.lib")

#include <iostream>


//#include "MyTcpFun.h"

#define BUF_MAXSIZE 255

//阻塞式并发模型

int main()
{


    WSADATA wsaData;
    SOCKET hServer;
    WORD wVerSion = MAKEWORD(2,2);
    if (WSAStartup(wVerSion, &wsaData)) {
        //如果启动失败
        printf("WSAStartup\n");
        return 0;
    };

    //流式套接字SOCK_STREAM，  TCP协议 IPPROTO_TCP
    hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (hServer == INVALID_SOCKET) {
        printf("socket失败");
        return 0;
    }

    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(10080);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    //绑定
    int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
    if (nRet == SOCKET_ERROR) {
        printf("socket 绑定失败");
        return 0;
    }

    printf("socket server\n");



    //在socket上进行监听
    nRet = listen(hServer, 10);
    if (nRet == SOCKET_ERROR) {
        printf("listen错误");
        closesocket(hServer);
        WSACleanup();
        return 0;
    }
    printf("socket server2\n");


    int iMode = 1;
    nRet = ioctlsocket(hServer, FIONBIO, (u_long FAR*)&iMode);




    SOCKET hClient;
    sockaddr_in saClient;
    int nSaClientSize = sizeof(saClient);

    while (true) {
        //因为是非阻塞式，所以会直接返回
        hClient = accept(hServer, (sockaddr*)&saClient, &nSaClientSize);
        if (hClient == INVALID_SOCKET) {

            int nErrorCode = WSAGetLastError();
            if (nErrorCode == WSAEWOULDBLOCK) {
            
                Sleep(100);
                continue;
            }
            else
            {
                printf("accept 错误\n");
                closesocket(hServer);
                WSACleanup();
                return -1;
            }
        }
        break;
    }

    char szBuf[BUF_MAXSIZE];
    //循环接收客户端数据
    while (true) {
        memset(szBuf, 0, BUF_MAXSIZE);
        nRet = recv(hClient, szBuf, BUF_MAXSIZE, 0);
        if (nRet == SOCKET_ERROR) {


            int nErrorCode = WSAGetLastError();
            //接收数据缓冲区暂无数据
            if (nErrorCode == WSAEWOULDBLOCK) {
                Sleep(100);
                continue;
            }
            else if ( nErrorCode == WSAETIMEDOUT || nErrorCode == WSAENETDOWN) {
            //超时和网络中断
                printf("recv error\n");
                closesocket(hClient);
                WSACleanup();
                return -1;
            }
        }

        char tempChar[0x200];
        sprintf(tempChar,"IP:%s,接收到的消息：%s", inet_ntoa(saClient.sin_addr),szBuf);
        printf(tempChar);

        //接收到客户端的消息就退出
        if (strcmp(szBuf,"close") == 0) {
        
            nRet = send(hClient, "close", strlen("close"),0);
            break;
        }
        else {
            sprintf(tempChar, "已经接收到的消息：%s",  szBuf);
            nRet = send(hClient, tempChar, strlen(tempChar),0);
            int nErrorCode = WSAGetLastError();
            //无法立即完成阻塞套接字上的操作
            if (nErrorCode == WSAEWOULDBLOCK) {
                Sleep(100);
                continue;
            }
            else {
                printf("send error\n");
                closesocket(hClient);
                WSACleanup();
                return -1;
            }
        }
        break;
    }

    //释放资源
    closesocket(hServer);
    closesocket(hServer);
    WSACleanup();

    return 0;




}

