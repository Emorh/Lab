//
// Created by gefre on 10.02.2020.
//

#include <iostream>
#include "Flist.h"
#include "cstring"

template <typename T>
void Flist::fwrite(const T val)
{
    this->write((char *) &val, sizeof(val));
}

template <typename T>
T Flist::fread() {
    T val;
    this->read((char *) &val, sizeof(val));
    return val;
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

Flist::Flist(char name[])
{
    this->name = new char[strlen(name) + 1];
    for (int i = 0; i < strlen(name); ++i)
    {
        this->name[i] = name[i];
    }
    this->name[strlen(name)] = '\0';

    open(name, ios::binary | ios::out | ios::in | ios::ate | ios::trunc);

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

Flist &Flist::operator>>(int &val)
{
    add(val);
    return *this;
}

void Flist::get(int ind, int &tmp)
{
    //this->seekg(3*sizeof(int) + sizeof(int)*(2*ind - 1));
    this->seekg(sizeof(int) * (2*ind + 2));
    tmp = fread<int>();
}
