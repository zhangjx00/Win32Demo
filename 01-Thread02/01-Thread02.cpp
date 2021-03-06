// 01-Thread02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <windows.h>


//远程线程，控制Thread01
//参数：线程ID，函数地址
BOOL MyCreateRemoteThread(DWORD dwProcessID, DWORD dwProcAddr) {

    HANDLE hProcess;
    HANDLE hThread;
    HANDLE dwThreadId;

    hProcess = 0;

    //1、得到句柄
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
    if (hProcess == NULL) {
        OutputDebugString(TEXT("OpenProcess Error \n"));
        return FALSE;
    }

    //2、创建远程线程
    //返回线程ID
    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)dwProcAddr, NULL, 0, (LPDWORD)&dwThreadId);
    if (hThread == NULL) {
        OutputDebugString(TEXT("hThread Error \n"));
        CloseHandle(hProcess);
        return FALSE;
    }


    //3、关闭
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return true;

}


int main(int argc, char* argv[])
{
    MyCreateRemoteThread(17220, 0x003617E0);

    getchar();
    return 0;
}
