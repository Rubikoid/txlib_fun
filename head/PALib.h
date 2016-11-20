/*!
    @file
    @brief Заголовочный файл с основными классами
    @author Dmitry Zotov

    Данный файл содержит объявления основных классов и функций.
*/

#ifndef PALIB_H
#define PALIB_H

#define TIME     GetTickCount()/100
#define KEY      GetAsyncKeyState

/*!
    @brief Класс пикселя

    Класс, отвечающий за содержание и действия с одним пикселем
*/
class pixel
{
    public:
    double x; //< X координата пикселя
    double y; //< Y координата пикселя
    COLORREF color; //< Цвет пикселя в структуре #COLORREF

    /*!
        @brief Конструктор

        Конструктор, задающий начальные параметры пикселя

        @param X,Y Координаты
        @param col Цвет пикселя
    */
    pixel(double X, double Y, COLORREF col);

    /*!
        @brief Поворот пикселя

        Поворачивает пиксель вокруг точки с координатами @p @a cX, @p @a cY на @p @a rol градусов c использованием функции #rollX и #rollY

        @param cX,cY Координаты центра
        @param rol Угол повората в градусах
    */
    void roll(double cX, double cY, float rol);

    /*!
        @brief Перемещение пикселя

        Перемещается пиксель на @p @a mx, @p @a my

        @param mx,my Координаты перемещения
    */
    void move(double mx, double my);
    pixel();//< Пустой конструктор для работы с векторами
};

class pixCtrl
{
    public:
    vector< vector<pixel> > pixs;
    vector<string> names;
    pixCtrl(const char *file);
    pixCtrl();
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
	
    mv(const char *file);
    mv();
    void do_move();
    void get_center(double nX=0.0, double nY=0.0);
};

class movsCtrl
{
    public:
    vector<mv> movs;
    movsCtrl(const char *file);
    movsCtrl();
};

vector<pixel> load_file(const char *file);
void save_file(const char *file,vector<pixel> pixs);

/*!
    @brief Вычисление рандомного числа

    Вычисляет рандомное число от @p @a min до @p @a max включительно

    @param min,max Ограничители числа
    @return Рандомное число
*/
int irand(int min, int max);

/*!
    @brief Вычисляет синус от угла в градусах

    @param roll Угол в градусах
    @return Синус угла
*/
double sinus(float roll);

/*!
    @brief Вычисляет косинус от угла в градусах

    @param roll Угол в градусах
    @return Косинус угла
*/
double cosin(float roll);

/*!
    @brief Вычисление X координаты точки после поворота

    Вычисляет новую X координату точки после поворота относительно центра @p @a cX, @p @a cY на @p @a roll градусов.
    @param x,y Координаты точки
    @param cX,cY Координаты центра
    @param roll Угол поворота
    @return Новая X координата

    @warning Угол в градусах
    @warning При положжительном угле поворот происходит против часовой стрелки
*/
double rollX(double x, double y, double cX, double cY, float roll);

/*!
    @brief Вычисление Y координаты точки после поворота

    Вычисляет новую Y координату точки после поворота относительно центра @p @a cX, @p @a cY на @p @a roll градусов.
    @param x,y Координаты точки
    @param cX,cY Координаты центра
    @param roll Угол поворота
    @return Новая Y координата

    @warning Угол в градусах
    @warning При положжительном угле поворот происходит против часовой стрелки
*/
double rollY(double x, double y, double cX, double cY, float roll);
#endif
