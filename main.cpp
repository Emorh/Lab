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

template <typename T>
void Menu(Flist& list)
{
    char c;

    do {
        printMenu();
        cin >> c;

        T data;
        int num, len = list.len();

        switch (c) {
            case '1':
                cout << "Enter a data: ";
                cin >> data;
                list << data;
                cout << "Data added" << endl;
                break;
            case '2':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> num;
                    if (num < 1 || num > len) {
                        cout << "Wrong number" << endl;
                    } else {
                        cout << "Extracted: " << list.extr<T>(num) << endl;
                    }
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case '3':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> num;
                    if (num < 1 || num > len) {
                        cout << "Wrong number" << endl;
                    } else {
                        cout << "Deleted: " << list.del<T>(num) << endl;
                    }
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case '4':
                cout << "Enter a number up to " << len + 1 << ": ";
                cin >> num;
                if (num < 1 || num > len + 1) {
                    cout << "Wrong number" << endl;
                } else {
                    cout << "Enter a data: ";
                    cin >> data;
                    list.insByNum(num, data);
                    cout << "Data inserted" << endl;
                }
                break;
            case '5':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> num;
                    if (num < 1 || num > 1) {
                        cout << "Wrong number" << endl;
                    } else {
                        cout << "Сhange the data " << list.extr<T>(num) << " to (enter a new data): ";
                        cin >> data;
                        list.edit(num, data);
                        cout << "Data edited" << endl;
                    }
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case '6':
                cout << "Enter a data: ";
                cin >> data;
                list.insWithOrder(data);
                cout << "Data added" << endl;
                break;
            case '7':
                list.sort<T>();
                cout << "List sorted" << endl;
                break;
            case '8':
                int page;
                cout << "Enter a page: ";
                cin >> page;
                list.pageView<T>(page);
                break;
            case '9':
                list.compression<T>();
                cout << "List is compressed" << endl;
        }
    } while (c != '0');

}

int main() {
    Flist list;

    //Menu<int>(list);


    return 0;
}