//
// Created by alex_ on 19.11.2021.
//

#include "Controller.h"
bool Controller::send(fromController dat) {
    _pModel_->receive(dat);
}
bool Controller::capture(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int sig = SIG_NOTHING;
    bool mouseMove = (message == WM_MOUSEMOVE);
    POINT p;
    GetCursorPos(&p);
    if (GetKeyState(VK_ESCAPE) & 0x8000){
        sig = SIG_ESC;
    } else
    if (GetKeyState(VK_SELECT) & 0x8000){
        sig = SIG_SET;
    } else
    if (GetKeyState(VK_UP) & 0x8000){
        sig = SIG_UP;
    } else
    if (GetKeyState(VK_RIGHT) & 0x8000){
        sig = SIG_RIGHT;
    } else
    if (GetKeyState(VK_LEFT) & 0x8000){
        sig = SIG_LEFT;
    } else
    if (GetKeyState(VK_DOWN) & 0x8000){
        sig = SIG_DOWN;
    } else
    return (this->send({sig, mouseMove, p}));
}

