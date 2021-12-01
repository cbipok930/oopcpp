//
// Created by alex_ on 19.11.2021.
//

#include "Model.h"
void initChecker(checkersSet& set, Board& board, checkerPos& pos, bool side){
    auto pch = new checkerObject{side, pos};
    set[pos] = *pch;
    board[pos] = &set[pos];
}
Model::Model(View *pv) {
    _pView = pv;
    _finishProc = false;
    _updateCords = false;
    _keyPressed = false;
    _menu = false;
    _keyType = SIG_NOTHING;
    _mouseCords = {0, 0};
    _msg = "";
    for (char l = 'A'; l <= 'H'; l++) {
        for (char d = '1'; d <= '8'; d++) {
            checkerPos pos = {l, d};
            if (d >= '6') {
                if (d == '7') {
                    std::set<char> i = {'A', 'C', 'E', 'G'};
                    if (i.count(l) <= 0)_checkBoard[pos] = nullptr;
                    else initChecker(_foeCheckers, _checkBoard, pos, false);
                } else {
                    std::set<char> i = {'B', 'D', 'F', 'H'};
                    if (i.count(l) <= 0) _checkBoard[pos] = nullptr;
                    else initChecker(_foeCheckers, _checkBoard, pos, false);
                }
            } else if (d <= '3') {
                if (d == '2') {
                    std::set<char> i = {'B', 'D', 'F', 'H'};
                    if (i.count(l) <= 0)_checkBoard[pos] = nullptr;
                    else initChecker(_userCheckers, _checkBoard, pos, true);
                } else {
                    std::set<char> i = {'A', 'C', 'E', 'G'};
                    if (i.count(l) <= 0) _checkBoard[pos] = nullptr;
                    else initChecker(_userCheckers, _checkBoard, pos, true);
                }
            }
            else _checkBoard[pos] = nullptr;
        }
    }
}
bool Model::receive(fromController dat) {
_updateCords = dat.mouseMove;
_mouseCords = dat.mouse;
switch (dat.sig) {
    case SIG_ESC:
        _finishProc = true;
        return false;
    case SIG_SET:
        _keyPressed = true;
        _keyType = SIG_SET;
        return (this->changeState());
    default:
        return (this->changeState());
    }
}
bool Model::changeState() {
    std::string keyString;
    switch (_keyType) {
        case SIG_SET:
            _msg = "Enter pressed\n";
            break;
        default:
            break;
    }
    // send to View
    bool ret = this->send();
    // set defaults
    _msg = "";
    _keyPressed = false;
    _updateCords = false;
    return ret;
}

bool Model::send() {
    auto dm = new DataModel;
    dm->msg = _msg;
    dm->keyPressed = _keyPressed;
    dm->updateCords = _updateCords;
    dm->mouseCords = _mouseCords;
    std::vector<int> foePos;
    std::vector<int> userPos;
    for (auto it = _foeCheckers.begin(); it != _foeCheckers.end(); it++){
        int row = abs(int(it->first.dig) - int('8'));
        int col = abs(int(it->first.let) - int('A'));
        foePos.push_back(row * 8 + col);
    }
    for (auto it = _userCheckers.begin(); it != _userCheckers.end(); it++){
        int row = abs(int(it->first.dig) - int('8'));
        int col = abs(int(it->first.let) - int('A'));
        userPos.push_back(row * 8 + col);
    }
    dm->foeCheckersPos = foePos;
    dm->userCheckersPos = userPos;
    return (_pView->get(dm));
}



