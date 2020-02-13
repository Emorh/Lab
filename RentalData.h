// RentalData.h -- класс элемента базы данных проката

#ifndef PIV_RENTALDATA_H
#define PIV_RENTALDATA_H

#include "String.h"

class RentalData {
    struct DateAndTime {
        short day;
        short mon;
        short year;
        short hour;
    };
    String item;
    double cost;
    DateAndTime get;
    DateAndTime retrieve;
    String surname;

    void outDT(const DateAndTime &) const;

    void inDT(DateAndTime &);

    void finDT(Flist &, DateAndTime &);

public:
    RentalData();

    bool operator>(const RentalData &) const;

    [[nodiscard]] String getItem() const;

    [[nodiscard]] double getCost() const;

    [[nodiscard]] int getGetMon() const;

    [[nodiscard]] int getGetYear() const;

    [[nodiscard]] int getRetrieveDay() const;

    friend ostream &operator<<(ostream &, const RentalData &);

    friend istream &operator>>(istream &, RentalData &);

    friend Flist &operator<<(Flist &, const RentalData &);

    friend Flist &operator>>(Flist &, RentalData &);
};

#endif //PIV_RENTALDATA_H
