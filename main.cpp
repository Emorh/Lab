// Проект на курсовую по Программированию (3 семестр, 2 курс) Бисеровой Эвелины из группы ДТ-860.
// Преподаватель: Васюткина И. А.
// Тема "Динамические структуры данных в файле"

// C++17, IDE -- CLion 2019.2.4
// main.cpp

// Возвращаемые коды программы (коды ошибок):
// 1 -- невозможно открыть файл с бд
// 2 -- невозможно удалить файл с бд
// 3 -- невозможно переименовать файл с бд

#include <cmath>
#include "RentalData.h"

double calcOfAmountGoods(Flist &fl, String &s) {
    double sum = 0;
    for (int i = 1; i <= fl.len(); ++i) {
        auto elem = fl.extr<RentalData>(i);
        if (elem.getItem() == s && elem.getRetrieveDay() > 0) {
            sum += elem.getCost();
        }
    }
    return sum;
}

double monthlyIncome(Flist &fl, int mon, int year) {
    double sum = 0;
    for (int i = 1; i <= fl.len(); ++i) {
        auto elem = fl.extr<RentalData>(i);
        if (elem.getGetMon() == mon && elem.getGetYear() == year && elem.getRetrieveDay() > 0) {
            sum += elem.getCost();
        }
    }
    return sum;
}

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

template<typename T>
void menu(Flist &fl) {
    char c;
    do {
        printMenu();
        cin >> c;

        T data;
        int ind, len = fl.len();

        switch (c) {
            case '1':
                cout << "Enter a data: ";
                cin >> data;
                fl << data;
                cout << "Data added" << endl;
                break;

            case '2':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> ind;
                    if (ind < 1 || ind > len) {
                        cout << "Wrong number" << endl;
                    } else {
                        cout << "Extracted: " << fl.extr<T>(ind) << endl;
                    }
                } else {
                    cout << "List is empty" << endl;
                }
                break;

            case '3':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> ind;
                    if (ind < 1 || ind > len) {
                        cout << "Wrong number" << endl;
                    } else {
                        cout << "Deleted: " << fl.del<T>(ind) << endl;
                    }
                } else {
                    cout << "List is empty" << endl;
                }
                break;

            case '4':
                cout << "Enter a number up to " << len + 1 << ": ";
                cin >> ind;
                if (ind < 1 || ind > len + 1) {
                    cout << "Wrong number" << endl;
                } else {
                    cout << "Enter a data: ";
                    cin >> data;
                    fl.insByNum(ind, data);
                    cout << "Data inserted" << endl;
                }
                break;
            case '5':
                if (len != 0) {
                    cout << "Enter a number up to " << len << ": ";
                    cin >> ind;
                    if (ind < 1 || ind > len + 1) {
                        cout << "Wrong number" << endl;
                    } else {
                        cout << "Сhange the data " << fl.extr<T>(ind) << " to (enter a new data): ";
                        cin >> data;
                        fl.edit(ind, data);
                        cout << "Data edited" << endl;
                    }
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case '6':
                cout << "Enter a data: ";
                cin >> data;
                fl.insWithOrder(data);
                cout << "Data added" << endl;
                break;
            case '7':
                fl.sort<T>(); // По стоимости
                cout << "List sorted" << endl;
                break;
            case '8':
                int page;
                cout << "Enter a page to " << ceil((double)fl.len() / fl.numOfRecords) << " (";
                cout << fl.numOfRecords << " elements per page): ";
                cin >> page;
                if (page < 1 || fl.len() <= (page - 1) * fl.numOfRecords) {
                    cout << "Wrong page" << endl;
                } else {
                    fl.pageView<T>(page);
                }
                break;
            case '9':
                fl.compress<T>();
                cout << "List is compressed" << endl;
            default:
                cout << endl;
        }
    } while (c != '0');

    // Закомментировать, если вносим int-ы!!!
    static_assert(!is_integral<T>::value && !is_floating_point<T>::value,
                  "Only RentalData class! Please comment code");
    String item((char *)"laptop");
    cout << "Amount of payment for the " << item << ": " << calcOfAmountGoods(fl, item) << endl;

    int mon = 1, year = 2020;
    cout << setw(2) << setfill('0') << mon << '.' << year << " income: " << monthlyIncome(fl, mon, year) << endl;
}

int main() {
    Flist list;
    menu<RentalData>(list);
    return 0;
}
