//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_CONTROLLER_H
#define TASK4_CONTROLLER_H
#pragma once
#include <cstdint>
#include "../model/Model.h"
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75
class Controller {
public:
    Controller(Model* m) : _pModel_(m){
    }
    bool start(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    Model* _pModel_;
    int64_t capture(POINT mouseCords);
    void send(fromController dat);
};


#endif //TASK4_CONTROLLER_H
