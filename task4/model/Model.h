//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_MODEL_H
#define TASK4_MODEL_H
#pragma once
#include <cstdint>
#include <map>
#include <vector>
#include <set>
#include "../view/View.h"
#define SIG_UP 0
#define SIG_RIGHT 1
#define SIG_DOWN 2
#define SIG_LEFT 3
#define SIG_SET 4
#define SIG_ESC 5
#define SIG_NOTHING -1
#define SYSRES_H 1080
#define SYSRES_W 1920
struct checkerPos{
    char let;
    char dig;
    bool operator < (const checkerPos& pos) const{
        if ( let < pos.let )
            return true;
        if ( let == pos.let &&  dig < pos.dig )
            return true;
        return false;
    }
};
struct checkerObject{
    bool user;
    checkerPos pos;
};
typedef std::map<checkerPos, checkerObject* > Board;
typedef std::map<checkerPos, checkerObject> checkersSet;
struct fromController{
    int sig;
    bool mouseMove;
    POINT mouse;
};
class Model {
public:
    Model(View* pv);
    bool receive(fromController dat);

private:
    View* _pView;
    Board _checkBoard;
    checkersSet _foeCheckers;
    checkersSet _userCheckers;
    bool _finishProc;
    bool _menu;
    bool _updateCords;
    bool _keyPressed;
    int _keyType;
    POINT _mouseCords;

    bool changeState();
    bool send(DataModel* dat);
};


#endif //TASK4_MODEL_H
