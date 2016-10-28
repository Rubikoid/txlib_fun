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
double rollX(double x, double y, double cX, double cY, float roll);
double rollY(double x, double y, double cX, double cY, float roll);

class pixel
{
    public:
    double x;
    double y;
    COLORREF color;
    pixel(double X, double Y, COLORREF col)
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
    double x;
    double y;
    double rollCX;
    double rollCY;
    float roll;
    double centerX;
    double centerY;
    mv(const char *file)
    {
        strcpy(name, file);
        pix = load_file(name);
        x=0;
        y=0;
        rollCX=0;
        rollCY=0;
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
        if(pix.size() <= 0) return;
        int sumX=0;
        int sumY=0;
        for(int i=0;i<pix.size();i++)
        {
            sumX+=pix[i].x;
            sumY+=pix[i].y;
        }
        centerX = (sumX/pix.size());
        centerY = (sumY/pix.size());
        //printf("X:%f;Y:%f", rollCX, rollCY);
        rollCX+=centerX;
        rollCY+=centerY;
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
                float tmpx, tmpy, rolx, roly;
                if(stage == 0){sscanf(mes,"%f,%f", &tmpx, &tmpy); last_mv.x = tmpx; last_mv.y = tmpy; stage++;}
                else if(stage == 1)
                {
                    sscanf(mes,"%f,%f,%f", &rolx, &roly, &last_mv.roll);
                    last_mv.rollCX = rolx;
                    last_mv.rollCY = roly;
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
        float x,y;
        int r,g,b;
        stat = fscanf(fl,"%f,%f;%d,%d,%d\n", &x, &y, &r, &g, &b);
        if(x>2000.0 || y>2000.0){ continue;}
        pixs.insert(pixs.end(), pixel(x,y,RGB(r,g,b)));
    }
    fclose(fl);
    return pixs;
}

void save_file(const char *file,vector<pixel> pixs)
{
    FILE *fl;
    fl= fopen(file, "w");
    for(int i=0;i<pixs.size()-1;i++){ fprintf(fl, "%f,%f;%d,%d,%d\n", pixs[i].x, pixs[i].y, GetRValue(pixs[i].color), GetGValue(pixs[i].color), GetBValue(pixs[i].color)); }
    fclose(fl);
}


int irand(int min, int max)
{
    return rand() % max + min;
}

double sinus(float roll)
{
    return (double)sin(roll * M_PI / 180.0);
}
double cosin(float roll)
{
    return (double)cos(roll * M_PI / 180.0);
}

double rollX(double x, double y, double cX, double cY, float roll)
{
    int rx = x - cX;
    int ry = y - cY;
    double ret = rx*cosin(roll)+ry*sinus(roll)+cX;
    return ret;
	//return ((x)*cosin(roll)+(y)*sinus(roll));
    //return 0.0;
}

double rollY(double x, double y, double cX, double cY, float roll)
{
    int rx = x - cX;
    int ry = y - cY;
    double ret = ry*cosin(roll) - rx*sinus(roll)+cY;
    return ret;
	//return ((y)*cosin(roll) - (x)*sinus(roll));
    //return 0.0;
}
