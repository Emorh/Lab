#include <iostream>
#include "Flist.h"
#include "RentalData.h"

int main() {
    Flist list;

    for (int i = 1; i <= 5; ++i)
    {
        list << i;
    }

    for (int i = 1; i <= list.len(); ++i)
    {
        cout << list.extr<int>(i) << " ";
    }
    cout << endl;

    int a = 10;
    list.edit(3, a);

    for (int i = 1; i <= list.len(); ++i)
    {
        cout << list.extr<int>(i) << " ";
    }
    cout << endl;
    //list.del<int>(1);
    //list.del<int>(2);
    //list.del<int>(3);
    //list.insByNum<int>(2, 10);


    /*
    RentalData rd;
    list << rd;
    //rd.

    int a = 1;
    list << a;
    a = 2;
    list << a;
    a = 3;
    list << a;

    for (int i = 1; i <= 3; ++i)
    {
        int tmp;
        list.extr(i, tmp);
        cout << tmp << " ";
    }
    cout << endl;
*/
    return 0;
}