#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
    movsCtrl mvs;
    message = txInputBox("¬ведите название группы:", NULL, "");
    if(message[0] == 0) return 1;
    strcat(message,".txt");
    mvs = movsCtrl(message);
    txCreateWindow(800,500, true);
    txSetFillColour(RGB(50,50,50));
    txTextCursor(false);
    txClear();
    Time = TIME;
    T0 = Time;
    txBegin();
    while(!KEY(VK_ESCAPE))
    {
        txClear();
        for(int k=0;k<mvs.movs.size();k++)
        {
            for(int i=0;i<mvs.movs[k].pix.size();i++)
            {
                for(double x=mvs.movs[k].pix[i].x;x<mvs.movs[k].pix[i].x+4;x++)
                {
                    //printf("X:%d;Y:%d",mvs.movs[k].pix[i].x ,mvs.movs[k].pix[i].y);
                    for(double y=mvs.movs[k].pix[i].y;y<mvs.movs[k].pix[i].y+4;y++)
                    txSetPixel(x, y,mvs.movs[k].pix[i].color);
                }
            }
            mvs.movs[k].do_move();
        }
        sprintf(mod, "TIME:%d;\0", ((TIME - T0)/10)%1000);
        txTextOut(500, 30, mod);
        txSleep(10);
    }
    txEnd();
    return 0;
}
