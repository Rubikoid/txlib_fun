#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
    movsCtrl mvs;
    message = txInputBox("¬ведите название группы:");
    strcat(message,".txt");
    mvs = movsCtrl(message);
    txCreateWindow(800,500, true);
    txSetFillColour(RGB(50,50,50));
    txTextCursor(false);
    txClear();
    Time = TIME;
    T0 = Time;
    int move = 0;
    txBegin();
    while(!KEY(VK_ESCAPE))
    {
        txClear();
        for(int k=0;k<mvs.movs.size();k++)
        {
            for(int i=0;i<mvs.movs[k].pix.size();i++)
            {
                for(int x=mvs.movs[k].pix[i].x;x<mvs.movs[k].pix[i].x+4;x++)
                {
                    //printf("X:%d;Y:%d",mvs.movs[k].pix[i].x ,mvs.movs[k].pix[i].y);
                    for(int y=mvs.movs[k].pix[i].y;y<mvs.movs[k].pix[i].y+4;y++)
                    txSetPixel(x, y,mvs.movs[k].pix[i].color);
                }
            }
            mvs.movs[k].do_move();
        }
        sprintf(mod, "TIME:%d;X:%d,Y:%d\0", ((TIME - T0)/10)%1000, mvs.movs[0].pix[1].x, mvs.movs[0].pix[1].y);
        txTextOut(500, 30, mod);
        txSleep(100);
    }
    txEnd();
    return 0;
}
