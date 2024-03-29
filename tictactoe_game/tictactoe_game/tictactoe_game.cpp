#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <math.h>
#include "game_area.h"
#include "resource.h"


// Global Variables
HINSTANCE hInst;
#define szWindowClass _T("WINCLASS1")           // the main window class name
#define szTitle _T("Tictactoe Game")
const int CELL_SIZE = 100;
HBRUSH hbPlayer1;
HBRUSH hbPlayer2;
HICON hXicon;
HICON hOicon;
HPEN hWinnerLinePen;
HPEN hDefaultLinePen;
Player playerTurn = Player::player_1;
GameArea area;

// Forward declarations of functions included in this code module
ATOM                RegisterMainWindowClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL                GetGameboardRect(HWND, RECT*);
void                DrawLine(HDC, int, int, int, int, bool);
int                 GetCellIndex(HWND, int, int);
BOOL                GetCellRect(HWND, int, RECT*);
void                DisplayWinnerAsMessageBox(BoardState, HWND);
void                ShowTurn(HWND, HDC);
void                DrawCenteredIcon(HDC, RECT*, Player);
void                DrawWinnerLineComb(HWND, HDC, BoardState, const int*);

// ENTRY POINT
int WINAPI wWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPWSTR    lpCmdLine,
                   int       nCmdShow)
{
    // Perform application initialization
    RegisterMainWindowClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

//  PURPOSE: Registers the window class.
ATOM RegisterMainWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXW winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);

    winclass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    winclass.lpfnWndProc    = MainWndProc;
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
    // save global app context
    hInst = hInstance;

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
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

        // load images to app
        hXicon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_X));
        hOicon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_O));
    
        const int widthOfWinnerPen = 10;
        const int widthOfDefaultPen = 1;
        hWinnerLinePen = CreatePen(PS_SOLID, widthOfWinnerPen, RGB(255, 0, 0));
        hDefaultLinePen = CreatePen(PS_SOLID, widthOfWinnerPen, RGB(0, 0, 0));

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
           
            // fill gameBoard by colors corespond to current situation on the table
            RECT rectCell;
            const Player* currentArea = area.GetArea();
            for (int i = 0; i < 9; i++)
            {
                if (GetCellRect(hWnd, i, &rectCell))
                {
                    if (*(currentArea + i) != Player::unknown)
                    {
                        FillRect(hdc, &rectCell, (*(currentArea + i) == Player::player_1) ? hbPlayer1 : hbPlayer2);
                        DrawCenteredIcon(hdc, &rectCell, *(currentArea+i));
                    }
                    else
                    {
                        FillRect(hdc, &rectCell, GetStockBrush(WHITE_BRUSH));
                    }
                }
            }

        }

        ShowTurn(hWnd, hdc);

        EndPaint(hWnd, &ps);
    } break;
    case WM_LBUTTONDOWN:
    {
        // get mouse position
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        // compute number of cell where click event was happend
        int index = GetCellIndex(hWnd, xPos, yPos);
        
        // if current cell is occupied
        if (area.IsOccupied(index))
            break;

        // write player turn for save current state of table
        area.makeStep(playerTurn, index);
    
        // draw specific cell's area refer to current playerturn
        HDC hdc = GetDC(hWnd);
        if (hdc)
        {
            RECT cellRect;
            GetCellRect(hWnd, index, &cellRect);
            
            FillRect(hdc, &cellRect, (playerTurn == Player::player_1) ? hbPlayer1 : hbPlayer2);
            DrawCenteredIcon(hdc, &cellRect, playerTurn);

            // draw text who is turn under gameboard
            ShowTurn(hWnd, hdc);
           
            ReleaseDC(hWnd, hdc);
        }
        
        // Rotate order
        playerTurn = (playerTurn == Player::player_1) ? Player::player_2: Player::player_1;

        const int* indexesOfWinnerComb;
        BoardState winner;
        indexesOfWinnerComb = area.VictoryCheck(winner);
        // do the check - maybe anyone win
        if (winner == BoardState::player1_win)
        {
            DrawWinnerLineComb(hWnd, hdc, BoardState::player1_win, indexesOfWinnerComb);
            DisplayWinnerAsMessageBox(BoardState::player1_win, hWnd);
        }
        else if (winner == BoardState::player2_win)
        {
            DrawWinnerLineComb(hWnd, hdc, BoardState::player2_win, indexesOfWinnerComb);
            DisplayWinnerAsMessageBox(BoardState::player2_win, hWnd);
        }
        else if (winner == BoardState::draw)
        {
            DisplayWinnerAsMessageBox(BoardState::draw, hWnd);
        }

    } break;
    case WM_DESTROY:
        // release resources
        DeleteObject(hbPlayer1);
        DeleteObject(hbPlayer2);
        DeleteObject(hWinnerLinePen);
        DestroyIcon(hXicon);
        DestroyIcon(hOicon);

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

    SelectObject(hdc, hDefaultLinePen);

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

