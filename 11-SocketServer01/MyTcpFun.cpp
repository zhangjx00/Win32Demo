#include "MyTcpFun.h"

void debugLog(char* logStr) {
    cout << logStr << WSAGetLastError() << endl;

}

BOOL InitSocket() {


    WSADATA wsaData;
    SOCKET hServer;
    WORD wVerSion = MAKEWORD(2, 2);
    if (WSAStartup(wVerSion, &wsaData)) {
        //�������ʧ��
        debugLog((char*)"initSocket->WSAStartup error");
        return FALSE;
    };

    return TRUE;


}

//�ȴ���socket���󶨱��ص�ַ��Ȼ��ʼ����
SOCKET BindListen(int nBackLog) {

    //��ʽ�׽���SOCK_STREAM��  TCPЭ�� IPPROTO_TCP
    SOCKET hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (hServer == INVALID_SOCKET) {

        debugLog((char*)"bind listen->socket error");
        return INVALID_SOCKET;
    }

    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(10080);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    //��
    int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
    if (nRet == SOCKET_ERROR) {
        debugLog((char*)"socket ��ʧ��");
        closesocket(hServer);
        return INVALID_SOCKET;
    }

    //��socket�Ͻ��м���
    if (listen(hServer, 10) == SOCKET_ERROR) {
        closesocket(hServer);
        WSACleanup();
        debugLog((char*)"listen����");
        return INVALID_SOCKET;
    }

}

SOCKET AcceptConnetion(SOCKET hSocket) {

    sockaddr_in saConnAddr;
    int nSize = sizeof(saConnAddr);

    SOCKET sd = accept(hSocket, (LPSOCKADDR)&saConnAddr, &nSize);
    if (sd == INVALID_SOCKET) {
        debugLog((char*)"AcceptConnetion ����");
        return INVALID_SOCKET;
    }


    return sd;
}


//�̴߳���ҵ���߼�
DWORD WINAPI ClientThreadFun(LPVOID lpParam) {

    SOCKET sd = (SOCKET)lpParam;
    //�ͻ��˴���
    if (ClientConFun(sd) == FALSE) {
        //break;
    }

    //�ر�һ���ͻ�������
    if (CloseConnect(sd) == FALSE) {
        //break;
    }
    return 0;

};

BOOL ClientConFun(SOCKET sd) {


    char buf[nBufMaxSize];
    int nRetByte;
    //�������Կͻ��˵�����
    do {
        nRetByte = recv(sd, buf, nBufMaxSize, 0);
        if (nRetByte == SOCKET_ERROR) {
            debugLog((char*)"AcceptConnetion ����");
            return FALSE;
        }
        else if (nRetByte != 0) {

            buf[nRetByte] = 0;
            cout << "���յ�һ������" << buf << endl;
            int nSend = 0;
            while (nSend < nRetByte) {

                int nTemp = send(sd, &buf[nSend], nRetByte - nSend, 0);
                if (nTemp > 0) {
                    nSend += nTemp;
                }
                else if (nTemp == SOCKET_ERROR) {
                    debugLog((char*)"ClientConFun -> send ����");
                    return FALSE;
                }
                else
                {
                    //send����0�����ڴ�ʱsend < nRetByte��Ҳ�������ݻ�û���ͳ�ȥ����ʾ�ͻ��˱����ⱻ�ر���
                    debugLog((char*)"ClientConFun -> send -> close ����");
                    return FALSE;
                }
            }
        }
    } while (nRetByte != 0);

    return TRUE;
}

//�ر�һ������
BOOL CloseConnect(SOCKET sd) {

    //���ȷ���һ��TCP FIN�ֶΣ���Է������Ѿ�������ݷ���
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

            debugLog((char*)"closeconnect ����Ľ�������");
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

        //�����յĿͻ��˵�������������Ϊ����һ���߳�
        DWORD dwThreadId;
        HANDLE hThread = CreateThread(0,0, ClientThreadFun,(LPVOID)sd, 0, &dwThreadId);
        if (hThread) {
            CloseHandle(hThread);
        }

        ////�ͻ��˴���
        //if (ClientConFun(sd) == FALSE) {
        //    //break;
        //}

        ////�ر�һ���ͻ�������
        //if (CloseConnect(sd) == FALSE) {
        //    //break;
        //}

    }

    if (closesocket(hSocket) == SOCKET_ERROR) {
        debugLog((char*)"mytcpSerFun --> closesocket");
        return;
    }
}