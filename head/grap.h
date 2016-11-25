#ifndef GRAP_H
#define GRAP_H

#include "PALib.h"

/*!
    @file
    @brief ������������ ���� � ��������� �������
    @author Dmitry Zotov

    ������ ���� �������� ���������� ������� ������ � ��������
*/

/*!
	@brief ����� ����������
	
	���������� ���� ������� �� RGB(50,50,50), ������������� ����� ���� ����� � 1 ������
*/
void resetCol();

/*!
	@brief ��������� �����������
	
	������ ������ �������� �� �����������
	
	@param mvm �����������
	@param isCir ��������� �������
*/
void draw_mv(mv mvm, int isCir = 1);

/*!
	@brief ��������� ������� ��������
	
	������ ������ ��������
	
	@param pixs ������ ��������
	@param isCir ��������� �������
*/
void draw_pix(vector<pixel> pixs, int isCir = 1);

/*!
	@brief ������������� � ������� ������ TXLIB
	
	@param x,y ������� ����
*/
void init(int x, int y);

void clear();
void begin();
void end();
void gsleep(int sleep);
void textOut(int x, int y, char *text);
int MouseButt();
int MouseX();
int MouseY();
#endif
