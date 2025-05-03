#include "pch.h"
#include <shellapi.h>

void CreateControls(HWND hWnd)
{
    WPARAM font = (WPARAM)CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                     CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");

    HWND longText = CreateWindowEx(0, "STATIC", LONG_MESSAGE, WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 30, 400, 200, hWnd, NULL, NULL, NULL);

    int btnFlags = WS_CHILD | WS_VISIBLE | BS_FLAT;
    HWND btn1 = CreateWindowEx(0, "BUTTON", BUTTON1_TEXT, btnFlags, 25, 150, 100, 30, hWnd, (HMENU)1, NULL, NULL);
    HWND btn2 = CreateWindowEx(0, "BUTTON", BUTTON2_TEXT, btnFlags, 170, 150, 100, 30, hWnd, (HMENU)2, NULL, NULL);
    HWND btn3 = CreateWindowEx(0, "BUTTON", BUTTON3_TEXT, btnFlags, 320, 150, 100, 30, hWnd, (HMENU)3, NULL, NULL);

    SendMessage(longText, WM_SETFONT, font, TRUE);
    SendMessage(btn1, WM_SETFONT, font, TRUE);
    SendMessage(btn2, WM_SETFONT, font, TRUE);
    SendMessage(btn3, WM_SETFONT, font, TRUE);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateControls(hWnd);
        break;
    case WM_COMMAND:
        plugin::Events::initRwEvent += [wParam]()
        {
            if (LOWORD(wParam) == 1)
                ShellExecute(NULL, "open", BUTTON1_LINK, NULL, NULL, SW_SHOWNORMAL);
            else if (LOWORD(wParam) == 2)
                ShellExecute(NULL, "open", BUTTON2_LINK, NULL, NULL, SW_SHOWNORMAL);
            else if (LOWORD(wParam) == 3)
                ShellExecute(NULL, "open", BUTTON3_LINK, NULL, NULL, SW_SHOWNORMAL);
        };
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void ShowPopupWindow()
{
    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = MODNAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);

    RegisterClass(&wc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int xPos = (screenWidth - WINDOW_WIDTH) / 2;
    int yPos = (screenHeight - WINDOW_HEIGHT) / 2;

    HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, MODNAME, MODNAME, WS_OVERLAPPED | WS_SYSMENU, xPos, yPos, WINDOW_WIDTH,
                               WINDOW_HEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hWnd == NULL)
        return;

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}