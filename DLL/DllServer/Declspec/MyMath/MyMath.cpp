#include "stdafx.h"
#include<Windows.h>

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

extern "C" __declspec(dllexport) int MakeSquare(int num) {
	int result = -1;
	if (!isNumNegative(num)) {
		result = num * num;
	}
	return result;
}



