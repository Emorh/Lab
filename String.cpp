// String.cpp

#include <cstring>
#include "String.h"

String::String() : len(0), str(nullptr) {}

String::String(char s[]) {
    len = strlen(s);
    str = new char[len + 1];
    if (str == nullptr) { // Обработка ошибки
        len = 0;
        return;
    }
    strcpy(str, s);
}

String::String(const String &s) {
    len = s.len;
    str = new char[s.len + 1];
    if (str == nullptr) { // Обработка ошибки
        len = 0;
        return;
    }
    for (int i = 0; i < s.len; ++i) {
        str[i] = s.str[i];
    }
    str[s.len] = '\0';
}

String::~String() {
    delete[] str;
}

char String::operator[](const int &n) const {
    if (n >= 0 && n < len) {
        return str[n];
    }
    throw "String out of range";
}

bool String::operator==(const String &s) const {
    if (len != s.len) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (str[i] != s.str[i]) {
            return false;
        }
    }
    return true;
}

int String::length() const { return len; }

void String::addStr(Flist &of) const {
    for (int i = 0; i < len; ++i) {
        of.fwrite(str[i]);
    }
}

ostream &operator<<(ostream &os, const String &s) {
    cout << s.str;
    return os;
}

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

Flist &operator<<(Flist &of, const String &s) {

    int l = s.length();
    of << l;
    s.addStr(of);
    return of;
}

Flist &operator>>(Flist &ifl, String &s) {
    ifl >> s.len;
    s.str = new char[s.len + 1];
    if (s.str == nullptr) { // Обработка ошибки
        s.len = 0;
        return ifl;
    }
    for (int i = 0; i < s.len; ++i) {
        ifl >> s.str[i];
    }
    s.str[s.len] = '\0';
    return ifl;
}
