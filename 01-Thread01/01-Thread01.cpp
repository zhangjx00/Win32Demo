// 01-Thread01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <windows.h>



void Fun() {

    for (int i = 0; i < 10; i++) {

        Sleep(1000);
        printf("Fun().....\n");
    }

}

DWORD WINAPI ThreadProc(PVOID lpParameter) {

    Fun();
    return 0;

}

int main(int argc, char* argv[])
{
    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);

    getchar();
    return 0;
}
