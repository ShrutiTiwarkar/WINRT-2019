// MyMath.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include<Windows.h>

extern "C" int MakeSquare(int num);
extern "C" BOOL isNumNegative(int num);

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" BOOL isNumNegative(int num) {
	if (num < 0) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

extern "C" int MakeSquare(int num) {
	int result = -1;
	if (!isNumNegative(num)) {
		result = num * num;
	}
	return result;
}









