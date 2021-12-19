//
// Created by alex_ on 19.11.2021.
//

#include "Model.h"

#include <random>
void initChecker(checkersSet& set, Board& board, checkerPos& pos, bool side){
    auto pch = new checkerObject{side, false, pos};
    set.push_back(pch);
    board[pos] = pch;
}
checkerPos posFromIntsToChars(int row, int col){
    char let = char(col + int('A'));
    char dig = char(-1 * row + int('8'));
    return {let, dig};
}
void cordsToPosInts(const POINT p, int & row, int & col){
    col = (p.x - FIELD_TOPLEFTX * BOARD_SCALE) *
              double(8.0 / (FIELD_BOTTOMRIGHTX *BOARD_SCALE - FIELD_TOPLEFTX * BOARD_SCALE));
    row = (p.y - FIELD_TOPLEFTY * BOARD_SCALE) *
              double(8.0 / (FIELD_BOTTOMRIGHTY * BOARD_SCALE - FIELD_TOPLEFTY * BOARD_SCALE));
}
bool isWithinField(const POINT p){
    return (p.x >= FIELD_TOPLEFTX*BOARD_SCALE  && p.x <= FIELD_BOTTOMRIGHTX*BOARD_SCALE
    && p.y >= FIELD_TOPLEFTY*BOARD_SCALE && p.y <= FIELD_BOTTOMRIGHTY*BOARD_SCALE);
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
    _isFinal = false;
    _isSelected = false;
    _isUser = true;
    _isWhite = true;
    _isPvP = false;
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
bool Model::nextToPos(checkerPos p, checkerPos* pnext, int direction){
    checkerPos next = *pnext;
    switch(direction){
        case(0):
            next.let = (char)(p.let + 1); next.dig = (char)(p.dig + 1);break;
        case(1):
            next.let = (char)(p.let + 1);next.dig = (char)(p.dig - 1);break;
        case(2):
            next.let = (char)(p.let - 1);next.dig = (char)(p.dig - 1);break;
        case(3):
            next.let = (char)(p.let - 1);next.dig = (char)(p.dig + 1);break;
        default: return false;
    }
    *pnext = next;
    if (next.let < 'A' || next.let > 'H' || next.dig > '8' || next.dig < '1')
        return false;
    else
        return true;
}

void Model::possibleMoves(checkerPos pos, std::list<std::vector<StrikePath>> & posMoves) {
    int randomDir = 0 + (rand() % static_cast<int>(3 - 0 + 1));
    int dirStart = randomDir;
    do {
        StrikePath move = {nullptr, {0,0}};
        if (nextToPos(pos, &move.killerPosNew, dirStart)) {// not border
            if (_checkBoard[move.killerPosNew] == nullptr){ //free
                std::vector<StrikePath> free_vec;
                if((dirStart == 0  || dirStart == 3) && _isWhite && !_checkBoard[pos]->damka
                || (dirStart == 1 || dirStart == 2) && !_isWhite && !_checkBoard[pos]->damka
                || _checkBoard[pos]->damka)
                {
                free_vec.push_back(move);
                while (nextToPos(move.killerPosNew, &move.killerPosNew, dirStart) && _checkBoard[pos]->damka){
                    if (_checkBoard[move.killerPosNew] == nullptr)
                        free_vec.push_back(move);
                    else if (_checkBoard[move.killerPosNew]->user != _isUser){
                        StrikePath moveStrike = {nullptr, {0,0}};
                        if(nextToPos(move.killerPosNew, &moveStrike.killerPosNew, dirStart)) {
                            if (_checkBoard[moveStrike.killerPosNew] == nullptr) {
                                moveStrike.killed = _checkBoard[move.killerPosNew];
                                std::vector<StrikePath> strike_vec;
                                strike_vec.push_back(moveStrike);
                                posMoves.push_back(strike_vec);
                            }
                        }
                        break;
                    }
                    else
                        break;
                }
                posMoves.push_back(free_vec);
            }
        }
            else if (_checkBoard[move.killerPosNew]->user != _isUser){//enemy
                StrikePath moveStrike = {nullptr, {0,0}};
                if(nextToPos(move.killerPosNew, &moveStrike.killerPosNew, dirStart)) {
                    if (_checkBoard[moveStrike.killerPosNew] == nullptr) {
                        moveStrike.killed = _checkBoard[move.killerPosNew];
                        std::vector<StrikePath> strike_vec;
                        strike_vec.push_back(moveStrike);
                        posMoves.push_back(strike_vec);
                    }
                }
            }
        }
        dirStart = (dirStart + 1)%4;
    } while (dirStart != randomDir);
}
bool Model::botTurn() {
    std::map<checkerObject*, std::list<std::vector<StrikePath>>> movesForCheckers;
    std::vector<checkerObject*> tmpvec;
    for(auto & ch : _foeCheckers){
        tmpvec.push_back(ch);
    }
    std::shuffle(tmpvec.begin(), tmpvec.end(), std::mt19937(std::random_device()()));
    std::list<checkerObject*> tmplist;
    for(int i = 0; i < _foeCheckers.size(); i++){
        checkerObject* it = tmpvec[0];
        tmpvec.erase(tmpvec.cbegin());
        tmplist.push_back(it);
    }
    _foeCheckers = tmplist;
    for (auto & ch : _foeCheckers){
        std::list<std::vector<StrikePath>> moves;
        possibleMoves(ch->pos, moves);
        movesForCheckers[ch] = moves;
        for (auto & vec : moves){
            for (auto & move : vec){
                if ((move.killerPosNew.dig == '8' && _isWhite || move.killerPosNew.dig == '1' && !_isWhite) && !ch->damka){
                    if (move.killed != nullptr){
                        _checkBoard[move.killed->pos] = nullptr;
                        auto it = std::find(_userCheckers.begin(), _userCheckers.end(), move.killed);
                        _userCheckers.erase(it);
                        delete (*it);
                    }
                    _checkBoard[ch->pos] = nullptr;
                    ch->pos = move.killerPosNew;
                    _checkBoard[ch->pos] = ch;
                    if ((_isWhite && ch->pos.dig == '8' || !_isWhite && ch->pos.dig == '1') && !ch->damka){
                        ch->damka = true;
//                        std::cout << _checkerSelected <<" "<< ch->pos.let << ch->pos.dig << " is damka" << std::endl;
                    }
                    return true;
                }
                if (move.killed != nullptr){
                    _checkBoard[move.killed->pos] = nullptr;
                    auto it = std::find(_userCheckers.begin(), _userCheckers.end(), move.killed);
                    _userCheckers.erase(it);
                    delete (*it);
                    _checkBoard[ch->pos] = nullptr;
                    ch->pos = move.killerPosNew;
                    _checkBoard[ch->pos] = ch;
                    if ((_isWhite && ch->pos.dig == '8' || !_isWhite && ch->pos.dig == '1') && !ch->damka){
                        ch->damka = true;
//                        std::cout << _checkerSelected <<" "<< ch->pos.let << ch->pos.dig << " is damka" << std::endl;
                    }
                    return true;
                }
            }
        }
    }
  //  std::shuffle(_foeCheckers.begin(), _foeCheckers.end(), 321);
    for (auto & ch : _foeCheckers){
        std::list<std::vector<StrikePath>> moves = movesForCheckers[ch];
        for (auto & vec : moves){
            for (auto & move : vec) {
                _checkBoard[ch->pos] = nullptr;
                ch->pos = move.killerPosNew;
                _checkBoard[ch->pos] = ch;
                if (_isWhite && ch->pos.dig == '8' || !_isWhite && ch->pos.dig == '1'){
                    ch->damka = true;
                    std::cout << _checkerSelected <<" "<< ch->pos.let << ch->pos.dig << " is damka" << std::endl;
                }
                return true;
            }
        }
    }
    return true;
}
bool Model::playerTurn() {
    if (isWithinField(_inputSigs.mouseCords))
    {
        int col, row;
        cordsToPosInts(_inputSigs.mouseCords, row, col);
        checkerPos newPos = posFromIntsToChars(row, col);
        checkerObject* pCheckerClicked = _checkBoard[newPos];
//        std::cout << "Clicked at " << pCheckerClicked << std::endl;
        if (_isSelected)//checker's move
        {
            std::list<std::vector<StrikePath>> moves;
            possibleMoves(_checkerSelected->pos, moves);
            bool walk = false;
            for (auto & move : moves){
                for (auto & vt : move){
                    if (vt.killerPosNew.let == newPos.let && vt.killerPosNew.dig == newPos.dig){
                        if (vt.killed != nullptr){
                            _checkBoard[vt.killed->pos] = nullptr;
                            if (!vt.killed->user){
                                auto it = std::find(_foeCheckers.begin(), _foeCheckers.end(), vt.killed);
                                _foeCheckers.erase(it);
                                delete (*it);
                            }
                            else{
                                auto it = std::find(_userCheckers.begin(), _userCheckers.end(), vt.killed);
                                _userCheckers.erase(it);
                                delete (*it);
                            }
                        }
                        walk = true;
                        break;
                    }
                }
            }
            if ((pCheckerClicked == nullptr) && walk) {
                checkersSet::iterator it;
                if (_checkerSelected->user)
                    it = std::find(_userCheckers.begin(), _userCheckers.end(), _checkerSelected);
                else
                    it = std::find(_foeCheckers.begin(), _foeCheckers.end(), _checkerSelected);
                _checkBoard[_checkerSelected->pos] = nullptr;
                (*it)->pos = newPos;
                _checkBoard[newPos] = _checkerSelected;
                if (_isWhite && newPos.dig == '8' || !_isWhite && newPos.dig == '1'){
                    _checkerSelected->damka = true;
//                    std::cout << _checkerSelected <<" "<< newPos.let << newPos.dig << " is damka" << std::endl;
                }
                _isSelected = false;
                _checkerSelected = nullptr;
                return true;
            }
            else
                _isSelected = false;
        }
        else //choose checker
        {
            if (pCheckerClicked != nullptr){
                if ((pCheckerClicked->user && _isUser) || !(pCheckerClicked->user || _isUser)) {
                    _checkerSelected = pCheckerClicked;
                    _isSelected = true;
                }
            }
        }
        return false;
    }
    return false;
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
    if (_isFinishProc)
        return false;
    _msg = "";
    if (!_isFinal) {
        if (_foeCheckers.empty() || _userCheckers.empty()) {
            _msg = (_foeCheckers.empty()) ? "Player 1 won" : "Player 2 won";
            _isFinal = true;
            bool ret = this->send();
            return ret;
        }
        if (_isUser) {
            bool noMoves = true;
            for (auto &ch: _userCheckers) {
                std::list<std::vector<StrikePath>> moves;
                possibleMoves(ch->pos, moves);
                if (!moves.empty()) {
                    noMoves = false;
                    break;
                }
            }
            if (noMoves) {
                _isFinal = true;
                _msg = "Player 2 won";
                bool ret = this->send();
                return ret;
            }
        }
        if (!_isUser) {
            bool noMoves = true;
            for (auto &ch: _foeCheckers) {
                std::list<std::vector<StrikePath>> moves;
                possibleMoves(ch->pos, moves);
                if (!moves.empty()) {
                    noMoves = false;
                    break;
                }
            }
            if (noMoves) {
                _isFinal = true;
                _msg = "Player 1 won";
                bool ret = this->send();
                return ret;
            }
        }

        if (_inputSigs.isClicked) {
            _msg = "";
            _inputSigs.isClicked = false;
            _inputSigs.isKeyPressed = false;
            _inputSigs.isUpdateCords = false;
            if (_isPvP || _isUser) {
                if (playerTurn()) {
                    _isUser = !_isUser;
                    _isWhite = !_isWhite;
                    bool ret = this->send();
                    return ret;
                }
            }
        }
        if (!_isUser && !_isPvP) {
            _inputSigs.isClicked = false;
            _inputSigs.isKeyPressed = false;
            _inputSigs.isUpdateCords = false;
            botTurn();
            _isWhite = !_isWhite;
            _isUser = !_isUser;
        }
    }
    else{
        _inputSigs.isClicked = false;
        _inputSigs.isKeyPressed = false;
        _inputSigs.isUpdateCords = false;
    }
    bool ret = this->send();
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
    std::vector<int> damkasPos;
    for (auto it = _foeCheckers.begin(); it != _foeCheckers.end(); it++){
        int row = abs(int((*it)->pos.dig) - int('8'));
        int col = abs(int((*it)->pos.let) - int('A'));
        foePos.push_back(row * 8 + col);
        if ((*it)->damka)
            damkasPos.push_back(row * 8 + col);
    }
    for (auto it = _userCheckers.begin(); it != _userCheckers.end(); it++){
        int row = abs(int((*it)->pos.dig) - int('8'));
        int col = abs(int((*it)->pos.let) - int('A'));
        userPos.push_back(row * 8 + col);
        if ((*it)->damka)
            damkasPos.push_back(row * 8 + col);
    }
    if (isWithinField(_inputSigs.mouseCords) && _inputSigs.isUpdateCords)
    {
       int x, y;
       cordsToPosInts(_inputSigs.mouseCords, y, x);
       dm->pointArea = y * 8 + x;
   //     std::cout << dm->pointArea << std::endl;
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
    dm->damkasPos = damkasPos;
    return (_pView->get(dm));
}


