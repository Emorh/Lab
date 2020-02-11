
#include <iostream>
#include "RentalData.h"
#include "String.h"

//using namespace std;

void RentalData::DateAndTime::inp() {
    char c;
    cout << "\tDay, month and year in the format 31.01.2020: ";
    cin >> day >> c >> mon >> c >> year;
    cout << "\tHour: ";
    cin >> hour;
}

RentalData::RentalData() : item(), cost(0.0), get(), retrieve(), surname() {}

void RentalData::inp() {
    cout << endl;
    cout << "\tRental item: ";
    cin >> item;
    cout << "\tCost: ";
    cin >> cost;
    cout << "\tEnter date and time of receipt" << endl;
    get.inp();
    cout << "\tEnter date and time of return" << endl;
    retrieve.inp();
    cout << "\tSurname: ";
    cin >> surname;
}

Flist &operator>>(Flist &is, RentalData::DateAndTime &dt) {
    is >> dt.day;
    is >> dt.mon;
    is >> dt.year;
    is >> dt.hour;
    return is;
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

Flist &operator>>(Flist &is, RentalData &rd) {
    is >> rd.item;
    is >> rd.cost;
    is >> rd.get;
    is >> rd.retrieve;
    is >> rd.surname;
    return is;
}
