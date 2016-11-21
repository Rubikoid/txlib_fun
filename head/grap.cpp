#include <stdio.h>
#include "TXLib.h"
#include "PALib.h"
#include "grap.h"

void init(int x, int y)
{
    txCreateWindow(x,y, true);
    txTextCursor(false);
    resetCol();
    txClear();
}

void draw_mv(mv mvm, int isCir)
{
    for(int i=0;i<mvm.pix.size();i++)
    {
        if(isCir)
        {
            txSetColor(mvm.pix[i].color,1);
            txSetFillColor(mvm.pix[i].color);
            txCircle(mvm.pix[i].x,mvm.pix[i].y,3);
        }
        else
        {
            for(double x=mvm.pix[i].x;x<mvm.pix[i].x+4;x++)
            {
                for(double y=mvm.pix[i].y;y<mvm.pix[i].y+4;y++) txSetPixel(x, y,mvm.pix[i].color);
            }
        }
    }
}

void draw_pix(vector<pixel> pixs, int isCir)
{
    for(int i=0;i<pixs.size();i++)
    {
        if(isCir)
        {
            txSetColor(pixs[i].color,1);
            txSetFillColor(pixs[i].color);
            txCircle(pixs[i].x,pixs[i].y,3);
        }
        else
        {
            for(double x=pixs[i].x;x<pixs[i].x+4;x++)
            {
                for(double y=pixs[i].y;y<pixs[i].y+4;y++) txSetPixel(x, y,pixs[i].color);
            }
        }
    }
}

void resetCol()
{
    txSetFillColour(RGB(50,50,50));
    txSetColor(TX_WHITE, 1);
}
