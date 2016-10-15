#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"


#define mode_max 1

int main()
{
    //vars
    int mode = mode_max;
    char mod[20], *message;
    long Time = 0, T0 = 0;
    vector<pixel> pixs;
    //vars
    message = txInputBox("¬ведите название группы:");
    strcat(message,".txt");
    pixs = load_file(message);
    txCreateWindow(800,500, true);
    txSetFillColour(RGB(50,50,50));
    txClear();
    Time = TIME;
    T0 = Time;
    txBegin();
    while(!KEY(VK_ESCAPE))
    {
        txClear();
        sprintf(mod, "MODE:%d,TIME:%d\0", mode, ((TIME - T0)/10)%1000);
        txTextOut(500, 30, mod);
        for(int i=0;i<pixs.size();i++){ for(int x=pixs[i].x;x<pixs[i].x+4;x++){ for(int y=pixs[i].y;y<pixs[i].y+4;y++) txSetPixel(x, y,pixs[i].color); } }
        if (txMouseButtons() & 1)
        {
            if(mode == 0){ pixs.insert(pixs.end(), pixel(txMouseX(),txMouseY(),RGB(0,255,0))); }
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
            pixs.insert(pixs.end(), pixel(-1,-1,RGB(255,0,0)));
            txClear();
        }
        txSleep(10);
    }
    txEnd();
    save_file(message, pixs);
    return 0;
}
