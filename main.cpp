#include <iostream>
#include "Flist.h"
#include "RentalData.h"

void printMenu() {
    cout << ">Select an action:" << endl;
    cout << "\t1. Add" << endl;
    cout << "\t2. Extract" << endl;
    cout << "\t3. Delete" << endl;
    cout << "\t4. Insert by number" << endl;
    cout << "\t5. Edit" << endl;
    cout << "\t6. Insert with order" << endl;
    cout << "\t7. Sort" << endl;
    cout << "\t8. Page view" << endl;
    cout << "\t9. Compression" << endl;
    cout << "\t0. Exit" << endl;
}

int main() {
    Flist list;
    RentalData rd;
    rd.inp();
    list << rd;

    list.Set(1);
    RentalData rd1;
    list >> rd1;

    /*
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