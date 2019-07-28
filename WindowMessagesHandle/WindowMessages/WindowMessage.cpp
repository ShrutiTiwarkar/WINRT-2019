/************************************************************************
* Assignment - 3							*
*		This assignmnet Displays the "Hello World" or any text	*
*		in the middle of the Client Area.			*
*		For this, WM_PAINT is used.				*
*************************************************************************/

#include<Windows.h>

/************************************************************************
* CallBack Function							*
*									*
*	Name		:	WndProc					*
*	Parameters	:	HWND => Handle of Window(unsigned int)	*
*				UNIT	=> Message(unsigned int)	*
*				WPARAM	=> Word Parameter		*
*				LPARAM  => Long Parameter		*
*	Return Type :	LRESULT	CALLBACK				*
************************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/************************************************************************
* Entry Point function							*
*									*
*	Name		:	WinMain					*
*	Parameter	:	HINSTANCE => current Window Instance	*
*				HINSTANCE => Parent Window Instance	*
*				LPSTR	  => Command Line Arguments	*
*				iCmdShow  => Window Display		*
*	Return Type :	int WINAPI					*
************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;						// Structure of window features
	HWND hwnd;							// Unique Id store 
	MSG msg;							// Structure for message Loop
	TCHAR szAppName[] = TEXT("Hello World Program");

	wndclass.cbSize = sizeof(WNDCLASSEX);				//  Size of Structure WNDCLASSEX
	wndclass.style = CS_VREDRAW | CS_HREDRAW;			//  Vertical & Horizontal extension
	wndclass.cbClsExtra = 0;					//  Extra Information about Class
	wndclass.cbWndExtra = 0;					//  Extra Information about Window
	wndclass.lpfnWndProc = WndProc;					//  CallBack funcntion Name
	wndclass.hInstance = hInstance;					//  Current Window Instance
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//  Load Default Icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);			//  Load Default Cursor
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	// Client Area Background
	wndclass.lpszClassName = szAppName;				// Class Name
	wndclass.lpszMenuName = NULL;					// Menu default
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);					// Register the Window to the OS


	/***************************************************************
	*								*
	*	Create the Registered Window according to the		*
	*	parameters. It returns a Unique Id and store in 	*
	*	"hwnd" which helps to access window elements		*
	*								*
	*****************************************************************/
	hwnd = CreateWindow(szAppName,
		TEXT("Hello Word Application"),				// Title of application			
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,						// X co-ordinate
		CW_USEDEFAULT,						// y co-ordinate
		CW_USEDEFAULT,						// width
		CW_USEDEFAULT,						// height
		NULL,							// Parent Window
		NULL,							// Menu Handler
		hInstance,						// current window Instance
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

	TCHAR str[255];																		// Display Message

	switch (iMsg) {
	case WM_CREATE:									// Wnen window is Created								// Create Window
		wsprintf(str, TEXT("WM_CREATE is Arrived"));
		MessageBox(hwnd, str, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_KEYDOWN:								// Any Key Press								// Key is press down
		wsprintf(str, TEXT("WM_KeyDown is Arrived"));
		MessageBox(hwnd, str, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_LBUTTONDOWN:								// Mouse Left Click							// Mouse Left botton pressed
		wsprintf(str, TEXT("WM_LeftButtonDown is Arrived"));
		MessageBox(hwnd, str, TEXT("MESSAGE..."), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_DESTROY:								// Window Destroy								// close Application
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
