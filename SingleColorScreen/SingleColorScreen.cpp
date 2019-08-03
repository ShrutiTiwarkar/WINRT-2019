/************************************************
*ASSIGNMENT - 7									*
*		This assignment is about the changing	*
*		color of the screen according to button	*
*		pressed by the user.					*
*************************************************/

#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;												// Structure of window features
	HWND hwnd;															// Unique Id store 
	MSG msg;															// Structure for message Loop
	TCHAR szAppName[] = TEXT("Single Color Window");

	wndclass.cbSize = sizeof(WNDCLASSEX);								//	Size of Structure WNDCLASSEX
	wndclass.style = CS_VREDRAW | CS_HREDRAW;							//	Vertical & Horizontal extension
	wndclass.cbClsExtra = 0;											//	Extra Information about Class
	wndclass.cbWndExtra = 0;											//  Extra Information about Window
	wndclass.lpfnWndProc = WndProc;										//  CallBack funcntion Name
	wndclass.hInstance = hInstance;										//  Current Window Instance
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					//	Load Default Icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);						//  Load Default Cursor
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		// Client Area Background
	wndclass.lpszClassName = szAppName;									// Class Name
	wndclass.lpszMenuName = NULL;										// Menu default
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);											// Register the Window to the OS


	/****************************************************
	*													*
	*	Create the Registered Window according to the	*
	*	parameters. It returns a Unique Id and store in *
	*	"hwnd" which helps to access window elements	*
	*													*
	*****************************************************/
	hwnd = CreateWindow(szAppName,
		TEXT("Single Color Window"),									// Title of application			
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,													// X co-ordinate
		CW_USEDEFAULT,													// y co-ordinate
		CW_USEDEFAULT,													// width
		CW_USEDEFAULT,													// height
		NULL,															// Parent Window
		NULL,															// Menu Handler
		hInstance,														// current window Instance
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	/********************************************************
	*	Message Loop										*
	*														*
	*	Parameters : msg  => Addeess of structure MSG		*
	*				 NULL => Current and its Child Window	*
	*				 0,0  => Range							*
	*														*
	*********************************************************/
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	static int iPaintFlag = -1;														//Define for select color
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[255];
	switch (iMsg)
	{

	case WM_CHAR:

		switch (LOWORD(wParam)) {
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd,NULL,TRUE);
			break;
		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'M':
		case 'm':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'Y':
		case 'y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'K':
		case 'k':
		default:
			iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);

		switch (iPaintFlag)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));							
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));							//Red
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 128, 0));							//Green
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));							//Blue
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));						//Cyan
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));						//Magenta
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));						//Yellow
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));						//White
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
