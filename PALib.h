#include <vector>

using namespace std;

#define TIME     GetTickCount()/100
#define KEY      GetAsyncKeyState

class pixel;
class mv;
class movsCtrl;
vector<pixel> load_file(const char *file);
void save_file(const char *file,vector<pixel> pixs);
int irand(int min, int max);

class pixel
{
    public:
    int x;
    int y;
    COLORREF color;
    pixel(int X, int Y, COLORREF col)
    {
        x = X;
        y = Y;
        color = col;
    }
    pixel()
    {

    }
};

class mv
{
    public:
    vector<pixel> pix;
    char name[40];
    int x;
    int y;
    mv(const char *file)
    {
        strcpy(name, file);
        pix = load_file(name);
    }
    mv(){}
    void do_move()
    {
        for(int i=0;i<pix.size();i++)
        {
            pix[i].x += x;
            pix[i].y += y;
        }
    }
};

class movsCtrl
{
    public:
    vector<mv> movs;
    movsCtrl(const char *file)
    {
        movs = vector<mv>(0);
        FILE *fl;
        fl = fopen(file, "r");
        int stat = 0, start=0;
        char mes[300];
        mv last_mv;
        while(stat != EOF)
        {
            stat = fscanf(fl,"%s\n", &mes);
            if(stat == EOF){ movs.insert(movs.end(), last_mv); break;}
            if(strchr(mes, ':') != NULL)
            {
                char *tmp = strtok(mes,":");
                strcat(mes,".txt");
                if(start != 0) movs.insert(movs.end(), last_mv);
                if(start == 0) start = 1;
                last_mv = mv(mes);
            }
            else
            {
                sscanf(mes,"%d,%d", &last_mv.x, &last_mv.y);
            }
        }
        fclose(fl);
    }
    movsCtrl(){}
};

vector<pixel> load_file(const char *file)
{
    FILE *fl;
    vector<pixel> pixs(0);
    fl = fopen(file, "r");
    int stat = 0;
    while(stat != EOF)
    {
        int x,y,r,g,b;
        stat = fscanf(fl,"%d,%d;%d,%d,%d\n", &x, &y, &r, &g, &b);
        pixs.insert(pixs.end(), pixel(x,y,RGB(r,g,b)));
    }
    fclose(fl);
    return pixs;
}

void save_file(const char *file,vector<pixel> pixs)
{
    FILE *fl;
    fl= fopen(file, "w");
    for(int i=0;i<pixs.size()-1;i++){ fprintf(fl, "%d,%d;%d,%d,%d\n", pixs[i].x, pixs[i].y, GetRValue(pixs[i].color), GetGValue(pixs[i].color), GetBValue(pixs[i].color)); }
    fclose(fl);
}


int irand(int min, int max)
{
    return rand() % max + min;
}

