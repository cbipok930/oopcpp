//
// Created by alex_ on 19.11.2021.
//

#include "View.h"
View::View(HWND *hWnd, HDC *hdc, MSG *msg, const Gdiplus::Bitmap &imgB, const Gdiplus::Bitmap &imgC) {
    using namespace Gdiplus;
    _hWndP = hWnd;
    _hdcP = hdc;
    _boardImgP = imgB.Clone();
    _checkerImgP = imgC.Clone();
    _msgP = msg;
    _colorMatrixBlack = {
            0.33f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.23f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.23f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

bool View::get(DataModel *dat) {
    _whiteCheckersPos = dat->userCheckersPos;
    _blackCheckersPos = dat->foeCheckersPos;
    if(dat->keyPressed){
        std::cout << dat->msg << std::endl;
    }
    if(dat->updateCords){
        std::cout << dat->mouseCords.x << " " << dat->mouseCords.y << std::endl;
    }
    return true;
}

void View::show() {
    using namespace Gdiplus;
    auto imAtt = new ImageAttributes;
    imAtt->SetColorKey(
            Color(254, 254, 254),
            Color(255, 255, 255),
            ColorAdjustTypeBitmap);

    auto imAttBlack = new ImageAttributes;
    imAttBlack->SetColorKey(
            Color(254, 254, 254),
            Color(255, 255, 255),
            Gdiplus::ColorAdjustTypeDefault);
    imAttBlack->SetColorMatrices(&_colorMatrixBlack, nullptr);

    auto result = new Bitmap(_boardImgP->GetWidth() + FIELD_OX, _boardImgP->GetHeight() + FIELD_OY);
    auto g = Graphics::FromImage(result);
    auto graphics = new Graphics(*_hdcP);
    g->DrawImage(_boardImgP, FIELD_OX, FIELD_OY);
    for (auto it = _whiteCheckersPos.begin(); it != _whiteCheckersPos.end(); it++){
        int oY = FIELD_TOPLEFTY + ((*it) / 8) * 41.6;
        int oX = FIELD_TOPLEFTX + ((*it) % 8) * 41.6;
        g->DrawImage(_checkerImgP,
                     Rect(oX, oY, _checkerImgP->GetWidth(), _checkerImgP->GetHeight()),
                     0, 0, _checkerImgP->GetWidth(), _checkerImgP->GetHeight(),
                     Gdiplus::UnitPixel, imAtt);
    }
    for (auto it = _blackCheckersPos.begin(); it != _blackCheckersPos.end(); it++){
        int oY = FIELD_TOPLEFTY + ((*it) / 8) * 41.6;
        int oX = FIELD_TOPLEFTX + ((*it) % 8) * 41.6;
        g->DrawImage(_checkerImgP,
                     Rect(oX, oY, _checkerImgP->GetWidth(), _checkerImgP->GetHeight()),
                     0, 0, _checkerImgP->GetWidth(), _checkerImgP->GetHeight(),
                     Gdiplus::UnitPixel, imAttBlack);
    }
    graphics->DrawImage(result, 0, 0);
    delete imAtt;
    delete imAttBlack;
    delete g;
    delete graphics;
    delete result;
}
