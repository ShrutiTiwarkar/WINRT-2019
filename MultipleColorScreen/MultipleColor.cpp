/************************************************
*ASSIGNMENT - 8									*
*		This assignment is about the displaying	*
*		color like vertical strips on window	*
*************************************************/

#include<Windows.h>
#define MyTimer 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;												// Structure of window features
	HWND hwnd;															// Unique Id store 
	MSG msg;															// Structure for message Loop
	TCHAR szAppName[] = TEXT("Multiple Color Window");

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
		TEXT("Multiple Color Window"),									// Title of application			
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


	static RECT rcTemp;																// For Rectangle like Client Area for vertical Strip
	LONG rcWidth;																	// Width of one rectangular strip

	switch (iMsg)
	{
	
	case WM_CREATE:
		SetTimer(hwnd, MyTimer, (UINT)(1500), NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MyTimer);
		iPaintFlag++;
		if (iPaintFlag > 7) {
			iPaintFlag = 0;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		SetTimer(hwnd, MyTimer, (UINT)(500), NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		rcWidth = rc.right/8;

		hdc = BeginPaint(hwnd, &ps);

		switch (iPaintFlag)
		{
		case 0:
			rcTemp.left = 0;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 1:

			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(255, 0, 0));							//Red
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 2:


			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(0, 128, 0));							//Green
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 3:

			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(0, 0, 255));							//Blue
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 4:

			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(0, 255, 255));						//Cyan
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 5:

			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(255, 0, 255));						//Magenta
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 6:

			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(255, 255, 0));						//Yellow
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 7:

			rcTemp.left = rcTemp.right;
			rcTemp.top = 0;
			rcTemp.right = (rcTemp.left + rcWidth);
			rcTemp.bottom = rc.bottom;

			hBrush = CreateSolidBrush(RGB(255, 255, 255));						//White
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
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
