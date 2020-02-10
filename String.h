//
// Created by gefre on 11.02.2020.
//

#ifndef PIV_STRING_H
#define PIV_STRING_H

#include <iostream>
#include "Flist.h"

using namespace std;

class String {
    int len;
    char *str;

public:
    String();
    ~String();
    friend istream &operator>>(istream &is, String &s);
    int length() const;

    // ~
    char operator[](const int &) const;

    // friend Flist &operator<<(Flist &, const String &);
    // ~
};



#endif //PIV_STRING_H
