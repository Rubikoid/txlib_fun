#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"
void work(int secs);
void draw_time(int cX, int cY, int seconds, int minutes, int horses);
void draw_line(int cX, int cY, int radi, int one_len, float angle);

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
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
        int secs_now = (((TIME - T0)/10)%1000)%60;
        work(secs_now);
        sprintf(mod, "Secs:%d;X:%d;Y:%d\0", ((TIME - T0)/10)%1000,txMouseX(),txMouseY());
        txTextOut(500, 30, mod);
        txSleep(10);
    }
    txEnd();
    return 0;
}

void work(int secs)
{
    draw_time(400,250, secs, 0 ,0);
}

void draw_time(int cX, int cY, int seconds, int minutes, int horses)
{
    int part_len = 2*M_PI*150/12;
    int one_len = 10;
    int radi = 150;
    txCircle((double)cX, (double)cY, radi);
    for(float angle = 0.0; angle<=360;angle+=30.0) draw_line(cX, cY, radi, one_len, angle);//txLine(rollX(cX, cY-(radi-one_len), cX, cY, angle), rollY(cX, cY-(radi-one_len), cX, cY, angle), rollX(cX, cY-radi, cX, cY, angle),rollY(cX, cY-radi, cX, cY, angle));
    draw_line(cX, cY, 150, 150, -6*seconds);

}

void draw_line(int cX, int cY, int radi, int one_len, float angle)
{
    txLine(rollX(cX, cY-(radi-one_len), cX, cY, angle), rollY(cX, cY-(radi-one_len), cX, cY, angle), rollX(cX, cY-radi, cX, cY, angle),rollY(cX, cY-radi, cX, cY, angle));
}
