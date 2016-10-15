#include <vector>
#include <math.h>

using namespace std;

#define TIME     GetTickCount()/100
#define KEY      GetAsyncKeyState

class pixel;
class mv;
class movsCtrl;
vector<pixel> load_file(const char *file);
void save_file(const char *file,vector<pixel> pixs);
int irand(int min, int max);
double sinus(float roll);
double cosin(float roll);
double rollX(int x, int y, int cX, int cY, float roll);
double rollY(int x, int y, int cX, int cY, float roll);

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
    int rollCX;
    int rollCY;
    float roll;
    int centerX;
    int centerY;
    mv(const char *file)
    {
        strcpy(name, file);
        pix = load_file(name);
        x=0;
        y=0;
        rollCX=80;
        rollCY=80;
        roll = 0.0;
        centerX=0;
        centerY=0;
    }
    mv(){}
    void do_move()
    {
        //printf("%d,%d, %f\n", rollCX, rollCY, roll);
        for(int i=0;i<pix.size();i++)
        {
            int x_start = pix[i].x;
            pix[i].x = rollX(pix[i].x, pix[i].y, rollCX, rollCY, roll);
            pix[i].y = rollY(x_start, pix[i].y, rollCX, rollCY, roll);
            pix[i].x += x;
            pix[i].y += y;
        }
        centerX+=x;
        centerY+=y;
        rollCX+=x;
        rollCY+=y;
    }

    void get_center()
    {
        int sumX;
        int sumY;
        for(int i=0;i<pix.size();i++)
        {
            sumX+=pix[i].x;
            sumY+=pix[i].y;
        }
        centerX = (int)(sumX/pix.size());
        centerY = (int)(sumY/pix.size());
        //rollCX+=centerX;
        //rollCY+=centerY;
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
        int stat = 0, start=0, stage = 0;
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
                stage = 0;
            }
            else
            {
                if(stage == 0){sscanf(mes,"%d,%d", &last_mv.x, &last_mv.y); stage++;}
                else if(stage == 1)
                {
                    sscanf(mes,"%d,%d,%f", &last_mv.rollCX, &last_mv.rollCY, &last_mv.roll);
                    last_mv.get_center();
                    stage++;
                }
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

double sinus(float roll)
{
    return (double)sin(roll * M_PI / 180);
}
double cosin(float roll)
{
    return (double)cos(roll * M_PI / 180);
}

double rollX(int x, int y, int cX, int cY, float roll)
{
    return ((x-cX)*cosin(roll)+(y-cY)*sinus(roll)+cX);
}

double rollY(int x, int y, int cX, int cY, float roll)
{
    return ((y-cY)*cosin(roll) - (x-cX)*sinus(roll)+cY);
}
