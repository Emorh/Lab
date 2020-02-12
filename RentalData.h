#ifndef PIV_RENTALDATA_H
#define PIV_RENTALDATA_H

#include "String.h"
#include "Flist.h"

class RentalData {
private:
    struct DateAndTime {
        short day; // попробовать сделать char-ы
        short mon;
        short year;
        short hour;
    };
    String item;
    double cost;
    DateAndTime get;
    DateAndTime retrieve;
    String surname;

    void inDT(DateAndTime &);

    void outDT(const DateAndTime &) const;

    void finDT(Flist &, DateAndTime &);

public:
    RentalData();

    String getItem() const;

    double getCost() const;

    int getGetMon() const;

    int getGetYear() const;

    int getRetrieveDay() const;

    bool operator>(RentalData &dt) { return cost > dt.cost; }

    friend istream &operator>>(istream &, RentalData &);

    friend ostream &operator<<(ostream &, const RentalData &);

    friend Flist &operator>>(Flist &, RentalData &);

    friend Flist &operator<<(Flist &, const RentalData &);


};

#endif //PIV_RENTALDATA_H
