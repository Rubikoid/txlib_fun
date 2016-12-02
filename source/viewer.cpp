#include "../head/grap.h"

int main()
{
    char mod[20], *message;
    long Time = 0, T0 = 0;
    movsCtrl mvs;
    message = txInputBox("¬ведите название группы:", NULL, "");
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
        sprintf(mod, "TIME:%lu;DiffX:%f;DiffY:%f", ((TIME - T0)/10)%1000, MouseX() - mvs.movs[0].rollCX, MouseY() - mvs.movs[0].rollCY);
        textOut(500, 30, mod);
        for(uint k=0;k<mvs.movs.size();k++)
        {
            draw_mv(mvs.movs[k]);
            mvs.movs[k].do_move();
        }
        gsleep(10);
    }
    end();
    return 0;
}
