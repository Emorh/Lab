
//#include <iostream>
#include <iomanip>
#include "RentalData.h"
#include "String.h"

//using namespace std;

// ~
istream &operator>>(istream &is, RentalData::DateAndTime &dt) {
    char c;
    cout << "\tDay, month and year in the format 31.01.2020: ";
    cin >> dt.day;
    if (dt.day >= 0)
    {
        cin >> c >> dt.mon >> c >> dt.year;
        cout << "\tHour: ";
        cin >> dt.hour;
    }
    else
    {
        dt.mon = -1;
        dt.year = -1;
        dt.hour = -1;
    }

    return is;
}

ostream &operator<<(ostream &os, RentalData::DateAndTime &dt) {
    cout << setw(2) << setfill('0') << dt.day << '.';
    cout << setw(2) << setfill('0') << dt.mon << '.';
    cout << dt.year << ' ';
    cout << setw(2) << setfill('0') << dt.hour;
    return os;
}

Flist &operator>>(Flist &ifl, RentalData::DateAndTime &dt) {
    ifl >> dt.day;
    ifl >> dt.mon;
    ifl >> dt.year;
    ifl >> dt.hour;
    return ifl;
}
// ~

RentalData::RentalData() : item(), cost(0.0), get(), retrieve(), surname() {}

void RentalData::extr(Flist &list, int &num, RentalData& data)
{
    if (list.len() == 0 || num < 1 || num > list.len())
    {
        throw "Array index of range";                          /////////////////////////////////// Изменить
    }

}

// ~
istream &operator>>(istream &is, RentalData &rd) {
    cout << endl;
    cout << "\tRental item: ";
    cin >> rd.item;
    cout << "\tCost: ";
    cin >> rd.cost;
    cout << "\tEnter date and time of receipt" << endl;
    cin >> rd.get;
    cout << "\tEnter date and time of return" << endl;
    cin >> rd.retrieve;
    cout << "\tSurname: ";
    cin >> rd.surname;
    return is;
}

ostream &operator<<(ostream &os, const RentalData &rd) {
    cout << "Item: ";
    return os;
}

Flist &operator>>(Flist &ifl, RentalData &rd) {
    ifl >> rd.item;
    ifl >> rd.cost;
    ifl >> rd.get;
    ifl >> rd.retrieve;
    ifl >> rd.surname;
    return ifl;
}

Flist &operator<<(Flist &of, const RentalData &rd) {
    of << rd.item;
    of.fwrite(rd.cost);

    of.fwrite(rd.get.day);
    of.fwrite(rd.get.mon);
    of.fwrite(rd.get.year);
    of.fwrite(rd.get.hour);

    of.fwrite(rd.retrieve.day);
    of.fwrite(rd.retrieve.mon);
    of.fwrite(rd.retrieve.year);
    of.fwrite(rd.retrieve.hour);

    of.fwrite(rd.surname.length());
    rd.surname.addStr(of);
    return of;
}
// ~
