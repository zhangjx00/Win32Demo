// 11-SocketServer01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"ws2_32.lib")

#include <iostream>


#include "MyTcpFun.h"



//阻塞式并发模型

int main()
{
    //初始化
    InitSocket();
    //业务处理
    MyTcpSerFun();
    //关闭webSocket链接
    WSACleanup();


}

