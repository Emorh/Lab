//
// Created by gefre on 14.02.2020.
//

#ifndef PIV_TESTINT_H
#define PIV_TESTINT_H

#include "Flist.h"

class TestInt {
    Flist *fl;
public:
    explicit TestInt(Flist *);

    double timeOfAdd(const int &count = 10'000);

    double timeOfSort();
};


#endif //PIV_TESTINT_H
