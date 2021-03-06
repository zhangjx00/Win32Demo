﻿// MMFShare.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "windows.h"

HANDLE g_hMapFile;
LPSTR g_lpBuff;


int main()
{
    //getchar();

    //内核对象，物理页
    g_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,PAGE_READWRITE, 0, 4 * 1024, TEXT("共享内存"));
    //将物理页与线性地址进行映射
    g_lpBuff = (LPSTR)MapViewOfFile(g_hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 4 * 1024);

    DWORD error = GetLastError();
    *(PDWORD)g_lpBuff = 0x12345678;
    printf("%p", g_lpBuff);

    //getchar();
    *(PDWORD)g_lpBuff = NULL;

    //getchar();
    *(PDWORD)g_lpBuff = 0x1000000;

    //getchar();
    *(PDWORD)g_lpBuff = NULL;

    //getchar();
    //关闭映射
    UnmapViewOfFile(g_lpBuff);
    //关闭句柄
    CloseHandle(g_hMapFile);

    return 0;

}

