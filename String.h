//
// Created by gefre on 11.02.2020.
//

#ifndef PIV_STRING_H
#define PIV_STRING_H

#include <iostream>
#include "Flist.h"

//using namespace std;

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

    void addStr(Flist &) const;

    friend Flist &operator<<(Flist &, const String &);

    friend Flist &operator>>(Flist &, String &);
    // ~
};



#endif //PIV_STRING_H
