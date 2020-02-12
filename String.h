#ifndef PIV_STRING_H
#define PIV_STRING_H

#include <iostream>
#include "Flist.h"

class String {
    int len;
    char *str;

public:
    String();
    ~String();
    friend istream &operator>>(istream &is, String &s);
    int length() const;

    char operator[](const int &) const;

    void addStr(Flist &) const;

    bool operator==(String& str);

    friend ostream &operator<<(ostream &, const String &);

    friend Flist &operator>>(Flist &, String &);

    friend Flist &operator<<(Flist &, const String &);
};

#endif //PIV_STRING_H
