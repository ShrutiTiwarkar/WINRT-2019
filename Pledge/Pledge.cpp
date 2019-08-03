/***************************************************************
* Assignment - 6						*
*	This Assignment Displays the pledge in tri color	*
*	Orange, White, Green					*
*****************************************************************/

#include<Windows.h>

/***********************************************************************
* CallBack Function							*
*									*
*	Name		:WndProc					*
*	Parameters	:HWND	=> Handle of Window(unsigned int)	*
*			 UNIT 	=> Message(unsigned int)		*
*			 WPARAM	=> Word Parameter			*
*			 LPARAM => Long Parameter			*
*	Return Type :	LRESULT	CALLBACK				*
*************************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/************************************************************************
* Entry Point function							*
*									*
*	Name	:WinMain						*
*	Parameter:HINSTANCE => current Window Instance			*
*		  HINSTANCE => Parent Window Instance			*
*		  LPSTR	    => Command Line Arguments			*
*		  iCmdShow  => Window Display				*
*	Return Type :	int WINAPI					*
************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;									// Structure of window features
	HWND hwnd;										// Unique Id store 
	MSG msg;										// Structure for message Loop
	TCHAR szAppName[] = TEXT("Pledge Program");

	wndclass.cbSize = sizeof(WNDCLASSEX);							// Size of Structure WNDCLASSEX
	wndclass.style = CS_VREDRAW | CS_HREDRAW;						// Vertical & Horizontal extension
	wndclass.cbClsExtra = 0;								// Extra Information about Class
	wndclass.cbWndExtra = 0;								// Extra Information about Window
	wndclass.lpfnWndProc = WndProc;								// CallBack funcntion Name
	wndclass.hInstance = hInstance;								// Current Window Instance
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);					// Load Default Icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);						//  Load Default Cursor
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);				// Client Area Background
	wndclass.lpszClassName = szAppName;							// Class Name
	wndclass.lpszMenuName = NULL;								// Menu default
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);								// Register the Window to the OS


	/********************************************************
	*							*
	*	Create the Registered Window according to the	*
	*	parameters. It returns a Unique Id and store in *
	*	"hwnd" which helps to access window elements	*
	*							*
	*********************************************************/
	hwnd = CreateWindow(szAppName,
		TEXT("National Pledge"),							// Title of application			
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,									// X co-ordinate
		CW_USEDEFAULT,									// y co-ordinate
		CW_USEDEFAULT,									// width
		CW_USEDEFAULT,									// height
		NULL,										// Parent Window
		NULL,										// Menu Handler
		hInstance,									// current window Instance
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	/****************************************************************
	*	Message Loop						*
	*								*
	*	Parameters : msg  => Addeess of structure MSG		*
	*		     NULL => Current and its Child Window	*
	*		     0,0  => Range				*
	*								*
	*****************************************************************/
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;																			// Specialist
	PAINTSTRUCT ps;																		// Used by Os internally
	RECT rc;
	const char *str[] = {" ","India is my country","All Indians are my brothers and sisters.","I love my country, and I am proud of","its rich and varied heritage.","I shall always strive to be worthy of it.","I shal give my parents, teacher and all","elders respect and treat everyone with","courtesy.","To my country and my people, I pledge","my devotion.","In their well being and prosperity."};
	int i,x, y;
	static int cyChar;
	TEXTMETRIC tm;
	TCHAR str1[255];
	
	switch (iMsg) {
	case WM_CREATE:																	// Create Window
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hwnd, hdc);
		break;

	case WM_PAINT:																	// Display text in multiple color
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));

		SetTextColor(hdc, RGB(255, 165, 0));
		DrawText(hdc, "	            National Pledge", -1, &rc, DT_SINGLELINE);
		

		x = 50;
		y = 12;
		
		for (i = 0; i < 12; i++) {
			if (i < 4) {
				
				SetTextColor(hdc, RGB(255, 165, 0));
			}
			else if(i >= 4 && i <= 7){
				SetTextColor(hdc, RGB(255,255,255));
			}
			else {
				SetTextColor(hdc, RGB(0,255,0));
			}
			TextOut(hdc, x, y, str[i],strlen(str[i]));
			y = y + cyChar;
		}
		
		EndPaint(hwnd, &ps);														// Stop painting
		break;

	case WM_KEYDOWN:																// Key is press down
		wsprintf(str1, TEXT("WM_KeyDown is Arrived"));
		MessageBox(hwnd, str1, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_LBUTTONDOWN:															// Mouse Left botton pressed
		wsprintf(str1, TEXT("WM_LeftButtonDown is Arrived"));
		MessageBox(hwnd, str1, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_DESTROY:																// close Application
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


