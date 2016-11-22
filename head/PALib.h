/*!
    @file
    @brief Заголовочный файл с основными классами
    @author Dmitry Zotov

    Данный файл содержит объявления основных классов и функций.
*/

#ifndef PALIB_H
#define PALIB_H

#include <vector>
#include <string>
#include "TXLib.h"

using namespace std;

#define TIME     GetTickCount()/100
#define KEY      GetAsyncKeyState

/*!
    @brief Класс пикселя

    Класс, отвечающий за содержание и действия с одним пикселем
*/
class pixel
{
    public:
    double x; ///< X координата пикселя
    double y; ///< Y координата пикселя
    COLORREF color; ///< Цвет пикселя в структуре #COLORREF

    /*!
        @brief Конструктор

        Конструктор, задающий начальные параметры пикселя

        @param X,Y Координаты
        @param col Цвет пикселя
    */
    pixel(double X, double Y, COLORREF col);

    /*!
        @brief Поворот пикселя

        Поворачивает пиксель вокруг точки с координатами @a cX, @a cY на @a rol градусов c использованием функции #rollX и #rollY

        @param cX,cY Координаты центра
        @param rol Угол повората в градусах
    */
    void roll(double cX, double cY, float rol);

    /*!
        @brief Перемещение пикселя

        Перемещается пиксель на @a mx, @a my

        @param mx,my Координаты перемещения
    */
    void move(double mx, double my);
    //! Пустой конструктор для работы с векторами
    pixel();
};

/*!
    @brief Класс контроллера рисунков

    Класс, отвечающий за содержание и действия с рисунками
*/
class pixCtrl
{
    public:
    vector< vector<pixel> > pixs; ///< Вектор векторов пикселей для хранения нескольких рисунков
    vector<string> names; ///< Вектор строк для хранения названий файлов нескольких рисунков
    /*!
        @brief Конструктор, производится загрузка данных из файла

        Загружает список рисунков по формату "НазваниеФайлаБезTxt:\nДругоеНазваниеФайла:",
        либо, если это файл с одним рисунком, загружает один рисунок,
        либо, если файл не существует - создает пустой файл и работает с ним, как с одним рисунком.

        @note При загрузке списка рисунков файл создается, если не существует.
        @note Можно использовать пути файлов, вроде ".\..\ДругаяПапка\Файл:"

        @param file Название файла без .txt
    */
    pixCtrl(const char *file);
    pixCtrl(); ///< Пустой конструктор для работы с векторами
};

/*!
    @brief Класс перемешения

    Класс, отвечающий за содержание и перемещения с вектором пикселей
*/
class mv
{
    public:
    vector<pixel> pix; ///< Вектор пикселей
    char name[40]; ///< Названия файла для конкретного рисунка
    double x; ///< Перемещение по оси X
    double y; ///< Перемещение по оси Y
    double rollCX; ///< X координата центра вращения
    double rollCY; ///< Y координата центра вращения
    float roll; ///< Угол вращения @warning В градусах!
    double centerX; ///< X координата центра рисунка
    double centerY; ///< Y координата центра рисунка

    /*!
        @brief Конструктор класса, производится загрузка данных

        Загружает данные по формату из @a file в вектор, обнуляет переменные.
        Формат файла:\n
        "FileName:\n
         x_move,y_move\n
         rollCX,rollCY,roll\n
        "\n
        Пример:
        "test:\n
         0,0\n
         0,0,0\n
        " - рисунок, загруженный из файла с именем test.txt при вызове #do_move никуда не сдвинется

        @param file Название файла без .txt
    */
    mv(const char *file);
    mv(); ///< Пустой конструктор для работы с векторами
    /*!
        @brief Перемещает каждый пиксель рисунка

        Перемещается каждый пиксель на #x #y и вращает вокруг #rollCX #rollCY на #roll градусов
        @warning Используются функции #rollX и #rollY
    */
    void do_move();
    /*!
        @brief Вычисляет центр рисунка и прибавляет его к центру поворота

        Вычисляется координаты центра рисунка, после прибавляются к загруженным из файла координатам поворота.
        В случае, если @a nX и @a nY не равны 0 - задает центр поворота как @a nX и @a nY

        @param nX, nY
    */
    void get_center(double nX=0.0, double nY=0.0);
};

class movsCtrl
{
    public:
    vector<mv> movs;
    movsCtrl(const char *file);
    movsCtrl(); ///< Пустой конструктор для работы с векторами
};

vector<pixel> load_file(const char *file);
void save_file(const char *file,vector<pixel> pixs);

/*!
    @brief Вычисление рандомного числа

    Вычисляет рандомное число от @a min до @a max включительно

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

    Вычисляет новую X координату точки после поворота относительно центра @a cX, @a cY на @a roll градусов.
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

    Вычисляет новую Y координату точки после поворота относительно центра @a cX, @a cY на @a roll градусов.
    @param x,y Координаты точки
    @param cX,cY Координаты центра
    @param roll Угол поворота
    @return Новая Y координата

    @warning Угол в градусах
    @warning При положжительном угле поворот происходит против часовой стрелки
*/
double rollY(double x, double y, double cX, double cY, float roll);
#endif
