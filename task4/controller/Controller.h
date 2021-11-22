//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_CONTROLLER_H
#define TASK4_CONTROLLER_H
#pragma once
#include <cstdint>
#include "../model/Model.h"
class Controller {
public:
    Controller(Model* m) : _pModel_(m){
    }
    bool capture(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    Model* _pModel_;
    bool send(fromController dat);
};
#endif //TASK4_CONTROLLER_H
