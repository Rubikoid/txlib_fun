#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"
void work(int secs, int h, int m);
void draw_time(int cX, int cY, int seconds, int minutes, int horses);
void draw_line(int cX, int cY, int radi, int one_len, float angle);
void init();

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
    init();
    SYSTEMTIME st;
    Time = TIME;
    T0 = Time;
    txBegin();
    while(!KEY(VK_ESCAPE))
    {
        GetLocalTime(&st);
        txClear();
        int secs_from_start = ((TIME - T0))%3600;
        work(st.wSecond, st.wHour, st.wMinute);
        sprintf(mod, "Secs:%d;Hours:%d;Minutes:%d\0", st.wSecond,st.wHour,st.wMinute);
        txTextOut(400, 30, mod);
        txSleep(10);
    }
    txEnd();
    return 0;
}

void init()
{
    txCreateWindow(800,500, true);
    txSetFillColour(RGB(50,50,50));
    txTextCursor(false);
    txClear();
}

void work(int secs, int h, int m)
{
    draw_time(400,250, secs, m ,h);
}

void draw_time(int cX, int cY, int seconds, int minutes, int horses)
{
    int part_len = 2*M_PI*150/12;
    int one_len = 10;
    int radi = 150;
    txCircle((double)cX, (double)cY, radi);
    for(float angle = 0.0; angle<=360;angle+=30.0) draw_line(cX, cY, radi, one_len, angle);//txLine(rollX(cX, cY-(radi-one_len), cX, cY, angle), rollY(cX, cY-(radi-one_len), cX, cY, angle), rollX(cX, cY-radi, cX, cY, angle),rollY(cX, cY-radi, cX, cY, angle));
    draw_line(cX, cY, 150, 150, -6*seconds);
    draw_line(cX, cY, 120, 120, -6*minutes);
    draw_line(cX, cY, 80, 80, -30*horses);

}

void draw_line(int cX, int cY, int radi, int one_len, float angle)
{
    txLine(rollX(cX, cY-(radi-one_len), cX, cY, angle), rollY(cX, cY-(radi-one_len), cX, cY, angle), rollX(cX, cY-radi, cX, cY, angle),rollY(cX, cY-radi, cX, cY, angle));
}
