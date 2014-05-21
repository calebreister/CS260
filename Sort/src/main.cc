///@file
///@author Caleb Reister <calebreister@gmail.com>

//#define CHECK_SORT

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include "sort.hh"
#include "timePatch.h"
using namespace std;

enum SortMode {QUICK, MERGE, RADIX};
enum DataOrder {ORDERED, REVERSE, RANDOM};

double timeSort(SortMode mode, DataOrder order, uint32_t size);

int main() {
    cout << timeSort(QUICK, RANDOM, 100000);
}



///////////////////////////////////////////////////////////////////////////////
double timeSort(SortMode mode, DataOrder order, uint32_t size) {
    double startTime;
    double timeTaken;

    long* data = new long[size];

    switch (order) {
    case RANDOM:
        srand(42);
        for (uint32_t i = 0; i < size; i++)
            data[i] = rand();
        break;
    case ORDERED:
        for (uint32_t i = 0; i < size; i++)
            data[i] = i;
        break;
    case REVERSE:
        long val = static_cast<long>(size - 1);
        for (uint32_t i = 0; i < size; i++)
            data[i] = val--;
        break;
    }

    //TIMED ZONE
    startTime = get_cpu_time();
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
    timeTaken = get_cpu_time() - startTime;
    //END TIMED ZONE

    #ifdef CHECK_SORT
    for (uint32_t i = 1; i < size; i++)
        assert(data[i] >= data[i - 1]);
    cout << "data valid";
    #endif

    delete [] data;
    return timeTaken;
}
