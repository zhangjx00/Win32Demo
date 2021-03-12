// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <iostream>
#include <windows.h> 
#include <tchar.h>
#include<thread>

extern "C" _declspec(dllexport) VOID RECEIVE(DWORD, LPSTR, DWORD);
extern "C" _declspec(dllexport) VOID ACCEPT(DWORD);
extern "C" _declspec(dllexport) VOID CLOSE(DWORD);

extern "C" _declspec(dllexport)  BOOL InitWeChatSocket(VOID(*RECEIVE)(DWORD, LPSTR, DWORD), VOID(*ACCEPT)(DWORD), VOID(*CLOSE)(DWORD));


DWORD WINAPI ThreadProc(PVOID lpParameter);

void DebugLog(LPCWSTR logStr) {
    OutputDebugString(logStr);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {

    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


typedef struct CallBackStruct {
    VOID(*RECEIVE)(DWORD, LPSTR, DWORD);
    VOID(*ACCEPT)(DWORD);
    VOID(*CLOSE)(DWORD);
} CallBackFun;



BOOL InitWeChatSocket(VOID(*RECEIVE)(DWORD, LPSTR, DWORD), VOID(*ACCEPT)(DWORD), VOID(*CLOSE)(DWORD)) {



    //1、直接执行
    char data[10] = "abcd";
    (*RECEIVE)(1, data, 10);
    Sleep(2000);


    //2、开个线程执行

    CallBackFun* fun = (CallBackFun*)malloc(sizeof(CallBackFun));
    fun->RECEIVE = RECEIVE;
    fun->ACCEPT = ACCEPT;
    fun->CLOSE = CLOSE;

    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, fun, 0, NULL);
    if (hThread) {
        CloseHandle(hThread);
    }
    return TRUE;
}




//新线程，开启socket
DWORD WINAPI ThreadProc(PVOID lpParameter) {


    CallBackFun* fun = (CallBackFun*)lpParameter;

    char data[10] = "abcd";
    for (int i = 0; i < 10; i++) {
    
        fun->RECEIVE(1, data, 10);
        Sleep(2000);
    }

    return 0;

}
