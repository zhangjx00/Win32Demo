#pragma once


#include <WinSock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

using std::cin;
using std::cout;
using std::endl;

#define nSerPort 10080
#define nBufMaxSize 1024

BOOL InitSocket();
void MyTcpSerFun();