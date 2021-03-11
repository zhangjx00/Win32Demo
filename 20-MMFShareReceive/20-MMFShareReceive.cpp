// 20-MMFShareReceive.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
//#include <string.h>

#define nBufSize 0x1024


int main()
{
	HANDLE hMapObject;
	HANDLE hMapView;

	//创建FileMapping对象					
	hMapObject = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, nBufSize, TEXT("shared"));
	if (!hMapObject)
	{
		MessageBox(NULL, TEXT("共享内存失败"), TEXT("Error"), MB_OK);
		return FALSE;
	}
	//将FileMapping对象映射到自己的进程					
	hMapView = MapViewOfFile(hMapObject, FILE_MAP_WRITE, 0, 0, nBufSize);
	if (!hMapView)
	{
		MessageBox(NULL, TEXT("内存映射失败"), TEXT("Error"), MB_OK);
		return FALSE;
	}



	//存在问题，如果写入数据过快，会覆盖历史数据
	while (true) {

		//从共享内存读取数据					
		char szBuffer[nBufSize] = { 0 };
		memcpy(szBuffer, hMapView, nBufSize);

		size_t nSize = strlen(szBuffer);


		if (nSize > 0) {
			printf("receive: %s \n", szBuffer);

			//清空buff
			memset(hMapView,0, nBufSize);

		}

		//Sleep(100);

	}

	getchar();

}
