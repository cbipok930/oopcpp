//
// Created by alex_ on 19.11.2021.
//

#ifndef TASK4_MODEL_H
#define TASK4_MODEL_H
#pragma once
#include <cstdint>
#include "../view/View.h"
#define SIG_UP 0
#define SIG_RIGHT 1
#define SIG_DOWN 2
#define SIG_LEFT 3
#define SIG_SET 4
#define NOTHING 99999999
#define SYSRES_H 1080
#define SYSRES_W 1920
struct fromController{
    uint64_t sig;
    POINT mouse;
};
class Model {
public:
    explicit Model(View* pv);
    void receive(fromController dat);

private:
    View* _pView_;
    pixel _one_;
    pixel _cursor_;
    void update(pixels *pNewDat);
};


#endif //TASK4_MODEL_H
