#include "../head/grap.h"

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
    movsCtrl mvs;
    message = txInputBox("Введите название группы:", NULL, "");
    if(message[0] == 0) return 1;
    strcat(message,".txt");
    mvs = movsCtrl(message);
    init(800,500);
    Time = TIME;
    T0 = Time;
    begin();
    while(!KEY(VK_ESCAPE))
    {
        resetCol();
        clear();
        sprintf(mod, "TIME:%d;DiffX:%f;DiffY:%f\0", ((TIME - T0)/10)%1000, txMouseX() - mvs.movs[0].rollCX, txMouseY() - mvs.movs[0].rollCY);
        textOut(500, 30, mod);
        for(int k=0;k<mvs.movs.size();k++)
        {
            draw_mv(mvs.movs[k]);
            mvs.movs[k].do_move();
        }
        gsleep(10);
    }
    end();
    return 0;
}
