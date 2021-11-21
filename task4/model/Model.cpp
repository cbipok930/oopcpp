//
// Created by alex_ on 19.11.2021.
//

#include "Model.h"
Model::Model(View *pv) {
    _pView_ = pv;
    _one_.cord.y = 2;
    _one_.cord.x = 2;
    _one_.mark = SHARP;
    _cursor_ = {{0, 0}, DOLLAR};
}

void Model::receive(fromController dat) {
/*   if(dat == SIG_UP)
       _one_.cord.y = ((_one_.cord.y - 1) >= 0) ? (_one_.cord.y - 1) : (_pView_->getResolution().y - 1);
   else {
   if(dat == SIG_DOWN)
       _one_.cord.y = ((_one_.cord.y + 1) < _pView_->getResolution().y) ? (_one_.cord.y + 1) : (0);
   else {
   if(dat == SIG_LEFT)
       _one_.cord.x = ((_one_.cord.x - 1) >= 0) ? (_one_.cord.x - 1) : (_pView_->getResolution().x - 1);
   else {
   if(dat == SIG_RIGHT)
       _one_.cord.x = ((_one_.cord.x + 1) < _pView_->getResolution().x) ? (_one_.cord.x + 1) : (0);
   else {
   if(dat == SIG_SET)
       _one_.mark = (_one_.mark == DOLLAR) ? (SHARP) : (DOLLAR);
                }
            }
        }
    }
   if (dat != NOTHING)
        this->update(_one_);
        */
    auto vec = new pixels;
    _cursor_.cord.x = dat.mouse.x * _pView_->getResolution().x/ SYSRES_W;
    _cursor_.cord.y = dat.mouse.y * _pView_->getResolution().y/ SYSRES_H;
    if(dat.sig == SIG_SET)
        _cursor_.mark = (_one_.mark == DOLLAR) ? (SHARP) : (DOLLAR);
    vec->push_back(_cursor_);
    _pView_->setDisplay(vec);
}

void Model::update(pixels *pNewDat) {
    _pView_->setDisplay(pNewDat);
}

