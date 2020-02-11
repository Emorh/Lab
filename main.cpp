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


    //int c = 1;
    list.pageView<int>(1);
    list.pageView<int>(2);

    return 0;
}