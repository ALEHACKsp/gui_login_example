// WindowsProject3.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "framework.h"
#include "WindowsProject4.h"

#define MAX_LOADSTRING 100
#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)

enum STATUS {
	NOTHING, OK, FAIL
};

struct User {
	wchar_t name[200];
	wchar_t pwd[200];
	bool ready;
	STATUS status;
};

struct User g_User { L"", L"", false, NOTHING };

// Globale Variablen:
HINSTANCE hInst;                                // Aktuelle Instanz
WCHAR szTitle[MAX_LOADSTRING] = L"LOADER";                  // Titelleistentext
WCHAR szWindowClass[MAX_LOADSTRING];            // Der Klassenname des Hauptfensters.

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Hier Code einfügen.

	// Globale Zeichenfolgen initialisieren
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Anwendungsinitialisierung ausführen:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT4));

	MSG msg;

	// Hauptnachrichtenschleife:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = 0;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

	HWND hWnd = CreateWindowW(szWindowClass, L"LOADER", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, ScreenY, 340, 140, nullptr, nullptr, hInstance, nullptr);
	// 360, 140
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK: Verarbeitet Meldungen für das Hauptfenster.
//
//  WM_COMMAND  - Verarbeiten des Anwendungsmenüs
//  WM_PAINT    - Darstellen des Hauptfensters
//  WM_DESTROY  - Ausgeben einer Beendenmeldung und zurückkehren
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static const WCHAR lbl_usr[] = L"Username:";
	static const WCHAR lbl_pwd[] = L"Password:";
	static WCHAR lbl_sta[50] = L"Status: online";

	static HWND hwndCommandLink;
	static RECT rect;

	static HWND editctl1;
	static HWND editctl2;

	switch (message)
	{
	case WM_CREATE:
	{
		// Pos Window
		RECT rc;
		GetWindowRect(hWnd, &rc);
		int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
		int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
		SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		// Create Button
		hwndCommandLink = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed
			L"login",        // Text will be defined later
			WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles
			200,        // x position 
			60,         // y position 
			100,        // Button width
			20,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed

			//Create TextBox
		editctl1 = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN | WS_EX_CLIENTEDGE, 120, 10, 180, 20, hWnd, nullptr, nullptr, 0);
		editctl2 = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN | WS_EX_CLIENTEDGE, 120, 30, 180, 20, hWnd, nullptr, nullptr, 0);
	}
	case WM_COMMAND:
	{
		if (lParam == (LPARAM)hwndCommandLink)
		{
			int name_len = GetWindowTextLength(editctl1);
			int pwd_len = GetWindowTextLength(editctl2);
			if (name_len < 200 && pwd_len < 200) {
				GetWindowText(editctl1, g_User.name, name_len + 1);
				GetWindowText(editctl2, g_User.pwd, pwd_len + 1);
				g_User.ready = true;
			}
			if (HIWORD(wParam) == BN_CLICKED)
				SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		if (lParam == (LPARAM)editctl1) {
			//Do Something
		}
		int wmId = LOWORD(wParam);
		// Menüauswahl analysieren:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//RoundRect(hdc, rect.right / 2 - 30, rect.bottom / 2 - 30,
		//	rect.right / 2 + 30, rect.bottom / 2 + 30, 15, 15);
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(DKGRAY_BRUSH));

		TextOut(hdc, 20, 10, lbl_usr, _tcslen(lbl_usr));
		TextOut(hdc, 20, 30, lbl_pwd, _tcslen(lbl_pwd));
		TextOut(hdc, 20, 60, lbl_sta, _tcslen(lbl_sta));
		// TODO: Zeichencode, der hdc verwendet, hier einfügen...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
