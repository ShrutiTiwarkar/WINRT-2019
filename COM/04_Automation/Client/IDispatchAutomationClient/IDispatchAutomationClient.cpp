#include<Windows.h>
#include<stdio.h> 
#include "AutomationServerWithRegFile.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COM Automation IDispatch Client");

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		AppName,
		TEXT("COM Automation Client"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ComErrorDescriptionString(HWND, HRESULT);

	IDispatch *pIDispatch = NULL;
	HRESULT hr;
	DISPID dispid;
	OLECHAR *szFunctionName_one = (OLECHAR *)L"SumOfTwoIntegers"; // L means Literal. give L if string is hardcoded.
	OLECHAR *szFunctionName_two = (OLECHAR *)L"SubtractionOfTwoIntegers"; // L means Literal. give L if string is hardcoded.
	VARIANT vArg[2], vRet;
	DISPPARAMS param = { vArg, 0, 2, NULL };
	int n1, n2;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
	{
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("COM library can not be initialized"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}

		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Component can not be created"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}

		n1 = 100;
		n2 = 25;

		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName_one,	
			1,		              
			GetUserDefaultLCID(),  
			&dispid);              

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not get ID for SumOfTwoIntegers()"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}

		
		VariantInit(vArg);     

		vArg[0].vt = VT_INT;  
		vArg[0].intVal = n2;      
		vArg[1].vt = VT_INT;  
		vArg[1].intVal = n1;      

		param.cArgs = 2;          

		param.cNamedArgs = 0;     

		param.rgdispidNamedArgs = NULL;

		
		VariantInit(&vRet);

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL
		);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not Invoke Function SumOfTwoIntegers()"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		else
		{
			wsprintf(str, TEXT("Sum of %d and %d Is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("SumOfTwoIntegers"), MB_OK);
		}



		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName_two,
			1,
			GetUserDefaultLCID(),
			&dispid
		);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not get ID for SubtractionOfTwoIntegers()"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}


		VariantInit(&vRet);

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL
		);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not Invoke Function SubtractionOfTwoIntegers()"), TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}
		else
		{
			wsprintf(str, TEXT("Subtraction of %d and %d Is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("SubtractionOfTwoIntegers"), MB_OK);
		}

		VariantClear(vArg);
		VariantClear(&vRet);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hwnd);
		break;
	}

	case WM_DESTROY:
	{
		CoUninitialize();
		PostQuitMessage(0);
		break;
	}
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR *szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%s"), szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM ERROR"), MB_OK);
}

