#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <math.h>


// Global Variables:
 HINSTANCE hInst;                                // current instance
#define szWindowClass _T("WINCLASS1")            // the main window class name
#define szTitle _T("Tictactoe Game")
const int CELL_SIZE = 100;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL                GetGameboardRect(HWND, RECT*);
void                DrawLine(HDC, int, int, int, int, bool);

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
    winclass.hbrBackground  = (HBRUSH)(GetStockObject(GRAY_BRUSH));
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

    switch (message)
    {
    case WM_CREATE:
    {
        // mock of window center procedure
        SetWindowPos(hWnd, 0, 100, 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    } break;
    case WM_GETMINMAXINFO:
    {
        // disallow window make smaller than
        MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
        pMinMax->ptMinTrackSize.x = CELL_SIZE * 5;
        pMinMax->ptMinTrackSize.y = CELL_SIZE * 5;

    } break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        RECT rect;
        // redraw client area
        if (GetGameboardRect(hWnd, &rect))
        {
            // draw gameboard rectangle
            FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

            // draw horizontal lines
            DrawLine(hdc, rect.left, rect.top + CELL_SIZE, rect.right, rect.top + CELL_SIZE, TRUE);
            DrawLine(hdc, rect.left, rect.top + CELL_SIZE * 2, rect.right, rect.top + CELL_SIZE * 2, TRUE);

            // draw vertical lines
            DrawLine(hdc, rect.left + CELL_SIZE, rect.top, rect.left + CELL_SIZE, rect.bottom, FALSE);
            DrawLine(hdc, rect.left + CELL_SIZE * 2, rect.top, rect.left + CELL_SIZE * 2, rect.bottom, FALSE);

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

BOOL GetGameboardRect(HWND hWnd, RECT *pRect)
{
    // we need to calculate center of client area
    RECT rc;
    if (GetClientRect(hWnd, &rc))
    {
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;

        // calculate sides of rectangular gameboard
        pRect->left = (width - CELL_SIZE * 3) / 2;
        pRect->top = (height - CELL_SIZE * 3) / 2;
        pRect->right = pRect->left + CELL_SIZE * 3;
        pRect->bottom = pRect->top + CELL_SIZE * 3;
        return TRUE;
    }

    SetRectEmpty(pRect);
    return FALSE;
}

void DrawLine(HDC hdc, int startx, int starty, int endx, int endy, bool isHorizontal)
{
    const double SIZE_OF_PADDING = 0.03; // 3%
    double padding = sqrt(pow((double)endx-startx, 2) + pow((double)endy-starty, 2)) * SIZE_OF_PADDING;

    if (isHorizontal)
    {
        MoveToEx(hdc, startx + padding, starty, NULL);
        LineTo(hdc, endx - padding, endy);
    }
    else
    {
        MoveToEx(hdc, startx, starty + padding, NULL);
        LineTo(hdc, endx, endy - padding);
    }
}

