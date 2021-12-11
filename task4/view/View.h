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
#define FIELD_OX 0
#define FIELD_OY 0
#define FIELD_TOPLEFTX (16 + FIELD_OX)
#define FIELD_TOPLEFTY (16 + FIELD_OY)
#define FIELD_BOTTOMRIGHTX (349 + FIELD_OX)
#define FIELD_BOTTOMRIGHTY (349 + FIELD_OY)
#define BOARD_SCALE 1

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
    int pointArea;
    int selArea;
};
class View {
public:
    View(HWND *hWnd, HDC *hdc, MSG *msg, const Gdiplus::Bitmap &imgB, const Gdiplus::Bitmap &imgC,
         const Gdiplus::Bitmap &imgCv);
    bool get(DataModel* dat);
    void show();
private:
    Gdiplus::Image* _boardImgP;
    Gdiplus::Image* _checkerImgP;
    Gdiplus::Image* _coverImgP;
    Gdiplus::ColorMatrix _colorMatrixBlack;
    Gdiplus::ColorMatrix _colorMatrixWhite;
    HWND* _hWndP;
    HDC* _hdcP;
    MSG* _msgP;
    std::vector<int> _whiteCheckersPos;
    std::vector<int> _blackCheckersPos;
    int _pointArea;
    int _selArea;

    void drawChecker(Gdiplus::Graphics *g, Gdiplus::ImageAttributes* att1,
                     Gdiplus::ImageAttributes* att2, int pos);
};


#endif //TASK4_VIEW_H
