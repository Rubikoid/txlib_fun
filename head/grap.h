#ifndef GRAP_H
#define GRAP_H

#include "PALib.h"

void resetCol();
void draw_mv(mv mvm, int isCir = 1);
void draw_pix(vector<pixel> pixs, int isCir = 1);
void init(int x, int y);

#endif
