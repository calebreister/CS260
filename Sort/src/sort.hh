#ifndef SORT_HH
#define SORT_HH

///@file
///@author Caleb Reister <calebreister@gmail.com>

#include <algorithm>
#include <forward_list>
#include <utility>
#include <cstdint>
#include <cmath>

typedef uint32_t index;

namespace sort {
    bool radix(long data[], index size);
    void merge(long data[], index last, index first = 0);
    void quick(long data[], index size);
}

#endif // SORT_HH
