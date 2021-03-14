// 21-CallBackFunction.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h> 
#include <tchar.h>
#include<thread>

using namespace std;

// 定义函数指针

typedef VOID(* RECEIVE)(DWORD, LPSTR, DWORD);
typedef VOID(* ACCEPT)(DWORD);
typedef VOID(* CLOSE)(DWORD);



typedef BOOL(* InitFn)(RECEIVE, ACCEPT, CLOSE);

#ifdef _UNICODE
HINSTANCE hModule = LoadLibrary(L"21-CallBackDLL.dll");
#else
HINSTANCE hModule = LoadLibrary("21-CallBackDLL.dll");
#endif

//InitFn InitWeChatSocket = (InitFn)GetProcAddress(hModule, "InitWeChatSocket");


VOID receive(DWORD clientId, LPSTR data, DWORD len)
{
    std::cout << "new message! " << data << endl;
}
VOID accept(DWORD clientId)
{
    std::cout << "new client! " << endl;
}
VOID close(DWORD clientId)
{
    std::cout << "client closed! " << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{

    DWORD in = 0;
    BOOL rs = FALSE;

    InitFn InitWeChatSocket = (InitFn)GetProcAddress(hModule, "InitWeChatSocket");

    rs = InitWeChatSocket(receive, accept, close);
    std::cout << "调用结果：" << rs << endl;


    cin.get();
}

