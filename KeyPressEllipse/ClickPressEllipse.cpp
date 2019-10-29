#include<Windows.h>
#include<windowsx.h>
#include<gdiplus.h>

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);


	hwnd = CreateWindow(szAppName,
		TEXT("Key Press Ellipse"),
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

	
	static int xPos, yPos;
	static RECT rc;
	static int colorChoice = 0;
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	HRGN bgRgn;

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	
	case WM_LBUTTONDOWN:

		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);

		rc.left = xPos - 50;
		rc.top = yPos - 50;
		rc.right = xPos + 50;
		rc.bottom = yPos + 50;

		colorChoice++;
		if (colorChoice > 8) {
			colorChoice = 1;
		}

		InvalidateRect(hwnd, &rc, false);
		
		break;
	

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);
	
		
		//Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
		
		//FillEllipse(hBrush,&rc);
	

		switch (colorChoice)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));//Red
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 128, 0));//Green
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));//Blue
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));//Cyan
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));//Magenta
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));//Yellow
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));// Black
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		case 8:
			hBrush = CreateSolidBrush(RGB(255, 184, 0));//Orange
			bgRgn = CreateEllipticRgn(rc.left, rc.top, rc.right, rc.bottom);
			SelectObject(hdc, hBrush);
			FillRgn(hdc, bgRgn, hBrush);
			break;
		}

		UpdateWindow(hwnd);

		EndPaint(hwnd, &ps);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

