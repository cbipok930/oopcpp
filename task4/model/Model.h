//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_MODEL_H
#define TASK4_MODEL_H
#pragma once
#include <cstdint>
#include <map>
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
struct checkPos{
    char let;
    char dig;
};
struct checkerObject{
    bool user;
    checkPos pos;
};
typedef std::map<>
struct fromController{
    int sig;
    bool mouseMove;
    POINT mouse;
};
class Model {
public:
    Model(View* pv) : _finishProc(false),
                      _updateCords(false),
                      _updateKey(false),
                      _keyPressed(SIG_NOTHING),
                      _mouseCords({0,0})
                      {

    }
    bool receive(fromController dat);

private:
    bool _finishProc;
    bool _updateCords;
    bool _updateKey;
    int _keyPressed;
    POINT _mouseCords;

    bool changeState();
//    View* _pView_;
//    pixel _one_;
//    pixel _cursor_;
//    void update(pixels *pNewDat);
};


#endif //TASK4_MODEL_H
