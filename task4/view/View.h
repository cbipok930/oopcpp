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
#define DOLLAR 36
#define SHARP 35
struct point{
    int  x;
    int  y;
};
typedef point resolution;
struct pixel{
    point cord;
    int mark;
};
typedef std::vector<pixel> pixels;
void SetWindow(SHORT width, SHORT height);

class View {
public:
    View(HWND hWnd, MSG msg, SHORT width, SHORT height) : _width_(width), _height_(height){
        _hWnd_ = hWnd;
        _msg_ = msg;
        _display_ = new wchar_t[_width_ * _height_];
        pDisplay = &_display_[0];
    }
    void setDisplay(pixels *pNewDat);
    const wchar_t* pDisplay;
    resolution getResolution();
private:
    HWND _hWnd_;
    MSG _msg_;
    SHORT _width_;
    SHORT _height_;
    wchar_t* _display_;
};


#endif //TASK4_VIEW_H
