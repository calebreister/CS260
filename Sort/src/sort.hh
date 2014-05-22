#ifndef SORT_HH
#define SORT_HH

///@file
///@author Caleb Reister <calebreister@gmail.com>

#include <utility>
#include <cstdint>

typedef uint32_t index;

///@brief A container for sorting algorithm functions.
namespace sort {
    void merge(long data[], index last, index first = 0);
    void quick(long data[], index size);
    void heap(long data[], index size);
}

#endif // SORT_HH
