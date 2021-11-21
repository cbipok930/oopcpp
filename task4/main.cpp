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
    LONG_PTR dat = GetWindowLongA(hWnd, GWLP_USERDATA);
    if (!dat) { return DefWindowProc(hWnd, message, wParam, lParam);}
    auto vec_dat = (std::vector<LONG_PTR>*)dat;
    View* view = (View*)((*vec_dat)[0]);
    Controller* controller = (Controller*)((*vec_dat)[2]);
    switch(message)
    {
        case WM_KEYDOWN:
            controller->start(hWnd, message, wParam, lParam);
            return 0;
        case WM_MOUSEMOVE:
            controller->start(hWnd, message, wParam, lParam);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
    using namespace Gdiplus;
    HWND hwnd;
    MSG msg;
    WNDCLASS wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = MainWndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = TEXT("MainWnd");

    RegisterClass(&wndClass);


    hwnd = CreateWindow(
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
            NULL);                    // creation parameters
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
    while(c->start()) {
        WriteConsoleOutputCharacter(hConsole, reinterpret_cast<LPCSTR>(v->pDisplay), WIDTH * HEIGHT * 2, {0, 0 }, &dwBytesWritten);
    }
    return 0;*/
}