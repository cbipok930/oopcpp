//
// Created by alex_ on 19.11.2021.
//

#include "Model.h"
void initChecker(checkersSet& set, Board& board, checkerPos& pos, bool side){
    auto pch = new checkerObject{side, pos};
    set[pos] = *pch;
    std::cout << &set[pos] << std::endl;
    board[pos] = &set[pos];
}
checkerPos posFromDigTab(int row, int col){
    char let = char(col + int('A'));
    char dig = char(-1 * row + int('8'));
    return {let, dig};
}
Model::Model(View *pv) {
    _pView = pv;
    _inputSigs.isUpdateCords = false;
    _inputSigs.isKeyPressed = false;
    _inputSigs.keyType = SIG_NOTHING;
    _inputSigs.mouseCords = {0, 0};
    _inputSigs.isClicked = false;

    _checkerSelected= nullptr;
    _isFinishProc = false;
    _isMenu = false;
    _isSelected = false;
    _isUser = true;
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
    _inputSigs.isUpdateCords = dat.mouseMove;
    _inputSigs.mouseCords = dat.mouse;
switch (dat.sig) {
    case SIG_ESC:
        _isFinishProc = true;
        return false;
    case SIG_SET:
        _inputSigs.isKeyPressed = true;
        _inputSigs.keyType = SIG_SET;
        return (this->changeState());
    case SIG_CLICK:
        _inputSigs.isClicked = true;
        return (this->changeState());
    default:
        return (this->changeState());
    }
}
bool Model::changeState() {
    std::string keyString;
    switch (_inputSigs.keyType) {
        case SIG_SET:
            _msg = "Enter pressed\n";
            break;
        default:
            break;
    }
    if (_inputSigs.isClicked)
    {
        if (_isUser)
        {
            if (_inputSigs.mouseCords.x >= FIELD_TOPLEFTX && _inputSigs.mouseCords.x <= FIELD_BOTTOMRIGHTX
                && _inputSigs.mouseCords.y >= FIELD_TOPLEFTY && _inputSigs.mouseCords.y <= FIELD_BOTTOMRIGHTY)
            {
                int col = (_inputSigs.mouseCords.x - FIELD_TOPLEFTX) *
                          double(8.0 / (FIELD_BOTTOMRIGHTX - FIELD_TOPLEFTX));
                int row = (_inputSigs.mouseCords.y - FIELD_TOPLEFTY) *
                          double(8.0 / (FIELD_BOTTOMRIGHTY - FIELD_TOPLEFTY));
                checkerPos newPos = posFromDigTab(row, col);
                checkerObject* pchk = _checkBoard[{newPos.let, newPos.dig}];
                if (_isSelected)
                {
                    std::cout << "Move\n";
                    if (pchk == nullptr) {
                        auto it = _userCheckers[_checkerSelected->pos];
                        it.pos = newPos;

                        _isSelected = false;
                        _checkerSelected = nullptr;
                    }
                    else
                        _isSelected = false;
                }
                else
                {
                    std::cout << "Take\n";
                    if (pchk != nullptr){
                        if (pchk->user) {
                            _checkerSelected = pchk;
                            _isSelected = true;
                        }
                    }
                    else
                        std::cout << pchk;
                }
            }
        }
    }
    // send to View
    bool ret = this->send();
    // set defaults
    _msg = "";
    _inputSigs.isClicked = false;
    _inputSigs.isKeyPressed = false;
    _inputSigs.isUpdateCords = false;
    return ret;
}

bool Model::send() {
    auto dm = new DataModel;
    dm->msg = _msg;
    dm->keyPressed = _inputSigs.isKeyPressed;
    dm->updateCords = _inputSigs.isUpdateCords;
    dm->mouseCords = _inputSigs.mouseCords;
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

    if (_inputSigs.mouseCords.x >= FIELD_TOPLEFTX && _inputSigs.mouseCords.x <= FIELD_BOTTOMRIGHTX
    && _inputSigs.mouseCords.y >= FIELD_TOPLEFTY && _inputSigs.mouseCords.y <= FIELD_BOTTOMRIGHTY)
    {
        int x = (_inputSigs.mouseCords.x - FIELD_TOPLEFTX) * double(8.0/ (FIELD_BOTTOMRIGHTX - FIELD_TOPLEFTX));
        int y = (_inputSigs.mouseCords.y - FIELD_TOPLEFTY) * double(8.0/ (FIELD_BOTTOMRIGHTY - FIELD_TOPLEFTY));
        dm->pointArea = y * 8 + x;
        std::cout << dm->pointArea << std::endl;
    }
    else dm->pointArea = -1;

    if (_isSelected){
        int row = abs(int(_checkerSelected->pos.dig) - int('8'));
        int col = abs(int(_checkerSelected->pos.let) - int('A'));
        dm->selArea = row * 8 + col;
    }
    else dm->selArea = -1;
    dm->foeCheckersPos = foePos;
    dm->userCheckersPos = userPos;
    return (_pView->get(dm));
}



