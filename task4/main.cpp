#pragma once
#include <iostream>
#include <cstdint>
#include "controller/Controller.h"
#include "view/View.h"
#include <gdiplus.h>
#include <objidl.h>
#include <vector>
#define WIDTH 640//116
#define HEIGHT 480//66

VOID OnPaint(HDC hdc)
{
    using namespace Gdiplus;
    Graphics graphics(hdc);
    Pen      pen(Color(255, 0, 0, 255));
    graphics.DrawLine(&pen, 0, 0, 200, 100);
}
/*LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                         WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch(message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            OnPaint(hdc);
            EndPaint(hWnd, &ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc*/
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
//    LONG_PTR dat = GetWindowLongA(hWnd, GWLP_USERDATA);
//    if (!dat) { return DefWindowProc(hWnd, message, wParam, lParam);}
//
//    auto vec_dat = (std::vector<LONG_PTR>*)dat;
//    View* view = (View*)((*vec_dat)[0]);
//    Controller* controller = (Controller*)((*vec_dat)[2]);
//    if (!controller->capture(hWnd, message, wParam, lParam))
//        PostQuitMessage(0);
    if (message == WM_CREATE){
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    else if (message == WM_NCCREATE)
        return DefWindowProc(hWnd, message, wParam, lParam);
    else
    {
        switch(message)
        {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                LONG_PTR dat = GetWindowLongA(hWnd, GWLP_USERDATA);
                auto vec_dat = (std::vector<LONG_PTR>*)dat;
                View* view = (View*)((*vec_dat)[0]);
                Controller* controller = (Controller*)((*vec_dat)[2]);
                if (!controller->capture(hWnd, message, wParam, lParam))
                    PostQuitMessage(0);
                return 0;
        }
    }
   /* switch(message)
    {
        case WM_KEYDOWN:
            if (!controller->capture(hWnd, message, wParam, lParam))
                PostQuitMessage(0);
            return 0;
        case WM_MOUSEMOVE:
            if (!controller->capture(hWnd, message, wParam, lParam))
                PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_USER:
            if (!controller->capture(hWnd, message, wParam, lParam))
                PostQuitMessage(0);
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }*/
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
    using namespace Gdiplus;
    HWND hwnd;
    MSG msg;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    WNDCLASS wnd;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
    wnd.lpszMenuName = 0;
    wnd.style = 0;
    wnd.hbrBackground = 0;
    wnd.lpfnWndProc = MainWndProc;
    wnd.hInstance = hInstance;
    wnd.lpszClassName = reinterpret_cast<LPCSTR>(L"MainWnd");

    RegisterClass(&wnd);


   /* hwnd = CreateWindow(
            TEXT("MainWnd"),   // window class name
            TEXT("Getting Started"),  // window caption
            WS_OVERLAPPEDWINDOW,      // window style
            CW_USEDEFAULT,            // initial x position
            CW_USEDEFAULT,            // initial y position
            CW_USEDEFAULT,            // initial x size
            CW_USEDEFAULT,            // initial y size
            NULL,                     // parent window handle
            NULL,                     // window menu handle
            hInstance,                // program instance handle
            NULL);                    // creation parameters*/
    hwnd = CreateWindowExA(
            WS_OVERLAPPEDWINDOW,           // Optional window styles.
            reinterpret_cast<LPCSTR>(L"MainWnd"),         // Window class
            reinterpret_cast<LPCSTR>(L"Getting Started"), // Window text
            WS_OVERLAPPEDWINDOW,           // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,       // Parent window
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL      // Additional application data
            );
    DispatchMessage(&msg);
    auto view = new View(hwnd, msg, WIDTH, HEIGHT);
    auto model = new Model(view);
    auto controller = new Controller(model);

    auto vecToProc = new std::vector<LONG_PTR>;
    vecToProc->push_back((LONG_PTR)view);
    vecToProc->push_back((LONG_PTR)model);
    vecToProc->push_back((LONG_PTR)controller);

    LONG_PTR toProc = (LONG_PTR)vecToProc;
    auto test = (std::vector<LONG_PTR>*)toProc;
    SetWindowLongA(hwnd, GWLP_USERDATA, toProc);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
    return 0;
   /* auto v = new View(0, 0, WIDTH, HEIGHT);
    auto m = new Model(v);
    auto c = new Controller(m);
    SetWindow(WIDTH * 2, HEIGHT);
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    while(c->capture()) {
        WriteConsoleOutputCharacter(hConsole, reinterpret_cast<LPCSTR>(v->pDisplay), WIDTH * HEIGHT * 2, {0, 0 }, &dwBytesWritten);
    }
    return 0;*/
}