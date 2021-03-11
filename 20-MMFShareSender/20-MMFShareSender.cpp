// 20-MMFShareSender.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

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
	hMapView = MapViewOfFile(hMapObject, FILE_MAP_WRITE, 0, 0, 0);
	if (!hMapView)
	{
		MessageBox(NULL, TEXT("内存映射失败"), TEXT("Error"), MB_OK);
		return FALSE;
	}


	//向共享内存写入数据					
	//strcpy((char*)hMapView, "Test Shared Memery");

	

	for (int i = 0; i < 10; i++) {
		char szBuffer[nBufSize] = "Test Shared Memery";
		char suf[2] = { 0 };
		suf[0] = i + 0x30;
		strcat((char*)szBuffer, suf);
		printf("%s \n", szBuffer);

		strcpy((char*)hMapView, (char*)szBuffer);

		//避免太快数据被覆盖				
		char szBuffer2[nBufSize] = { 0 };
		memcpy(szBuffer2, hMapView, nBufSize);
		size_t nSize = strlen(szBuffer2);
		if (nSize > 0) {
			Sleep(100);
		}
		
	}

	getchar();
}



