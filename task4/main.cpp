#include <iostream>
#include <cstdint>
#include "controller/Controller.h"
#include "view/View.h"
#include <objidl.h>
#include <vector>
#include <csignal>
#define WIDTH 700//116
#define HEIGHT 480//66
#define MOUSELEAVE      0x0001
#define MOUSEHOVER      0x0002
Controller* GetController(LONG_PTR dat){
    if (0 == dat) return nullptr;
    auto vec_dat = (std::vector<LONG_PTR>*)dat;
    auto controller = (Controller*)((*vec_dat)[2]);
    return controller;
}
View* GetView(LONG_PTR dat){
    if (0 == dat) return nullptr;
    auto vec_dat = (std::vector<LONG_PTR>*)dat;
    auto view = (View*)((*vec_dat)[0]);
    return view;
}
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    Controller* controller;
    View* view;
    switch(message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_MOUSEMOVE:
        case WM_MOUSEHOVER:
        case WM_KEYDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONDOWN:
            controller = GetController(GetWindowLongA(hWnd, GWLP_USERDATA));
            if (nullptr == controller) return 0;
            if (!controller->capture(hWnd, message, wParam, lParam)){
                PostQuitMessage(0);
                return 0;
            }
            view = GetView(GetWindowLongA(hWnd, GWLP_USERDATA));
            if (nullptr == view){
                return 0;
            }
            view->show();
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR commandLine, INT iCmdShow) {
    using namespace Gdiplus;
    DWORD appNameLen = 256;
    LPSTR appName[256] = {0};
    GetModuleFileNameA(nullptr, reinterpret_cast<LPSTR>(appName), appNameLen);
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
//     Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    WNDCLASSW wnd_class = {0};
    wnd_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wnd_class.hCursor = LoadCursor(nullptr, IDC_HAND);
    wnd_class.hInstance = hInstance;
    wnd_class.lpszClassName = L"MainWind";
    wnd_class.lpfnWndProc = MainWndProc;
    wnd_class.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    if (!RegisterClassW(&wnd_class)){
        MessageBeep(MB_ICONERROR);
        MessageBoxA(nullptr, "Failed to register class", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    HWND hwnd = CreateWindowExW(WS_EX_APPWINDOW, L"MainWind", reinterpret_cast<LPCWSTR>("Checkers"),
                               WS_OVERLAPPEDWINDOW /*WS_POPUP*/ | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
                    nullptr,
                    nullptr,
                    nullptr,
                    nullptr
                    );
    if (!hwnd){
        MessageBeep(MB_ICONERROR);
        MessageBoxA(nullptr, "Failed to get window handler", reinterpret_cast<LPCSTR>(appName), MB_OK | MB_ICONERROR);
        return 1;
    }
    MSG msg;
    HDC hDc = GetDC(hwnd);

    auto board = new Gdiplus::Bitmap(L"..\\dat\\shashechnaya-doska.jpg");
    auto checker = new Gdiplus::Bitmap(L"..\\dat\\draughts64.png");
    if (board->GetLastStatus() != Gdiplus::Ok || checker->GetLastStatus() != Ok){
        MessageBeep(MB_ICONERROR);
        MessageBoxA(nullptr, "Corrupt data", reinterpret_cast<LPCSTR>(appName), MB_OK | MB_ICONERROR);
        return 1;
    }

    auto view = new View(&hwnd, &hDc, &msg, *board, *checker);
    auto model = new Model(view);
    auto controller = new Controller(model);
    auto vecToProc = new std::vector<LONG_PTR>;
    vecToProc->push_back((LONG_PTR)view);
    vecToProc->push_back((LONG_PTR)model);
    vecToProc->push_back((LONG_PTR)controller);
    LONG_PTR toProc = (LONG_PTR)vecToProc;
    SetWindowLongA(hwnd, GWLP_USERDATA, toProc);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        UpdateWindow(hwnd);
    }
    GdiplusShutdown(gdiplusToken);
    ReleaseDC(hwnd, hDc);
    DeleteObject(&board);
    return msg.wParam;
}
