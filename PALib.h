#include <vector>

using namespace std;

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

