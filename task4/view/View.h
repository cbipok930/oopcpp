//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_VIEW_H
#define TASK4_VIEW_H
#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>
#define ID_GLOB_BOOL 0
#define ID_BOOL_KP 0
#define ID_BOOL_MM 1
#define ID_GLOB_KPMSG 1
#define ID_GLOB_MMMSG 2
class Model;
class DataModel{
public:
    DataModel() = default;
    bool updateCords;
    bool keyPressed;
    std::string msg;
    POINT mouseCords;
};
class View {
public:
    View(HWND hWnd, MSG msg, SHORT width, SHORT height) : _width_(width), _height_(height){
        _hWnd_ = hWnd;
        _msg_ = msg;
    }
    bool get(DataModel* dat);
private:
    HWND _hWnd_;
    MSG _msg_;
    SHORT _width_;
    SHORT _height_;
    wchar_t* _display_;
};


#endif //TASK4_VIEW_H
