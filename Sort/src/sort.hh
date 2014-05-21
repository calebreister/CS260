#ifndef SORT_HH
#define SORT_HH

///@file
///@author Caleb Reister <calebreister@gmail.com>

#include <algorithm>
#include <forward_list>
#include <utility>
#include <cstdint>
#include <cmath>

namespace sort {
    bool radix(long data[], uint32_t size);
    void merge(long data[], uint32_t last, uint32_t first = 0);
    void quick(long data[], uint32_t last, uint32_t first = 0);
}

#endif // SORT_HH
