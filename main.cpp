#include <iostream>
#include "Flist.h"

int main() {
    Flist list;

    int a = 3;
    list >> a;
    a = 3;
    list >> a;
    a = 4;
    list >> a;

    for (int i = 1; i <= 3; ++i)
    {
        int var;
        list.get(i, var);
        cout << var << " ";
    }
    cout << endl;

    return 0;
}