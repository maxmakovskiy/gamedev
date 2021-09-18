#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <math.h>

enum player {
    player_1,
    player_2
};

// Global Variables:
 HINSTANCE hInst;                                // current instance
#define szWindowClass _T("WINCLASS1")            // the main window class name
#define szTitle _T("Tictactoe Game")
const int CELL_SIZE = 100;
HBRUSH hbPlayer1;
HBRUSH hbPlayer2;
player playerTurn = player_1;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL                GetGameboardRect(HWND, RECT*);
void                DrawLine(HDC, int, int, int, int, bool);
int                 GetCellIndex(HWND, int, int);
BOOL                GetCellRect(HWND, int, RECT*);

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
        
        // create solid brush for drawing in certain cell
        hbPlayer1 = CreateSolidBrush(RGB(255, 153, 255));
        hbPlayer2 = CreateSolidBrush(RGB(102, 255, 178));
       
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
    case WM_LBUTTONDOWN:
    {
        // get mouse position
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        // compute number of cell where click event was happend
        int index = GetCellIndex(hWnd, xPos, yPos);
       
        HDC hdc = GetDC(hWnd);
        if (hdc)
        {
            RECT cellRect;
            GetCellRect(hWnd, index, &cellRect);

            FillRect(hdc, &cellRect, (playerTurn == player_1) ? hbPlayer1 : hbPlayer2);

            ReleaseDC(hWnd, hdc);
        }
        
        // Rotate order
        playerTurn = (playerTurn == player_1) ? player_2: player_1;

    } break;
    case WM_DESTROY:
        // release resources
        DeleteObject(hbPlayer1);
        DeleteObject(hbPlayer2);

        PostQuitMessage(0);
        break;
    default:
        // windows proccesses other messages 
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// PURPOSE: define sides of game board
BOOL GetGameboardRect(HWND hWnd, RECT *pRect)
{
    // we need to calculate center of client area
    RECT rc;
    if (GetClientRect(hWnd, &rc))
    {
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;

        // calculate coordinates of upper-left and lower-right corners of rectangular gameboard
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

int GetCellIndex(HWND hWnd, int xPos, int yPos)
{
    // index = -1 - cursor is moving outside the board
    // index = [0;8] - cursor in board area
    POINT pt;
    pt.x = xPos;
    pt.y = yPos;
    RECT rect;

    // get sides of gameboard
    if (GetGameboardRect(hWnd, &rect))
    {
        if (PtInRect(&rect, pt))
        {
            // MAGIC CALCULATION:
            // 1. normalise coordinates if point in gameboard area
            xPos = pt.x - rect.left;
            yPos = pt.y - rect.top;
            // 2. calculate column and row numbers
            int column = xPos / CELL_SIZE;
            int row = yPos / CELL_SIZE;
            // 3. calculate cell number
            return column + row * 3;
        }
    }

    // outside of gameboard area
    return -1;
}

BOOL GetCellRect(HWND hWnd, int index, RECT* rect)
{
    RECT gameboardRect;

    SetRectEmpty(rect);

    if (index == -1)
        return FALSE;
    
    if (GetGameboardRect(hWnd, &gameboardRect))
    {
        // convert index to (x,y) coordinates of cell's upper-left corner in range [0;2] - x; [0;2] - y 
        int x = index % 3; 
        int y = index / 3;
        
        // calculate upper-left corner coordinates using gameboard coordinates and size of one cell
        rect->left = gameboardRect.left + CELL_SIZE * x + 1; // make offset by 1
        rect->top = gameboardRect.top + CELL_SIZE * y + 1;   // for maintain gameboard's lines
        // calculate lower-right corner coordinates using coordinates of upper-left corner
        rect->right = rect->left + CELL_SIZE - 1;
        rect->bottom = rect->top + CELL_SIZE - 1;
    }

    return TRUE;
}
