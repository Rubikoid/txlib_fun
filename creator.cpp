#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"


#define mode_max 3

void drow(vector<pixel> pixs);
void resetCol();

int main()
{
    //vars
    int mode = mode_max;
    char mod[20], *message;
    long Time = 0, T0 = 0;
    pixCtrl pixCt;
    //vars
    message = txInputBox("¬ведите название группы:", NULL, "");
    if(message[0] == 0) return 1;
    strcat(message,".txt");
    txCreateWindow(800,500, true);
    pixCt = pixCtrl(message);
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
        sprintf(mod, "MODE:%d,TIME:%d\0", mode, ((TIME - T0)/10)%1000);
        txTextOut(500, 30, mod);
        for(int i=0; i<pixCt.pixs.size(); i++) drow(pixCt.pixs[i]);
        if (txMouseButtons() & 1)
        {
            if(mode == 0){ pixCt.pixs[0].insert(pixCt.pixs[0].end(), pixel(txMouseX(),txMouseY(),RGB(0,255,0))); }
            else if(mode == mode_max) ;
        }
        else if(KEY(VK_LEFT) || KEY(VK_UP) || KEY(VK_RIGHT) || KEY(VK_DOWN))
        {
            if(mode == 1)
            {
                for(int i=0;i<pixCt.pixs[0].size();i++)
                {
                    if(KEY(VK_LEFT)) pixCt.pixs[0][i].move(-1,0);
                    if(KEY(VK_RIGHT)) pixCt.pixs[0][i].move(1,0);
                    if(KEY(VK_UP)) pixCt.pixs[0][i].move(0,-1);
                    if(KEY(VK_DOWN)) pixCt.pixs[0][i].move(0,1);
                }
            }
            else if(mode == 2)
            {
                for(int j=0;j<pixCt.pixs.size();j++)
                {
                    for(int i=0;i<pixCt.pixs[j].size();i++)
                    {
                        if(KEY(VK_LEFT)) pixCt.pixs[j][i].move(-1,0);
                        if(KEY(VK_RIGHT)) pixCt.pixs[j][i].move(1,0);
                        if(KEY(VK_UP)) pixCt.pixs[j][i].move(0,-1);
                        if(KEY(VK_DOWN)) pixCt.pixs[j][i].move(0,1);
                    }
                }
            }
        }
        else if (KEY(VK_SPACE) && TIME - Time > 2)
        {
            mode++;
            if(mode>mode_max) mode = 0;
            Time = TIME;
            resetCol();
            txClear();
        }
        else if (KEY(VK_F1))
        {
            pixCt.pixs[0].clear();
            pixCt.pixs[0].insert(pixCt.pixs[0].end(), pixel(-1,-1,RGB(255,0,0)));
            resetCol();
            txClear();
        }
        txSleep(10);
    }
    txEnd();
    for(int j=0;j<pixCt.pixs.size();j++) save_file(pixCt.names[j].c_str(), pixCt.pixs[j]);
    return 0;
}


void drow(vector<pixel> pixs)
{
    for(int i=0;i<pixs.size();i++)
    {
        txSetColor(pixs[i].color,1);
        txSetFillColor(pixs[i].color);
        txCircle(pixs[i].x,pixs[i].y,3);
        /*for(double x=pixs[i].x;x<pixs[i].x+4;x++)
        {
            for(double y=pixs[i].y;y<pixs[i].y+4;y++) txSetPixel(x, y,pixs[i].color);
        }*/
    }
}

void resetCol()
{
    txSetFillColour(RGB(50,50,50));
    txSetColor(TX_WHITE, 1);
}

