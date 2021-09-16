#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>


// Global Variables:
 HINSTANCE hInst;                                // current instance
#define szWindowClass _T("WINCLASS1")            // the main window class name
#define szTitle _T("Tictactoe Game")

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// ENTRY POINT
int WINAPI wWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR    lpCmdLine,
                   int       nCmdShow)
{
    // Perform application initialization
    MyRegisterClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);

    winclass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    winclass.lpfnWndProc    = WndProc;
    winclass.cbClsExtra     = 0;
    winclass.cbWndExtra     = 0;
    winclass.hInstance      = hInstance;
    winclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    winclass.lpszMenuName   = NULL;
    winclass.lpszClassName  = szWindowClass;
    winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassExW(&winclass);
}

//   PURPOSE: Saves instance handle and creates main window
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(
       szWindowClass, szTitle, (WS_OVERLAPPEDWINDOW|WS_VISIBLE),
       0, 0, 600, 600,
       NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  PURPOSE: Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    const int CELL_SIZE = 100;

    switch (message)
    {
    case WM_CREATE:
    {
        // mock of window center procedure
        SetWindowPos(hWnd, 0, 100, 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    } break;
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
        pMinMax->ptMinTrackSize.x = CELL_SIZE * 5;
        pMinMax->ptMinTrackSize.y = CELL_SIZE * 5;

    } break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        // redraw client area

        // we need to calculate center of client area
        RECT rc;
        if (GetClientRect(hWnd, &rc))
        {
            int width = rc.right - rc.left;
            int height = rc.bottom - rc.top;

            // calculate sides of rectangular gameboard
            int left = (width - CELL_SIZE * 3) / 2;
            int top = (height - CELL_SIZE * 3) / 2;
            int right = left + CELL_SIZE * 3;
            int bottom = top + CELL_SIZE * 3;
            
            Rectangle(hdc, left, top, right, bottom);

        }

        EndPaint(hWnd, &ps);
    } break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        // windows proccesses other messages 
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}