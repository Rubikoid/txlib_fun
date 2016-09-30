#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
    vector<pixel> pixs;
    message = txInputBox("¬ведите название группы:");
    strcat(message,".txt");
    pixs = load_file(message);
    txCreateWindow(800,500, true);
    txSetFillColour(RGB(50,50,50));
    txClear();
    Time = TIME;
    T0 = Time;
    int move = 0;
    while(!KEY(VK_ESCAPE))
    {
        txClear();
        txBegin();
        sprintf(mod, "TIME:%d\0", ((TIME - T0)/10)%1000);
        txTextOut(500, 30, mod);
        for(int i=0;i<pixs.size();i++)
        {
            for(int x=pixs[i].x;x<pixs[i].x+4;x++)
            {
                for(int y=pixs[i].y;y<pixs[i].y+4;y++)
                txSetPixel(x, y,pixs[i].color);
            }
            pixs[i].x+=1;
            //pixs[i].y+=1;
        }
        txEnd();
        txSleep(10);
    }
    return 0;
}
