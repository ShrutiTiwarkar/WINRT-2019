#include<Windows.h>

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);


	hwnd = CreateWindow(szAppName,
		TEXT("MULTI-THREADING WINDOW"),
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

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;

	TCHAR str[255];

	switch (iMsg) {

	case WM_CREATE:
		hThreadOne = CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcOne,
			(LPVOID)hwnd,
			0,
			NULL);
		
		hThreadTwo = CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd,
			0,
			NULL);

		break;

	case WM_KEYDOWN:																// Key is press down
		wsprintf(str, TEXT("Key is Pressed...!"));
		MessageBox(hwnd, str, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_DESTROY:																// close Application
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	HDC hdc;
	long int i = 0;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));
	for (i = 0; i < 429495729; i++) {
		wsprintf(str, TEXT("Thread One -> Increasing Order : %ld"),i);
		TextOut(hdc, 5, 5, str, strlen(str));
	}
	ReleaseDC(HWND(param), hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {
	HDC hdc;
	long int i = 0;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));
	for (i = 429495729; i > 0; i--) {
		wsprintf(str, TEXT("Thread Two -> Decreasing Order : %ld"), i);
		TextOut(hdc, 5, 20, str, strlen(str));
	}
	ReleaseDC(HWND(param), hdc);
	return 0;
}

