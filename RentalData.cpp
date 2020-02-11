
#include <iostream>
#include "RentalData.h"
#include "String.h"

using namespace std;

void RentalData::DateAndTime::inp() {
    char c;
    cout << "\tDay, month and year in the format 31.01.2020: ";
    cin >> day >> c >> mon >> c >> year;
    cout << "\tHour: ";
    cin >> hour;
}

/*
// ~
Flist &operator>>(Flist &is, RentalData::DateAndTime &dt) {
    is >> dt.day;
    is >> dt.mon;
    is >> dt.year;
    is >> dt.hour;
    return is;
}
// ~
*/

RentalData::RentalData() : item(), cost(0.0), get(), retrieve(), surname() {}

// ~
/*
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

    **************************************************
    of.fwrite(rd.surname.length());
    for (int i = 0; i < rd.surname.length(); ++i) {
        try {
            of.fwrite(rd.surname[i]);
        }
        catch (char err[]) {
            cerr << err;
            break;
        }
    } ********************************************
    of << rd.surname;

    return of;
}
*/
// ~

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


void RentalData::extr(Flist &list, int &num, RentalData& data)
{
    if (list.len() == 0 || num < 1 || num > list.len())
    {
        throw "Array index of range";                          /////////////////////////////////// Изменить
    }




}
/*
// ~
Flist &operator>>(Flist &is, RentalData &rd) {
    is >> rd.item;
    is >> rd.cost;
    is >> rd.get;
    is >> rd.retrieve;
    is >> rd.surname;
    return is;
}
// ~
 */
