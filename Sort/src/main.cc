///@file
///@author Caleb Reister <calebreister@gmail.com>

//#define CHECK_SORT

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include "sort.hh"
#include "time.h"
using namespace std;

enum SortMode {QUICK, MERGE, RADIX};
enum DataOrder {ORDERED, REVERSE, RANDOM};

double timeSort(ostream& out, SortMode mode, DataOrder order,
                 uint32_t minSize, uint32_t maxSize);

int main() {
    runSortTest(cout, MERGE, RANDOM, 1000, 1000);
}

///////////////////////////////////////////////////////////////////////////////
double timeSort(ostream& out, SortMode mode, DataOrder order,
                 uint32_t minSize, uint32_t maxSize) {
    long* data;
    for (uint32_t size = minSize; size <= maxSize; size *= 10)
    {
        data = new long[size];

        switch (order) {
        case RANDOM:
            srand(42);
            for (uint32_t i = 0; i < size; i++)
                data[i] = rand();
            break;
        case ORDERED:
            for (uint32_t i = 0; i < maxSize; i++)
                data[i] = i;
            break;
        case REVERSE:
            long val = static_cast<long>(maxSize - 1);
            for (uint32_t i = 0; i < maxSize; i++)
                data[i] = val--;
            break;
        }

        switch (mode) {
        case QUICK:
            sort::quick(data, size);
            break;
        case MERGE:
            sort::merge(data, size);
            break;
        case RADIX:
            sort::radix(data, size);
            break;
        }

        #ifdef CHECK_SORT
        for (uint32_t i = 1; i < size; i++)
            assert(data[i] >= data[i - 1]);
        cout << "data valid";
        #else

        #endif

        delete [] data;
    }
}
