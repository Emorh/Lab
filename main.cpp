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
                //list.add(data);
                cout << "Data added\n";
                break;
            case '2':
                if (len != 0) { // ВЫНЕСТИ В ФУНКЦИЮ!
                    cout << "Enter a number up to " << len << ": ";
                    cin >> num;
                    if (len < num) {
                        cout << "Wrong number\n";
                    } else {
                        cout << "Extracted: " << list.extr<T>(num) << '\n';
                    }
                } else {
                    cout << "List is empty\n";
                }
                break;
            case '3':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> num;
                    if (len < num) {
                        cout << "Wrong number\n";
                    } else {
                        cout << "Deleted: " << list.del<T>(num) << '\n';
                    }
                } else {
                    cout << "List is empty\n";
                }
                break;
            case '4':
                cout << "Enter a number up to " << len + 1 << ": ";
                cin >> num;
                if (len + 1 < num) {
                    cout << "Wrong number\n";
                } else {
                    cout << "Enter a data: ";
                    cin >> data;
                    if (list.insByNum(num, data)) {
                        cout << "Data inserted\n";
                    }
                }
                break;
            case '5':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> num;
                    if (len < num) {
                        cout << "Wrong number\n";
                    } else {
                        cout << "Сhange the data " << list.extr<T>(num) << " to (enter a new data): ";
                        cin >> data;
                        if (list.edit(num, data)) {
                            cout << "Data edited\n";
                        }
                    }
                } else {
                    cout << "List is empty\n";
                }
                break;
            case '6':
                cout << "Enter a data: ";
                cin >> data;
                list.insWithOrder(data);
                cout << "Data added\n";
                break;
            case '7':
                list.sort<T>();
                cout << "List sorted\n";
                break;
            case '8':
                int page;
                cout << "Enter a page: ";
                cin >> page;
                if (page >= 1)
                {
                    list.pageView<T>(page);
                }
                else
                {
                    cout << "Wrong page\n";
                }
                break;
            case '9':
                list.compression<T>();
                cout << "List is compressed\n";
        }
    } while (c != '0');

}



int main() {
    Flist list;

    Menu<int>(list);

    return 0;
}