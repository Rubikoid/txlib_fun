#include <vector>
#include <math.h>
#include <string>
#include "PALib.h"

/*!
    @file
    @brief Заголовочный файл с основными классами
    @author Dmitry Zotov

    Данный файл содержит описания основных классов и функций.
*/

using namespace std;

//pixel
pixel::pixel(){}
pixel::pixel(double X, double Y, COLORREF col)
{
	x = X;
	y = Y;
	color = col;
}

void pixel::roll(double cX, double cY, float rol)
{
	double x_start = x;
	x = rollX(x, y, cX, cY, rol);
	y = rollY(x_start, y, cX, cY, rol);
}

void pixel::move(double mx, double my)
{
	x+=mx;
	y+=my;
}
//pixel

//pixCtrl
pixCtrl::pixCtrl(){}
pixCtrl::pixCtrl(const char *file)
{
	pixs = vector< vector<pixel> >(0);
	FILE *fl;
	if(access(file,0)) fclose(fopen(file, "w"));
	fl = fopen(file, "r");
	int stat = 0;
	char mes[300];
	while(stat != EOF)
	{
		stat = fscanf(fl,"%s\n", mes);
		if(stat == EOF) break;
		if(strchr(mes, ':') != NULL)
		{
			strtok(mes,":");
			strcat(mes,".txt");
			vector<pixel> px = load_file(mes);
			pixs.push_back(px);
			names.push_back(string(mes));
		}
		else break;
	}
	fclose(fl);
	if(pixs.size()==0) { vector<pixel> px = load_file(file); pixs.push_back(px); names.push_back(string(file));}
}
//pixCtrl

//mv
mv::mv(){}
mv::mv(const char *file)
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

void mv::do_move()
{
	for(uint i=0;i<pix.size();i++)
	{
		pix[i].roll(rollCX, rollCY, roll);
		pix[i].move(x,y);
	}
	centerX+=x;
	centerY+=y;
	rollCX+=x;
	rollCY+=y;
}

void mv::get_center(double nX, double nY)
{
	if(pix.size() <= 0) return;
	if(nX != 0.0 && nY != 0.0)
	{
		rollCX = nX;
		rollCY = nY;
		return;
	}
	double sumX=0;
	double sumY=0;
	for(uint i=0;i<pix.size();i++)
	{
		sumX+=pix[i].x;
		sumY+=pix[i].y;
	}
	centerX = (sumX/pix.size());
	centerY = (sumY/pix.size());
	rollCX+=centerX;
	rollCY+=centerY;
}
//mv

//movsCtrl
movsCtrl::movsCtrl(){}
movsCtrl::movsCtrl(const char *file)
{
	movs = vector<mv>(0);
	FILE *fl;
	fl = fopen(file, "r");
	int stat = 0, start=0, stage = 0;
	char mes[300];
	mv last_mv;
	while(stat != EOF)
	{
		stat = fscanf(fl,"%s\n", mes);
		if(stat == EOF){ movs.insert(movs.end(), last_mv); break;}
		if(strchr(mes, ':') != NULL)
		{
			strtok(mes,":");
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
				//last_mv.get_center();
				if(movs.size() > 0) last_mv.get_center(movs[0].rollCX, movs[0].rollCY);
				else last_mv.get_center();
				stage++;
			}
		}
	}
	fclose(fl);
}
//movsCtrl

vector<pixel> load_file(const char *file)
{
    FILE *fl;
    vector<pixel> pixs(0);
    if(access(file,0)) fclose(fopen(file, "w"));
    fl = fopen(file, "r");
    int stat = 0;
    while(stat != EOF)
    {
        float x=-100.0,y=-100.0;
        int r=0,g=0,b=0;
        stat = fscanf(fl,"%f,%f;%d,%d,%d\n", &x, &y, &r, &g, &b);
        if(x>2000.0 || y>2000.0 || (x == -100.0 && y== -100.0 && r == 0 && g == 0)){ continue;}
        pixs.insert(pixs.end(), pixel(x,y,RGB(r,g,b)));
    }
    fclose(fl);
    if(pixs.size() == 0){ printf("new"); pixs.insert(pixs.end(), pixel(-100,-100,RGB(0,0,0))); }//null pixel
    return pixs;
}

void save_file(const char *file,vector<pixel> pixs)
{
    FILE *fl;
    fl= fopen(file, "w");
    for(uint i=0;i<pixs.size();i++){ if(pixs[i].x < 0 || pixs[i].y < 0) continue; fprintf(fl, "%f,%f;%d,%d,%d\n", pixs[i].x, pixs[i].y, GetRValue(pixs[i].color), GetGValue(pixs[i].color), GetBValue(pixs[i].color)); }
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
    double rx = x - cX;
    double ry = y - cY;
    double ret = rx*cosin(roll)+ry*sinus(roll)+cX;
    return ret;
}

double rollY(double x, double y, double cX, double cY, float roll)
{
    double rx = x - cX;
    double ry = y - cY;
    double ret = ry*cosin(roll) - rx*sinus(roll)+cY;
    return ret;
}
