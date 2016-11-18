#include "../head/TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "../head/PALib.h"

void work(int secs, int h, int m, int radi);
void draw_time(int cX, int cY, int seconds, int minutes, int horses, int radi);
void draw_line(int cX, int cY, int radi, int one_len, float angle);
void init(int radi);

int main()
{
    char mod[20], *message;
    int radi = 100;
    init(radi);
    SYSTEMTIME st;
    txBegin();
    while(!KEY(VK_ESCAPE))
    {
        GetLocalTime(&st);
        txClear();
        work(st.wSecond, st.wHour, st.wMinute, radi);
        //sprintf(mod, "Secs:%d;Hours:%d;Minutes:%d\0", st.wSecond,st.wHour,st.wMinute);
        //txTextOut(400, 30, mod);
        txSleep(10);
    }
    txEnd();
    return 0;
}

void init(int radi)
{
    txCreateWindow((radi+5)*2,(radi+5)*2, true);
    txSetFillColour(RGB(50,50,50));
    txTextCursor(false);
    txClear();
}

void work(int secs, int h, int m, int radi)
{
    draw_time(radi+5,radi+5, secs, m ,h,radi);
}

void draw_time(int cX, int cY, int seconds, int minutes, int horses, int radi)
{
    int one_len = radi/15;
    txCircle((double)cX, (double)cY, radi);
    for(float angle = 0.0; angle<=360;angle+=30.0) draw_line(cX, cY, radi, one_len, angle);//txLine(rollX(cX, cY-(radi-one_len), cX, cY, angle), rollY(cX, cY-(radi-one_len), cX, cY, angle), rollX(cX, cY-radi, cX, cY, angle),rollY(cX, cY-radi, cX, cY, angle));
    draw_line(cX, cY, radi, radi, -6*seconds);
    draw_line(cX, cY, radi-one_len*2, radi-one_len*2, -6*minutes);
    draw_line(cX, cY, radi-one_len*6, radi-one_len*6, -30*horses);

}

void draw_line(int cX, int cY, int radi, int one_len, float angle)
{
    txLine(rollX(cX, cY-(radi-one_len), cX, cY, angle), rollY(cX, cY-(radi-one_len), cX, cY, angle), rollX(cX, cY-radi, cX, cY, angle),rollY(cX, cY-radi, cX, cY, angle));
}
