#include<Windows.h>
#include "SetIcon.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Icon Application");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance,(LPSTR) MYICON);				//Customized ICON
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(hInstance, (LPSTR)MYICON);				// Customized ICON
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Icon and FlashScreen Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static HINSTANCE hInst;
	static HBITMAP hBitmap  = NULL;

	HDC hdc, hMemdc;																	// Specialist
	PAINTSTRUCT ps;																		// Used by Os internally
	RECT re;
	TCHAR str[255];																		// Display Message
	TCHAR str1[] = TEXT("My First Window with Text");

	switch (iMsg) {
	case WM_CREATE:																	
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		hBitmap = (HBITMAP)LoadBitmap(hInst,(LPCSTR) MYBITMAP);
		//hBitmap = (HBITMAP)LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));	// Another option
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &re);													// size of Client Area
		hdc = BeginPaint(hwnd, &ps);												// Call Specialist
		hMemdc = CreateCompatibleDC(NULL);
		SelectObject(hMemdc, (HGDIOBJ)hBitmap);
		StretchBlt(hdc, 0, 0, 1024, 768, hMemdc, 0, 0, 800, 600, SRCCOPY);
		DeleteDC(hMemdc);
		EndPaint(hwnd, &ps);														// Stop painting
		break;

	
	case WM_KEYDOWN:// Key is press down
		wsprintf(str, TEXT("WM_KeyDown is Arrived"));
		MessageBox(hwnd, str, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_LBUTTONDOWN:															// Mouse Left botton pressed
		wsprintf(str, TEXT("WM_LeftButtonDown is Arrived"));
		MessageBox(hwnd, str, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_DESTROY:																// close Application
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