void DisplayWinnerAsMessageBox(BoardState state, HWND hWnd)
{
    const WCHAR* temp;

    if (state == BoardState::player1_win)
        temp = L"Player1 wins!\nStart new game?";
    else if (state == BoardState::player2_win)
        temp = L"Player2 wins!\nStart new game?";
    else
        temp = L"Draw!\nStart new game?";

    EnableWindow(hWnd, FALSE);

    int msgboxID = MessageBox(
        NULL,
        temp,
        _T("End of the game"),
        MB_ICONINFORMATION | MB_YESNO
    );

    if (msgboxID == IDYES)
    { // start new game
        area.Clean();
        playerTurn = Player::player_1;

        // generate WM_PAINT to the right way
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
    }
    else if (msgboxID == IDNO)
    { // exit from game
        PostMessage(hWnd, WM_CLOSE, 0, 0);
    }

    EnableWindow(hWnd, TRUE);
    SetForegroundWindow(hWnd);
}

void ShowTurn(HWND hWnd, HDC hdc)
{
    const WCHAR* playerStr;
    // if current player 2 then next step is for player1
    if (playerTurn == Player::player_2)
        playerStr = L"Player1 turn";
    else if ((playerTurn == Player::player_1) && area.IsEmpty())
        playerStr = L"Player1 turn";
    else
        playerStr = L"Player2 turn";

    RECT textRect;
    if (GetClientRect(hWnd, &textRect))
    {
        textRect.top = textRect.bottom - 50;
        DrawText(hdc, playerStr, lstrlen(playerStr), &textRect, DT_CENTER);
    }

}

void DrawCenteredIcon(HDC hdc, RECT *cellRect, Player owner)
{
    // i dont know why 32px is actually size of icon
    // that has in resources 80x80px size
    const int iconWidth = 32;
    const int iconHeight = 32;

    // (x, y) is coordinates of left-upper corner
    int x = cellRect->left + ((cellRect->right - cellRect->left) - iconWidth) / 2;
    int y = cellRect->top + ((cellRect->bottom - cellRect->top) - iconHeight) / 2;


    DrawIcon(hdc, x, y,
        (owner == Player::player_1) ? hXicon : hOicon);
}

void DrawWinnerLineComb(HWND hWnd, HDC hdc, BoardState state, const int *indexesOfWinnerComb)
{
    RECT startCellRect, endCellRect;
    int startx, starty, endx, endy;

    if (GetCellRect(hWnd, indexesOfWinnerComb[0], &startCellRect) &&
        GetCellRect(hWnd, indexesOfWinnerComb[2], &endCellRect))
    {
        startx = ((startCellRect.right - startCellRect.left) / 2) + startCellRect.left;
        starty = ((startCellRect.bottom - startCellRect.top) / 2) + startCellRect.top;
        endx = ((endCellRect.right - endCellRect.left) / 2) + endCellRect.left;
        endy =  ((endCellRect.bottom - endCellRect.top) / 2) + endCellRect.top;
        
        SelectObject(hdc, hWinnerLinePen);
        MoveToEx(hdc, startx, starty, NULL);
        LineTo(hdc, endx, endy);
    }

}