#include "Dot.h"

class MCircle: public MDot
{
protected:
    int mas[3];
    int xc,level;
    bool side, move, bobj1, bobj2, obj_side;
    int k;
    int change_x;

public:
    int count;
    bool circ;

    MCircle();
    void Level(int);
    void Size(int, int, int);
    void Timer(HWND, MCircle&, MCircle&);
    virtual void MPaint(HWND, HDC);
};

MCircle::MCircle()
{
    move=false;
    side=false;
    obj_side=false;
    bobj1=false;
    bobj2=false;
    circ=true;
    count=1000;
    k=0;
    level=1;
}
void MCircle::Level(int l)
{
    level=l;
}

void MCircle::Size(int x , int y, int n)
{
    for(int i =0; i<3; ++i)
        mas[i]=x/4+i*x/4;

    xp=mas[n-1];
    yp=y/2;
}

void MCircle::Timer(HWND hwnd, MCircle &obj1, MCircle &obj2)
{
    srand(time(NULL));
        if(count<25&&!move)
        {
            circ=false;
            bobj1=false;
            bobj2=false;

            xc=mas[k];
            int c=k;
            k=rand()%3;
            if(k==c && k%2==0 && count%2==0)
                k=1;
            else if(k==c && k%2==0 &&count%2==1)
                k=3;
            else if(k==c && k%2==1 && count%2==0)
                k=2;
            count++;

            if(xc>=mas[k])
                side=true;
            else
                side=false;

            move=true;

            if(obj1.xp==mas[k])
            {
                change_x=xc;
                bobj1=true;
            }
            if(obj2.xp==mas[k])
            {
                change_x=xc;
                bobj2=true;
            }
        }
        if(move)
        {
            ChangeX(mas[k], side, move, level);
            if(side)
                obj_side=false;
            else
                obj_side=true;
            if(bobj1)
                obj1.ChangeX(change_x, obj_side, move, level);
            if(bobj2)
                obj2.ChangeX(change_x, obj_side, move, level);
            InvalidateRect(hwnd, NULL, TRUE);
        }
}

void MCircle::MPaint(HWND hwnd, HDC hdc)
{
    if(circ)
    {
        KillTimer(hwnd, 1);
        SetTimer(hwnd, 1, 1, NULL);
        HBRUSH hBrush;
        hBrush=CreateSolidBrush(RGB(0,200,0));
        SelectObject(hdc,hBrush);
        Ellipse(hdc, xp+15, yp+15, xp-15, yp-15);
    }
}
