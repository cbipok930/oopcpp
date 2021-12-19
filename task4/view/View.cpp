//
// Created by alex_ on 19.11.2021.
//

#include "View.h"
View::View(HWND *hWnd, HDC *hdc, MSG *msg, const Gdiplus::Bitmap &imgB, const Gdiplus::Bitmap &imgC,
           const Gdiplus::Bitmap &imgCv) {
    using namespace Gdiplus;
    _hWndP = hWnd;
    _hdcP = hdc;
    _boardImgP = imgB.Clone();
    _checkerImgP = imgC.Clone();
    _coverImgP = imgCv.Clone();
    _msgP = msg;
    _msg = "";
    _colorMatrixBlack = {
            0.16, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.16, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.16, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0, 0, 0, 0.0f, 1.0f};
    _colorMatrixWhite = {
            1.9, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.9, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.9, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0, 0, 0, 0.0f, 1.0f};
}
void View::drawChecker(Gdiplus::Graphics *g, Gdiplus::ImageAttributes *att1,
                       Gdiplus::ImageAttributes *att2, int pos) {
    int oY = FIELD_TOPLEFTY + 3 + (pos / 8) * 41.6;
    int oX = FIELD_TOPLEFTX + 3 + (pos % 8) * 41.6;
    g->DrawImage(_checkerImgP,
                 Gdiplus::Rect(oX, oY, _checkerImgP->GetWidth(), _checkerImgP->GetHeight()),
                 0, 0, _checkerImgP->GetWidth(), _checkerImgP->GetHeight(),
                 Gdiplus::UnitPixel, att1);
    g->DrawImage(_coverImgP, Gdiplus::Rect(oX, oY, _checkerImgP->GetWidth(), _checkerImgP->GetHeight()),
                 0, 0, _checkerImgP->GetWidth(), _checkerImgP->GetHeight(),
                 Gdiplus::UnitPixel, att2);
}
bool View::get(DataModel *dat) {
    _whiteCheckersPos = dat->userCheckersPos;
    _blackCheckersPos = dat->foeCheckersPos;
    _pointArea = dat->pointArea;
    _selArea = dat->selArea;
    _damkasPos = dat->damkasPos;
    _msg = dat->msg;
    delete dat;
    return true;
}

void View::show() {
    using namespace Gdiplus;
    RECT rect;
    GetWindowRect(*_hWndP, &rect);
    auto imAttWhite = new ImageAttributes;
    imAttWhite->SetColorKey(
            Color(0, 253, 0),
            Color(0, 255, 0),
            Gdiplus::ColorAdjustTypeDefault);
    imAttWhite->SetColorMatrices(&_colorMatrixWhite, nullptr);

    auto imAttBlack = new ImageAttributes;
    imAttBlack->SetColorKey(
            Color(0, 253, 0),
            Color(0, 255, 0),
            Gdiplus::ColorAdjustTypeDefault);
    imAttBlack->SetColorMatrices(&_colorMatrixBlack, nullptr);

    auto imAtt = new ImageAttributes;
    imAtt->SetColorKey(
            Color(0, 253, 0),
            Color(0, 255, 0),
            Gdiplus::ColorAdjustTypeDefault);

    auto result = new Bitmap(_boardImgP->GetWidth() + FIELD_OX, _boardImgP->GetHeight() + FIELD_OY);
    auto g = Graphics::FromImage(result);
    auto graphics = new Graphics(*_hdcP);
    g->DrawImage(_boardImgP, FIELD_OX, FIELD_OY);

    for (auto it = _whiteCheckersPos.begin(); it != _whiteCheckersPos.end(); it++){
        drawChecker(g, imAttWhite, imAtt, (*it));
    }
    for (auto it = _blackCheckersPos.begin(); it != _blackCheckersPos.end(); it++){
        drawChecker(g, imAttBlack, imAtt, (*it));
    }
    if (!_damkasPos.empty()){
        for (auto it = _damkasPos.begin(); it != _damkasPos.end(); it++){
            auto pen = new Pen(Color(255, 254, 32, 32));
            pen->SetWidth(6.0);
            auto rec = new Rect((FIELD_TOPLEFTX + (*it % 8) * 41.6) + 17, (FIELD_TOPLEFTY + (*it / 8) * 41.6) + 17,
                                6, 6);
            g->DrawEllipse(pen, *rec);
            delete pen;
            delete rec;
        }
    }
    if (_pointArea > -1){
        auto pen = new Pen(Color(200, 100, 20, 255));
        pen->SetWidth(2.0);
        auto rec = new Rect((FIELD_TOPLEFTX + (_pointArea % 8) * 41.6) + 1, (FIELD_TOPLEFTY + (_pointArea / 8) * 41.6) + 1,
                             40, 40);
        auto solidBrush = new SolidBrush(Color(50, 100, 20, 240));
        g->FillRectangle(solidBrush, (FIELD_TOPLEFTX + (_pointArea % 8) * 41.6) + 1, (FIELD_TOPLEFTY + (_pointArea / 8) * 41.6) + 1
                         , 40, 40);
        g->DrawRectangle(pen, *rec);
        delete pen;
        delete rec;
        delete solidBrush;
    }
    if (_selArea > -1){
        auto pen = new Pen(Color(200, 50, 200, 50));
        pen->SetWidth(2.0);
        auto rec = new Rect((FIELD_TOPLEFTX + (_selArea % 8) * 41.6) + 1, (FIELD_TOPLEFTY + (_selArea / 8) * 41.6) + 1,
                            40, 40);
        auto solidBrush = new SolidBrush(Color(50, 50, 180, 50));
        g->FillRectangle(solidBrush, (FIELD_TOPLEFTX + (_selArea % 8) * 41.6) + 1, (FIELD_TOPLEFTY + (_selArea / 8) * 41.6) + 1
                , 40, 40);
        g->DrawRectangle(pen, *rec);
        delete pen;
        delete rec;
        delete solidBrush;
    }
    graphics->ScaleTransform(BOARD_SCALE, BOARD_SCALE);
    graphics->DrawImage(result, 0, 0);
    delete imAttWhite;
    delete imAttBlack;
    delete imAtt;
    delete g;
    delete graphics;
    delete result;
    if (_msg == "Player 2 won" || _msg == "Player 1 won"){
        MessageBeep(MB_ICONINFORMATION);
        if (_msg == "Player 2 won")
            MessageBoxA(nullptr, "Game over", "Player 2 won", MB_OK | MB_ICONINFORMATION);
        else
            MessageBoxA(nullptr, "Game over", "Player 1 won", MB_OK | MB_ICONINFORMATION);
    }
}


