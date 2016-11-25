#ifndef GRAP_H
#define GRAP_H

#include "PALib.h"

/*!
    @file
    @brief Заголовочный файл с функциями графики
    @author Dmitry Zotov

    Данный файл содержит объявления функций работы с графикой
*/

/*!
	@brief Сброс параметров
	
	Сбрасывает цвет заливки на RGB(50,50,50), устанавливает белый цвет линий и 1 размер
*/
void resetCol();

/*!
	@brief Рисование перемещение
	
	Рисует массив пикселей из перемещения
	
	@param mvm Перемещение
	@param isCir Отрисовка кругами
*/
void draw_mv(mv mvm, int isCir = 1);

/*!
	@brief Рисование массива пикселей
	
	Рисует массив пикселей
	
	@param pixs Массив пикселей
	@param isCir Отрисовка кругами
*/
void draw_pix(vector<pixel> pixs, int isCir = 1);

/*!
	@brief Инициализация и очистка экрана TXLIB
	
	@param x,y Размеры окна
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
