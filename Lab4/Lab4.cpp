#define _CRT_SECURE_NO_WARNINGS
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE

#endif
#define OEMRESOURCE
#define RGB(r,g,b)
#define _USE_MATH_DEFINES
#define IDM_EXIT 100

#include <math.h>
#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
    std::allocator<TCHAR> > String;
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("Lab4");

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;
    HFONT h_font;            /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    h_font = CreateFont(-13, 0, 0, 0,
        FW_NORMAL, 0,
        0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Times New Roman");
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_SHIELD);
    wincl.hIconSm = LoadIcon(NULL, IDI_ERROR);
    wincl.hCursor = LoadCursor(NULL, IDC_APPSTARTING);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW, 3);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("Operation systems"),       /* Title Text */
        WS_OVERLAPPEDWINDOW | WS_BORDER | WS_THICKFRAME | WS_VSCROLL, /* default window */
        200,       /* Windows decides the position */
        0,       /* where the window ends up on the screen */
        700,                 /* The programs width */
        800,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);
    SendMessage(hwnd, WM_SETFONT, (WPARAM)h_font, TRUE);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    int x, y;
    static int sx, sy;
    static int symbolCaret = 0;
    static HMETAFILE hmf;
    
    SIZE strSize;
    static String str;
    
    switch (message)
    {
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
   
    case WM_RBUTTONDOWN:
        hdc = GetDC(hwnd);
        SetBkColor(hdc, RGB(197, 88, 129));
        TextOut(hdc, 220, 300, L"Натиснуто на праву кнопку миші  ", 30);
        ReleaseDC(hwnd, hdc);
        break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        SetBkColor(hdc, RGB(197, 88, 129));
        TextOut(hdc, 220, 300, L"Натиснуто на ліву кнопку миші         ", 29);
        ReleaseDC(hwnd, hdc);
        break;
    case WM_MBUTTONDOWN:
        hdc = GetDC(hwnd);
        SetBkColor(hdc, RGB(197, 88, 129));
        TextOut(hdc, 220, 300, L"Натиснуто на колечко мишки     ", 26);
        ReleaseDC(hwnd, hdc);
        break;
    case WM_CREATE:
        hdc = GetDC(hwnd);
        CreateCaret
        (
            hwnd,		// дескриптор окна владельца каретки
            NULL,	// дескриптор точечного рисунка для формы каретки
            2,		// ширина каретки
            17 		// высота каретки
        );
        ReleaseDC(hwnd, hdc);
        break;
    case WM_MOUSEMOVE:
        WORD xPos, yPos, nSize;
        TCHAR szBuf[80];
        xPos = LOWORD(lParam);
        yPos = HIWORD(lParam);
        hdc = GetDC(hwnd);
        nSize = wsprintf(szBuf, TEXT("(%d, %d)"), xPos, yPos);
        SetBkColor(hdc, RGB(197, 88, 129));
        SetTextColor(hdc, RGB(255, 255, 255));
        TextOut(hdc, 270, 350, szBuf, nSize);
        ReleaseDC(hwnd, hdc);
        break;
    case WM_CHAR:
        if (wParam == 8)
        {
            if (str.size() + symbolCaret > 0)
                str.erase(str.size() + symbolCaret - 1, 1);
        }
        else
            str.insert(str.size() + symbolCaret, 1, (TCHAR)wParam);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
      
        hdc = BeginPaint(hwnd, &ps);
        GetTextExtentPoint32(hdc, str.data(), str.size() + symbolCaret, &strSize);
        SetCaretPos(strSize.cx + 2, 50);
        SetBkColor(hdc, RGB(197, 88, 129));
        TextOut(hdc, 3, 50, str.data(), str.size());
        ShowCaret(hwnd);
        
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 37:
            if (str.size() + symbolCaret != 1)
                symbolCaret -= 1;
            break;
        case 39:
            if (str.size() + symbolCaret != str.size())
                symbolCaret += 1;
            break;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}