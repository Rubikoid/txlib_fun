#include "TXLib.h"
#include <stdio.h>
#include "windows.h"
#include "PALib.h"
#include <cmath>

int main()
{
    double x=8,y=8;
    int cx=7, cy=7;
    for(int i=0;i<20;i++)
    {
        int x_start = x;
        x = rollX(x,y,cx,cy,90);
        y = rollY(x_start,y,cx,cy,90);
        printf("%f;%f\n",x ,y);
    }
    return 0;
}
