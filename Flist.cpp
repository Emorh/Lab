//
// Created by gefre on 10.02.2020.
//

#include <iostream>
#include "Flist.h"
#include "cstring"

int Flist::len()
{
    seekg(sizeof(int) * 2);
    return fread<int>();
}
template <typename T>
void Flist::fwrite(const T val)
{
    this->write((char *) &val, sizeof(val));
}
template <typename T>
void Flist::add(const T &dat) { // Добавление в конец списка
    this->seekg(0);

    if (fread<int>() != 0) { // Список не пуст
        // Узнать, на каком элементе (на какой позиции) заканчивается список
        this->seekg(sizeof(int));
        int penultimatePos = fread<int>();
        // Обновление позиции конца списка
        this->seekg(0, ios::end);
        int lastPos = this->tellg();
        this->seekp(sizeof(int));
        fwrite(lastPos);
        // Обновление длины списка
        this->seekg(sizeof(int) * 2);
        int lenMinOne = fread<int>();
        this->seekp(sizeof(int) * 2);
        fwrite(lenMinOne + 1);
        // Обновление предпоследнего элемента, чтобы он знал, где находится следующий за ним
        this->seekp(penultimatePos);
        fwrite(lastPos);
        this->seekp(0, ios::end);
        // Добавление нового последнего элемента
    }  else  { // Список пуст
        this->seekp(0);
        fwrite(sizeof(int) * 3); // Начало списка
        fwrite(sizeof(int) * 3); // Конец
        fwrite(1); // Длина
    }

    fwrite(0); // Указатель на следующий за первым
    fwrite(dat); // Данные первого
}

void Flist::Set(int index)
{
    if (len() == 0 || index < 1 || index > len())
    {
        throw "sds"; /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    // Извлечение последнего -- отдельный случай для ускорения
    if (index == len()) {
        seekg(sizeof(int));
        seekg(fread<int>() + sizeof(int));
    } else {
        seekg(0);
        for (int i = 1; i <= index; ++i) {
            seekg(fread<int>());
        }
        seekg(sizeof(int), ios::cur);
    }
}

Flist::Flist(char name[])
{
    this->name = new char[strlen(name) + 1];
    for (int i = 0; i < strlen(name); ++i)
    {
        this->name[i] = name[i];
    }
    this->name[strlen(name)] = '\0';

    open(name, ios::binary | ios::out | ios::in | ios::ate);

    if (!(*this))                 // Если есть какие-то проблемы с файлом
    {
        ofstream tmp(name);    // Пробуем создать его (вдруг его не существовало)
        tmp.close();

        // Если проблема осталась, то мы бессильны
        open(name, ios::binary | ios::out | ios::in | ios::ate);
        if (!is_open()) {
            cerr << "Can't open " << name;
            exit(1);
        }
    }

    // Если файл пустой
    if (tellg() == 0) {
        for (int i = 0; i < 3; ++i) {
            this->fwrite(0);
        }
    }
}

Flist::~Flist()
{
    delete[] name;
    close();
}

Flist &Flist::operator<<(char &val)
{
    add<char>(val);
    return *this;
}

Flist &Flist::operator<<(short &val)
{
    add<short>(val);
    return *this;
}

Flist &Flist::operator<<(int &val)
{
    add<int>(val);
    return *this;
}

Flist &Flist::operator<<(double &val)
{
    add<double>(val);
    return *this;
}

void Flist::swap(const int &lPrev) {
    int left, mid, right;
    seekg(lPrev);
    left = fread<int>();
    seekg(left);
    mid = fread<int>();
    seekg(mid);
    right = fread<int>();

    // Нужно получить
    // | mid | -> | right | -> | left | -> | rNext | -> ...
    // (lPrev)     (left)     (mid)        (right)
    seekp(lPrev);
    fwrite(mid);
    seekp(left);
    fwrite(right);
    seekp(mid);
    fwrite(left);
    // Обновление конца
    if (right == 0) {
        seekp(sizeof(int));
        fwrite(left);
    }
}

char &Flist::operator>>(char & val)
{
    val = fread<char>();
    return val;
}

short &Flist::operator>>(short & val)
{
    val = fread<short>();
    return val;
}

int &Flist::operator>>(int & val)
{
    val = fread<int>();
    return val;
}

double &Flist::operator>>(double & val)
{
    val = fread<double>();
    return val;
}






