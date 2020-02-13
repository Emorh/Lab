// RentalData.cpp

#include <iomanip>
#include "RentalData.h"

RentalData::RentalData() : item(), cost(0.0), get(), retrieve(), surname() {}

void RentalData::outDT(const RentalData::DateAndTime &dt) const {
    if (dt.day > 0) {
        cout << setw(2) << setfill('0') << dt.day << '.';
        cout << setw(2) << setfill('0') << dt.mon << '.';
        cout << dt.year << ' ';
        cout << setw(2) << setfill('0') << dt.hour;
    }
    cout << endl;
}

void RentalData::inDT(RentalData::DateAndTime &dt) {
    char c;
    cout << "\tDay, month and year in the format 31.01.2020: ";
    cin >> dt.day;
    if (dt.day >= 0) {
        cin >> c >> dt.mon >> c >> dt.year;
        cout << "\tHour: ";
        cin >> dt.hour;
    } else {
        dt.mon = -1;
        dt.year = -1;
        dt.hour = -1;
    }
}

void RentalData::finDT(Flist &ifl, RentalData::DateAndTime &dt) {
    ifl >> dt.day;
    ifl >> dt.mon;
    ifl >> dt.year;
    ifl >> dt.hour;
}

bool RentalData::operator>(const RentalData &dt) const { return cost > dt.cost; }

String RentalData::getItem()        const { return item; }

double RentalData::getCost()        const { return cost; }

int    RentalData::getGetMon()      const { return get.mon; }

int    RentalData::getGetYear()     const { return get.year; }

int    RentalData::getRetrieveDay() const { return retrieve.day; }

ostream &operator<<(ostream &os, const RentalData &rd) {
    cout << "\tItem: " << rd.item << endl;
    cout << "\tCost: " << rd.cost << endl;
    cout << "\tDate&time of receipt: ";
    rd.outDT(rd.get);
    cout << "\tDate&time of return: ";
    rd.outDT(rd.retrieve);
    cout << "\tSurname: " << rd.surname << endl;
    return os;
}

istream &operator>>(istream &is, RentalData &rd) {
    cout << endl;
    cout << "\tRental item: ";
    cin >> rd.item;
    cout << "\tCost: ";
    cin >> rd.cost;
    cout << "\tEnter date and time of receipt" << endl;
    rd.inDT(rd.get);
    cout << "\tEnter date and time of return" << endl;
    rd.inDT(rd.retrieve);
    cout << "\tSurname: ";
    cin >> rd.surname;
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

Flist &operator>>(Flist &ifl, RentalData &rd) {
    ifl >> rd.item;
    ifl >> rd.cost;
    rd.finDT(ifl, rd.get);
    rd.finDT(ifl, rd.retrieve);
    ifl >> rd.surname;
    return ifl;
}
