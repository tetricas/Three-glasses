#include <windows.h>

class MDot
{
protected:
    int xp, yp;

public:
    MDot(){};
    void  ChangeX(int, bool, bool&, int);
    virtual void MPaint(HWND, HDC);
};

void  MDot::ChangeX(int x, bool side, bool& move, int level)
{
    if(!side)
    {
        if(xp<x)
            xp+=level;
    }
    else if(side)
    {
        if(xp>x)
            xp-=level;
    }
    if(xp<(x+level+1)&&xp>(x-level-1))
    {
        xp=x;
        move=false;
    }
}

void MDot::MPaint(HWND hwnd, HDC hdc)
{
    KillTimer(hwnd, 1);
    SetTimer(hwnd, 1, 100, NULL);
    SetPixel(hdc, xp, yp, RGB(0xff, 0, 0));

}
