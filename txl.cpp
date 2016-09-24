#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include <vector>

using namespace std;

#define mode_max 1
#define TIME     GetTickCount()/100
#define KEY      GetAsyncKeyState

int irand(int min, int max)
{
    return rand() % max + min;
}

class pixel
{
    public:
    int x;
    int y;
    COLORREF color;
    pixel(int X, int Y, COLORREF col)
    {
        x = X;
        y = Y;
        color = col;
    }
    pixel()
    {

    }
};

int main()
{
    //vars
    FILE *fl;
    vector<pixel> pixs(0);
    int stat = 0, mode = mode_max;
    char mod[20];
    long Time = 0, T0 = 0;
    //vars
    //file
    fl = fopen("data.txt", "r");
    while(stat != EOF)
    {
        int x,y,r,g,b;
        stat = fscanf(fl,"%d,%d;%d,%d,%d\n", &x, &y, &r, &g, &b);
        pixs.insert(pixs.end(), pixel(x,y,RGB(r,g,b)));
    }
    fclose(fl);
    //file
    txCreateWindow(800,500, true);
    txSetFillColour(RGB(50,50,50));
    txClear();
    Time = TIME;
    T0 = Time;
    //pixs.insert(pixs.end(), pixel(10,10,RGB(255,0,0)));
    while(!KEY(VK_ESCAPE))
    {
        if(mode == mode_max) txClear();
        txBegin();
        sprintf(mod, "MODE:%d,TIME:%d\0", mode, ((TIME - T0)/10)%1000);
        txTextOut(500, 30, mod);
        for(int i=0;i<pixs.size();i++){ for(int x=pixs[i].x;x<pixs[i].x+4;x++){ for(int y=pixs[i].y;y<pixs[i].y+4;y++) txSetPixel(x, y,pixs[i].color); } }
        if (txMouseButtons() & 1)
        {
            if(mode == 0) pixs.insert(pixs.end(), pixel(txMouseX(),txMouseY(),RGB(0,255,0)));
            else if(mode == 1) ;
        }
        else if (KEY(VK_SPACE) && TIME - Time > 2)
        {
            mode++;
            if(mode>mode_max) mode = 0;
            Time = TIME;
            txClear();
        }
        else if (KEY(VK_F1))
        {
            pixs.clear();
            pixs.insert(pixs.end(), pixel(0,0,RGB(255,0,0)));
            txClear();
        }
        txEnd();
    }
    //file
    fl= fopen("data.txt", "w");
    for(int i=0;i<pixs.size()-1;i++){ fprintf(fl, "%d,%d;%d,%d,%d\n", pixs[i].x, pixs[i].y, GetRValue(pixs[i].color), GetGValue(pixs[i].color), GetBValue(pixs[i].color)); }
    fclose(fl);
    //file
    return 0;
}
