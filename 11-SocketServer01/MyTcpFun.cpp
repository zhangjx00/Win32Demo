#include "MyTcpFun.h"

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

//先创建socket，绑定本地地址，然后开始监听
SOCKET BindListen(int nBackLog) {

    //流式套接字SOCK_STREAM，  TCP协议 IPPROTO_TCP
    SOCKET hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (hServer == INVALID_SOCKET) {

        debugLog((char*)"bind listen->socket error");
        return INVALID_SOCKET;
    }

    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(10080);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    //绑定
    int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
    if (nRet == SOCKET_ERROR) {
        debugLog((char*)"socket 绑定失败");
        closesocket(hServer);
        return INVALID_SOCKET;
    }

    //在socket上进行监听
    if (listen(hServer, 10) == SOCKET_ERROR) {
        closesocket(hServer);
        WSACleanup();
        debugLog((char*)"listen错误");
        return INVALID_SOCKET;
    }

}

SOCKET AcceptConnetion(SOCKET hSocket) {

    sockaddr_in saConnAddr;
    int nSize = sizeof(saConnAddr);

    SOCKET sd = accept(hSocket, (LPSOCKADDR)&saConnAddr, &nSize);
    if (sd == INVALID_SOCKET) {
        debugLog((char*)"AcceptConnetion 错误");
        return INVALID_SOCKET;
    }


    return sd;
}


//线程处理业务逻辑
DWORD WINAPI ClientThreadFun(LPVOID lpParam) {

    SOCKET sd = (SOCKET)lpParam;
    //客户端处理
    if (ClientConFun(sd) == FALSE) {
        //break;
    }

    //关闭一个客户端连接
    if (CloseConnect(sd) == FALSE) {
        //break;
    }
    return 0;

};

BOOL ClientConFun(SOCKET sd) {


    char buf[nBufMaxSize];
    int nRetByte;
    //接收来自客户端的数据
    do {
        nRetByte = recv(sd, buf, nBufMaxSize, 0);
        if (nRetByte == SOCKET_ERROR) {
            debugLog((char*)"AcceptConnetion 错误");
            return FALSE;
        }
        else if (nRetByte != 0) {

            buf[nRetByte] = 0;
            cout << "接收到一条数据" << buf << endl;
            int nSend = 0;
            while (nSend < nRetByte) {

                int nTemp = send(sd, &buf[nSend], nRetByte - nSend, 0);
                if (nTemp > 0) {
                    nSend += nTemp;
                }
                else if (nTemp == SOCKET_ERROR) {
                    debugLog((char*)"ClientConFun -> send 错误");
                    return FALSE;
                }
                else
                {
                    //send返回0，由于此时send < nRetByte，也就是数据还没发送出去，表示客户端被意外被关闭了
                    debugLog((char*)"ClientConFun -> send -> close 错误");
                    return FALSE;
                }
            }
        }
    } while (nRetByte != 0);

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

void MyTcpServeFun() {

    SOCKET hSocket = BindListen(1);
    if (hSocket == INVALID_SOCKET) {
        debugLog((char*)"MyTcpSerFun -> bindListen error");
        return;
    }
    while (true) {

        SOCKET sd = AcceptConnetion(hSocket);
        if (sd == INVALID_SOCKET) {
            debugLog((char*)"MyTcpSerFun -> acceptconnect error");
            break;
        }

        //当接收的客户端的连接请求，我们为他开一个线程
        DWORD dwThreadId;
        HANDLE hThread = CreateThread(0,0, ClientThreadFun,(LPVOID)sd, 0, &dwThreadId);
        if (hThread) {
            CloseHandle(hThread);
        }

        ////客户端处理
        //if (ClientConFun(sd) == FALSE) {
        //    //break;
        //}

        ////关闭一个客户端连接
        //if (CloseConnect(sd) == FALSE) {
        //    //break;
        //}

    }

    if (closesocket(hSocket) == SOCKET_ERROR) {
        debugLog((char*)"mytcpSerFun --> closesocket");
        return;
    }
}