#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"

void drow(mv mvm);
void resetCol();

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
    txTextCursor(false);
    resetCol();
    txClear();
    Time = TIME;
    T0 = Time;
    txBegin();
    while(!KEY(VK_ESCAPE))
    {
        resetCol();
        txClear();
        sprintf(mod, "TIME:%d;DiffX:%f;DiffY:%f\0", ((TIME - T0)/10)%1000, txMouseX() - mvs.movs[0].rollCX, txMouseY() - mvs.movs[0].rollCY);
        txTextOut(500, 30, mod);
        for(int k=0;k<mvs.movs.size();k++)
        {
            drow(mvs.movs[k]);
            mvs.movs[k].do_move();
        }
        txSleep(10);
    }
    txEnd();
    return 0;
}


void drow(mv mvm)
{
    for(int i=0;i<mvm.pix.size();i++)
    {
        txSetColor(mvm.pix[i].color,1);
        txSetFillColor(mvm.pix[i].color);
        txCircle(mvm.pix[i].x,mvm.pix[i].y,3);
        /*for(double x=mvm.pix[i].x;x<mvm.pix[i].x+4;x++)
        {
            for(double y=mvm.pix[i].y;y<mvm.pix[i].y+4;y++) txSetPixel(x, y,mvm.pix[i].color);
        }*/
    }
}

void resetCol()
{
    txSetFillColour(RGB(50,50,50));
    txSetColor(TX_WHITE, 1);
}

