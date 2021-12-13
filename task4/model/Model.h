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
#include <list>
#include <algorithm>
#include "../view/View.h"
#define SIG_UP 0
#define SIG_RIGHT 1
#define SIG_DOWN 2
#define SIG_LEFT 3
#define SIG_SET 4
#define SIG_ESC 5
#define SIG_NOTHING -1
#define SIG_CLICK 6
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
    bool damka;
    checkerPos pos;
};
typedef std::map<checkerPos, checkerObject* > Board;
typedef std::list<checkerObject* > checkersSet;
struct fromController{
    int sig;
    bool mouseMove;
    POINT mouse;
};
struct InputSigs{
    bool isUpdateCords;
    bool isKeyPressed;
    bool isClicked;
    int keyType;
    POINT mouseCords;
};
struct StrikePath{
    checkerObject* killed;
    checkerPos killerPosNew;
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
    checkerObject* _checkerSelected;
    InputSigs _inputSigs;
    bool _isFinishProc;
    bool _isMenu;
    bool _isPvP;
    bool _isSelected;
    bool _isUser;
    bool _isWhite;
    std::string _msg;

    bool changeState();
    bool send();
    bool playerTurn();
    void possibleMoves(checkerPos pos, std::list<std::vector<StrikePath>> & posMoves);
    /*
     * direction vals:
     * 0 = right up
     * 1 = right down
     * 2 = left down
     * 3 = left up
     * */
    bool strikeSingle(checkerPos enemy, int direction);
    /*
   * direction vals:
   * 0 = right up
   * 1 = right down
   * 2 = left down
   * 3 = left up
   * */
    static bool nextToPos(checkerPos p, checkerPos* pnext ,int direction);
};


#endif //TASK4_MODEL_H
