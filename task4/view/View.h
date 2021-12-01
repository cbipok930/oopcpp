//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_VIEW_H
#define TASK4_VIEW_H
#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <windows.h>
#include <gdiplus.h>
#define FIELD_OX 200
#define FIELD_OY 100
#define FIELD_TOPLEFTX (16 + FIELD_OX + 3)
#define FIELD_TOPLEFTY (16 + FIELD_OY + 3)
#define FIELD_BOTTOMRIGHTX (349 + FIELD_OX)
#define FIELD_BOTTOMRIGHTY (349 + FIELD_OY)

class Model;
class DataModel{
public:
    DataModel() = default;
    bool updateCords;
    bool keyPressed;
    std::string msg;
    POINT mouseCords;
    bool _menu;
    std::vector<int> userCheckersPos;
    std::vector<int> foeCheckersPos;
};
class View {
public:
    View(HWND *hWnd, HDC *hdc, MSG *msg, const Gdiplus::Bitmap &imgB, const Gdiplus::Bitmap &imgC);
    bool get(DataModel* dat);
    void show();
private:
    Gdiplus::Image* _boardImgP;
    Gdiplus::Image* _checkerImgP;
    Gdiplus::ColorMatrix _colorMatrixBlack;
    HWND* _hWndP;
    HDC* _hdcP;
    MSG* _msgP;
    std::vector<int> _whiteCheckersPos;
    std::vector<int> _blackCheckersPos;
};


#endif //TASK4_VIEW_H
