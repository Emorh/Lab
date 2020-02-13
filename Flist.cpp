// File.cpp

#include <cstring>
#include <iostream>
#include "Flist.h"

Flist::Flist(char name[]) {
    int len = strlen(name);
    this->name = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        this->name[i] = name[i];
    }
    this->name[len] = '\0';

    open(name, ios::binary | ios::out | ios::in | ios::ate);

    if (!*this)                // Если есть какие-то проблемы с файлом
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
            fwrite(0);
        }
    }
}

Flist::~Flist() {
    delete[] name;
    close();
}

template<typename T>
void Flist::fwrite(const T &val) {
    write((char *) &val, sizeof(val));
}

template<typename T>
T Flist::fread() {
    T val;
    read((char *) &val, sizeof(val));
    return val;
}

template<typename T>
void Flist::add(const T &elem) { // Добавление в конец списка
    seekg(0);
    if (fread<int>() != 0) { // Список не пуст
        // Узнать, на каком элементе (на какой позиции) заканчивается список
        seekg(sizeof(int));
        int penultimatePos = fread<int>();
        // Обновление позиции конца списка
        seekg(0, ios::end);
        int lastPos = tellg();
        seekp(sizeof(int));
        fwrite(lastPos);
        // Обновление длины списка
        seekg(sizeof(int) * 2);
        int lenMinOne = fread<int>();
        seekp(sizeof(int) * 2);
        fwrite(lenMinOne + 1);
        // Обновление предпоследнего элемента, чтобы он знал, где находится следующий за ним
        seekp(penultimatePos);
        fwrite(lastPos);
        seekp(0, ios::end);
    } else { // Список пуст
        seekp(0);
        fwrite(sizeof(int) * 3); // Начало списка
        fwrite(sizeof(int) * 3); // Конец
        fwrite(1); // Длина
    }
    // Добавление нового элемента
    fwrite(0); // Указатель на следующий за первым
    fwrite(elem); // Данные первого
}

int Flist::len() {
    seekg(sizeof(int) * 2);
    return fread<int>();
}

void Flist::set(const int &ind) {
    int len = this->len();
    if (len == 0 || ind < 1 || ind > len) {
        throw "Index out of range";
    }
    // Извлечение последнего -- отдельный случай для ускорения
    if (ind == len) {
        seekg(sizeof(int));
        seekg(fread<int>() + sizeof(int));
    } else {
        seekg(0);
        for (int i = 1; i <= ind; ++i) {
            seekg(fread<int>());
        }
        seekg(sizeof(int), ios::cur);
    }
}

//                   <---->
// | left | -> | mid | -> | right | -> | rNext | -> ...
// (lPrev)     (left)     (mid)        (right)
// Нужно свопнуть mid и right
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

Flist &Flist::operator<<(const char &elem) {
    add<char>(elem);
    return *this;
}

Flist &Flist::operator<<(const short &elem) {
    add<short>(elem);
    return *this;
}

Flist &Flist::operator<<(const int &elem) {
    add<int>(elem);
    return *this;
}

Flist &Flist::operator<<(const double &elem) {
    add<double>(elem);
    return *this;
}

Flist &Flist::operator>>(char &elem) {
    elem = fread<char>();
    return *this;
}

Flist &Flist::operator>>(short &elem) {
    elem = fread<short>();
    return *this;
}

Flist &Flist::operator>>(int &elem) {
    elem = fread<int>();
    return *this;
}

Flist &Flist::operator>>(double &elem) {
    elem = fread<double>();
    return *this;
}
