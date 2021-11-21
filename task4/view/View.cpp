//
// Created by alex_ on 19.11.2021.
//

#include "View.h"
void SetWindow(SHORT width, SHORT height){
    _COORD coord{};
    coord.X = width;
    coord.Y = height;
    _SMALL_RECT Rect{};
    Rect.Top = 0;
    Rect.Left = 0;
    height--; width--;
    Rect.Bottom = height;
    Rect.Right = width;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

void View::setDisplay(pixels *pNewDat) {
    for (int i = 0; i < _height_; ++i) {
        for (int j = 0; j < _width_; ++j) {
            _display_[i * _width_ + j] = ' ';
        }
    }
    for (auto & i : *pNewDat) {
        if (i.cord.y >= 0 && i.cord.y < _height_ && i.cord.x >= 0 && i.cord.x < _width_)
            _display_[i.cord.y * _width_ + i.cord.x] = i.mark;
    }

}

resolution View::getResolution() {
    return {(int)_width_, (int)_height_};
}
