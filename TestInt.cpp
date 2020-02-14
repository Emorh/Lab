//
// Created by gefre on 14.02.2020.
//

#include <ctime>
#include "TestInt.h"

TestInt::TestInt(Flist *f) {
    fl = f;
}

double TestInt::timeOfAdd(const int &count) {
    unsigned int startTime = clock();
    srand(time(nullptr));
    for (int i = 0; i < count; ++i) {
        *fl << rand();
    }
    return ((double)clock() - startTime) / 1000;
}

double TestInt::timeOfSort() {
    unsigned int startTime = clock();
    fl->sort<int>();
    return ((double)clock() - startTime) / 1000;
}
