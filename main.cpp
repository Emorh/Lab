#include <iostream>
#include "Flist.h"
#include "RentalData.h"

int main() {
    Flist list;

    int a = 2;
    list << a;
    a = -1;
    list << a;
    a = 3;
    list << a;
    a = 1;
    list << a;
    a = 8;
    list << a;

    for (int i = 1; i <= list.len(); ++i)
    {
        cout << list.extr<int>(i) << " ";
    }


    return 0;
}