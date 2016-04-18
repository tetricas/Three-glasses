#include "Circle.h"


class MGlass : public MCircle
{
public:
    virtual void MPaint(HWND, HDC);
    void Check(int, int, HWND);
};

void MGlass::MPaint(HWND hwnd, HDC hdc)
{
    KillTimer(hwnd, 1);
    SetTimer(hwnd, 1, 1, NULL);

    POINT six[]={{xp+30, yp-60},//a
                 {xp+15, yp-75},//b
                 {xp-15, yp-75},//c
                 {xp-30, yp-60},//d
                 {xp-15, yp-45},//p
                 {xp+15, yp-45}};//l

    POINT man1[]={{xp-30, yp-60},//d
                  {xp-40, yp+30},//e
                  {xp-15, yp+45},//f
                  {xp-15, yp-45}};//p

    POINT man2[]={{xp+30, yp-60},//a
                  {xp+40, yp+30},//k
                  {xp+15, yp+45},//g
                  {xp+15, yp-45}};//l

    Rectangle(hdc, xp-15, yp+45, xp+15, yp-45);
    Polygon(hdc,six, 6);
    Polygon(hdc,man1, 4);
    Polygon(hdc,man2, 4);
}

void MGlass::Check(int x, int y, HWND hwnd)
{
    if (xp-40<x && x<xp+40 && yp-45<y && y<yp+40)
        MessageBox(hwnd,"You win!", "Congratulate!", MB_OK);
    else
       MessageBox(hwnd,"You lose!", "Haha", MB_OK);
;
}

