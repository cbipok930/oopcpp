//
// Created by alex_ on 19.11.2021.
//

#include "Controller.h"
int64_t Controller::capture(POINT mouseCords) {
    UINT message;

    switch (message)
    {
        case WM_KEYDOWN: {
            if (GetKeyState(VK_ESCAPE))
                return -1;
            if (GetKeyState(VK_UP))
                send({SIG_UP, mouseCords});
            if (GetKeyState(VK_RIGHT))
                send({SIG_RIGHT, mouseCords});
            if (GetKeyState(VK_LEFT))
                send({SIG_LEFT, mouseCords});
            if (GetKeyState(VK_DOWN))
                send({SIG_DOWN, mouseCords});
            if (GetKeyState(VK_SPACE))
                send({SIG_SET, mouseCords});
            else
                send({NOTHING, mouseCords});
        }
            break;


    }
    return 0;
}
void Controller::send(fromController dat) {
    _pModel_->receive(dat);
}

bool Controller::start(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //test
    if (GetKeyState(VK_UP) & 0x8000)
        std::cout << "UP\n";
    if (GetKeyState(VK_RIGHT) & 0x8000)
        std::cout << "RIGHT\n";
    POINT p;
    GetCursorPos(&p);
    switch (message)
    {
        case WM_MOUSEMOVE:
            std::cout << p.x << "  " << p.y <<'\n';
            break;
        default:
            break;
    }
    return true;
    //enstest
    /*int i = 0;
    POINT p;
    GetCursorPos(&p);
    uint64_t key = 0;
    if(this->capture(p) < 0)
        return false;
    else
        return true;
        */
}
