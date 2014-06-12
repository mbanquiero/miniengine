// AppViewer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AppViewer.h"
#include <graphics\RenderEngine.h>
#include <string.h>

CRenderEngine _engine;

int _cant_examples = 0;
IExample * _examples[MAX_EXAMPLES] = { 0 };
IExample * _current_example = NULL;
bool _listar_ejemplos = false;


void add_example(IExample * example) {
	_examples[_cant_examples++] =  example;
}

void set_example(IExample * example) {
	if (_current_example) {
		example->close();
	}
	_current_example = example;

	_current_example->init();
}

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPTSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_APPVIEWER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APPVIEWER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPVIEWER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_APPVIEWER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

void ListarEjemplos()
{
	if (!_listar_ejemplos)
		return;

	int x = 10;
	int y = 30;
	int sepy = 20;

	char text[1000];

	_engine.TextOutA(x, y, "Listado de Ejemplos:  Presiona el nro de ejemplo a cargar.");
	y += 5;
	_engine.TextOutA(x, y, "------------------------");
	y += sepy;

	for (int i = 0; i < _cant_examples; i++)
	{
		text[0] = '0' + i%10 + 1;
		text[1] = '.';
		text[2] = ' ';
		strcpy(text + 3, _examples[i]->getName());
		_engine.TextOutA(x, y, text);
		y += sepy;
	}	
}

void RenderScene()
{
	ListarEjemplos();
	_engine.TextOutA(30, 10, (char*)_current_example->getDescription());

	_current_example->render(_engine.elapsed_time);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
	  return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //sort examples
   for (int i = 0; i < _cant_examples - 1 ; i++)
   {
	   for (int j = i+1; j < _cant_examples; j++)
	   {
		   if (strcmp(_examples[i]->getName(), _examples[j]->getName()) > 0)
		   {
			   IExample * aux = _examples[i];
			   _examples[i] = _examples[j];
			   _examples[j] = aux;
		   }
	   }
   }

   
   BOOL seguir = TRUE;
   float time = 0;
   LARGE_INTEGER F, T0, T1;   // address of current frequency
   QueryPerformanceFrequency(&F);
   QueryPerformanceCounter(&T0);

   if (!_engine.IsReady())
   {
		_engine.Create(hWnd);
		set_example(_examples[0]);
   }

   while (seguir)
   {

	   QueryPerformanceCounter(&T1);
	   double elapsed_time = (double)(T1.QuadPart - T0.QuadPart) / (double)F.QuadPart;
	   T0 = T1;
	   time += (float)elapsed_time;
	   _engine.Update((float)elapsed_time);

	   _engine.RenderFrame(RenderScene);

	   D3DXVECTOR3 ViewDir = _engine.lookAt - _engine.lookFrom;
	   D3DXVec3Normalize(&ViewDir, &ViewDir);
	   MSG Msg;
	   ZeroMemory(&Msg, sizeof(Msg));
	   if (PeekMessage(&Msg, NULL, 0U, 0U, PM_REMOVE))
	   {

		   if (Msg.message == WM_QUIT || Msg.message == WM_CLOSE)
		   {
			   seguir = FALSE;
			   exit(0);
			   break;
		   }

		   // dejo que windows procese el mensaje
		   TranslateMessage(&Msg);
		   DispatchMessage(&Msg);

		   switch (Msg.message)
		   {
		   case WM_KEYDOWN:
			   switch ((int)Msg.wParam)	    // virtual-key code 
			   {
			   case VK_F1:
				   _listar_ejemplos = !_listar_ejemplos;
				   break;

			   case '0':
			   case '1':
			   case '2':
			   case '3':
			   case '4':
			   case '5':
			   case '6':
			   case '7':
			   case '8':
			   case '9':
			   {
							if (!_listar_ejemplos)
								break;

							int nro = ((int)Msg.wParam - '0' + 9)%10;

							if (nro >= _cant_examples)
								break;

							set_example(_examples[nro]);
							_listar_ejemplos = false;
							break;
			   }

			   }
			   break;
		   }

	   }
   }

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;		
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FILE_VEREJEMPLOS:
			_listar_ejemplos = !_listar_ejemplos;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



