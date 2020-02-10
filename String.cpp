//
// Created by gefre on 11.02.2020.
//
#include <cstring>
#include "String.h"

String::~String()
{
    delete[] str;
}

String::String() : len(0), str(nullptr) {}

istream &operator>>(istream &is, String &s) {
    char tmp[64];
    is >> tmp;
    delete[] s.str;

    s.len = strlen(tmp);
    s.str = new char[s.len + 1];
    if (s.str == nullptr) { // Обработка ошибки
        s.len = 0;
        return is;
    }
    strcpy(s.str, tmp);
    return is;
}

int String::length() const { return len; }

// ~
char String::operator[](const int &n) const {
    if (n >= 0 && n < len) {
        return str[n];
    }
    throw "String out of range";
}

/*
Flist &operator<<(Flist &of, const String &s) {

   of << s.len;
   for (int i = 0; i < s.len; ++i) {
       of.fwrite(s[i]);
   }
   return of;
}
 */