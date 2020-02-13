// String.h

#ifndef PIV_STRING_H
#define PIV_STRING_H

#include <iostream>
#include "Flist.h"

class String {
    int len;
    char *str;
public:
    String();
    explicit String(char []);
    String(const String &);
    ~String();

    char operator[](const int &) const;

    bool operator==(const String &s) const;

    [[nodiscard]] int length() const;

    void addStr(Flist &) const;

    friend ostream &operator<<(ostream &, const String &);

    friend istream &operator>>(istream &is, String &s);

    friend Flist &operator<<(Flist &, const String &);

    friend Flist &operator>>(Flist &, String &);
};

#endif //PIV_STRING_H
