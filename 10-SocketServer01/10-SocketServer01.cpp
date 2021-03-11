// 10-SocketServer01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"ws2_32.lib")

#include <iostream>


#include "MyTcpFun.h"


//阻塞式模型



int main()
{
    //初始化
    InitSocket();
    //业务处理
    MyTcpServeFun();
    //关闭webSocket链接
    WSACleanup();



    //WSADATA wsaData;
    //SOCKET hServer;
    //WORD wVerSion = MAKEWORD(2,2);
    //if (WSAStartup(wVerSion, &wsaData)) {
    //    //如果启动失败
    //    printf("WSAStartup\n");
    //    return 0;
    //};

    ////流式套接字SOCK_STREAM，  TCP协议 IPPROTO_TCP
    //hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //if (hServer == INVALID_SOCKET) {
    //    printf("socket失败");
    //    return 0;
    //}

    //sockaddr_in addrServer;
    //addrServer.sin_family = AF_INET;
    //addrServer.sin_port = htons(10080);
    //addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    ////绑定
    //int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
    //if (nRet == SOCKET_ERROR) {
    //    printf("socket 绑定失败");
    //    return 0;
    //}

    //printf("socket server\n");



    ////在socket上进行监听
    //nRet = listen(hServer, 10);
    //if (nRet == SOCKET_ERROR) {
    //    printf("listen错误");
    //    closesocket(hServer);
    //    WSACleanup();
    //    return 0;
    //}
    //printf("socket server2\n");

    //SOCKET hClient;
    //sockaddr_in addrClient;
    //int nLen = sizeof(addrClient);

    //hClient = accept(hServer, (sockaddr *)&addrClient, &nLen);
    //if (hClient == INVALID_SOCKET) {
    //    printf("accept 错误\n");
    //    closesocket(hServer);
    //    WSACleanup();
    //    return 0;
    //}

    //printf("socket server3\n");

    //char szBuf[255];
    ////循环接收客户端数据
    //while (TRUE) {
    //    memset(szBuf, 0, BUF_SIZE);
    //    nRet = recv(hClient, szBuf, BUF_SIZE, 0);
    //    if (nRet == SOCKET_ERROR) {
    //        printf("recv 错误\n");
    //        closesocket(hServer);
    //        WSACleanup();
    //        return 0;
    //    }

    //    char sPrintBuf[BUF_SIZE];
    //    sprintf(sPrintBuf,"IP:%s,接收到的消息：%s", inet_ntoa(addrClient.sin_addr),szBuf);
    //    printf(sPrintBuf);

    //    //发送给客户端消息
    //    if (strcmp(szBuf,"close") == 0) {
    //    
    //        nRet = send(hClient, "close", strlen("close"),0);
    //        break;
    //    }
    //    else {
    //        sprintf(sPrintBuf, "已经接收到的消息：%s",  szBuf);
    //        nRet = send(hClient, sPrintBuf, strlen(sPrintBuf),0);
    //        if (SOCKET_ERROR == nRet) {
    //        
    //            printf("send 出错\n");
    //            closesocket(hServer);
    //            closesocket(hServer);
    //            WSACleanup();
    //            return 0;
    //        }
    //    }
    //}

    ////释放资源
    //closesocket(hServer);
    //closesocket(hServer);
    //WSACleanup();

    //return 0;



    ////监听



    ////in_addr addr;
    ////addr.s_addr = inet_addr("127.0.0.1");
    ////char* lpszIp = inet_ntoa(addr);

    //printf("Hello World\n");
    //return 0;

}
