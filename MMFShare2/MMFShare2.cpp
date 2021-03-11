// MMFShare2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "windows.h"

HANDLE g_hMapFile;
LPSTR g_lpBuff;
char* dwType;


int main()
{
    dwType = 0;

    //内核对象，物理页
    g_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4 * 1024, TEXT("共享内存"));;

    //将物理页与线性地址进行映射
    g_lpBuff = (LPSTR)MapViewOfFile(g_hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 4 * 1024);

    for (;;) {
        if (g_lpBuff != NULL) {
        
            CopyMemory(&dwType, g_lpBuff, 4);
            if(dwType != 0){
                printf("数据: %x \n", dwType);
                *(PDWORD)g_lpBuff = NULL;
            }
            
        }

        Sleep(1000);
        
    }

    //关闭映射
    UnmapViewOfFile(g_lpBuff);
    //关闭句柄
    CloseHandle(g_hMapFile);
    getchar();

    return 0;

}
