#include "../head/grap.h"

#define mode_max 4
#define SIZE 6

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
    pixCt = pixCtrl(message);
    init(800,500);
    Time = TIME;
    T0 = Time;
    begin();
    while(!KEY(VK_ESCAPE))
    {
        resetCol();
        clear();
        sprintf(mod, "MODE:%d,TIME:%d\0", mode, ((TIME - T0)/10)%1000);
        textOut(500, 30, mod);
        for(int i=0; i<pixCt.pixs.size(); i++) draw_pix(pixCt.pixs[i]);
        if (MouseButt() & 1)
        {
            if(mode == 0){ pixCt.pixs[0].insert(pixCt.pixs[0].end(), pixel(MouseX(),MouseY(),RGB(0,255,0))); }
            else if(mode == 1)
            {
                for(int i=-SIZE;i<SIZE;i+=3) for(int j=-SIZE;j<SIZE;j+=3) pixCt.pixs[0].insert(pixCt.pixs[0].end(), pixel(MouseX()+i,MouseY()+j,RGB(0,255,0)));
            }
            else if(mode == mode_max) ;
        }
        else if(KEY(VK_LEFT) || KEY(VK_UP) || KEY(VK_RIGHT) || KEY(VK_DOWN))
        {
            if(mode == 2)
            {
                for(int i=0;i<pixCt.pixs[0].size();i++)
                {
                    if(KEY(VK_LEFT)) pixCt.pixs[0][i].move(-1,0);
                    if(KEY(VK_RIGHT)) pixCt.pixs[0][i].move(1,0);
                    if(KEY(VK_UP)) pixCt.pixs[0][i].move(0,-1);
                    if(KEY(VK_DOWN)) pixCt.pixs[0][i].move(0,1);
                }
            }
            else if(mode == 3)
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
            clear();
        }
        else if (KEY(VK_F1))
        {
            pixCt.pixs[0].clear();
            pixCt.pixs[0].insert(pixCt.pixs[0].end(), pixel(-1,-1,RGB(255,0,0)));
            resetCol();
            clear();
        }
        gsleep(10);
    }
    end();
    for(int j=0;j<pixCt.pixs.size();j++) save_file(pixCt.names[j].c_str(), pixCt.pixs[j]);
    return 0;
}

