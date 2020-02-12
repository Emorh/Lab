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

char String::operator[](const int &n) const {
    if (n >= 0 && n < len) {
        return str[n];
    }
    throw "String out of range";
}

void String::addStr(Flist &of) const {
    for (int i = 0; i < len; ++i) {
        of.fwrite(str[i]);
    }
}

ostream &operator<<(ostream &os, const String &s) {
    cout << s.str;
    return os;
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

Flist &operator<<(Flist &of, const String &s) {

    int l = s.length();
    of << l;
    s.addStr(of);
    return of;
}

bool String::operator==(String &str)
{
    if (len != str.len)
    {
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        if (this->str[i] != str.str[i])
        {
            return false;
        }
    }

    return true;
}
