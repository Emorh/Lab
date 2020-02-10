//
// Created by gefre on 10.02.2020.
//

#ifndef PIV_FLIST_H
#define PIV_FLIST_H

#include <fstream>
#include <iostream>

using namespace std;

class Flist : fstream {

    char* name;

    template <typename T>
    void fwrite(const T val);

    template <typename T>
    T fread();

    template <typename T>
    void add(const T &dat);

public:
    Flist(char name[] = (char*)"data.bin");

    Flist &operator>>(int &);

    int &operator<<(int&);

    void get(int ind, char& var);
    void get(int ind, short& var);
    void get(int ind, int& var);
    void get(int ind, double& var);

};


#endif //PIV_FLIST_H
