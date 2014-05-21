///@file Sort.cc
///@author Caleb Reister <calebreister@gmail.com>

#include "sort.hh"
using namespace std;

/**@brief merge function used by merge sort, used to merge two arrays,
          only locally accessible
   @param result the destination array (should be big enough to hold a and b
   @param a the first array to merge
   @param aSize the size of a
   @param b the second array to merge
   @param bSize the size of b

    function merge(left,right)
       var list result
       while length(left) > 0 and length(right) > 0
           if first(left) ≤ first(right)
               append first(left) to result
               left = rest(left)
           else
               append first(right) to result
               right = rest(right)
       if length(left) > 0
           append rest(left) to result
       if length(right) > 0
           append rest(right) to result
       return result
*/
void mergeData(long data[], long a[], index aSize,
               long b[], index bSize) {
    index di = 0, //data index
             ai = 0, //a index
             bi = 0; //b index

    while (ai < aSize && bi < bSize)
    {
        if (a[ai] <= b[bi])
            data[di++] = a[ai++];
        else
            data[di++] = b[bi++];
    }

    if (ai < aSize)
    {
        while (ai < aSize)
            data[di++] = a[ai++];
    }

    if (bi < bSize)
    {
        while (bi < bSize)
            data[di++] = b[bi++];
    }
}

void siftDown(long data[], index start, index end) {
    index root = start;
    index child;

    while (root * 2 + 1 < end)
    {
        child = 2 * root + 1;
        if ((child + 1 < end) && (data[child] < data[child + 1]))
            child++;
        if (data[root] < data[child])
        {
            swap(data[child], data[root]);
            root = child;
        }
        else return;
    }
}

///////////////////////////////////////////////////////////////////////////////
//SORTING ALGORITHMS

/**@brief Implements a complete recursive merge sort (low values on top),
          entirely self-contained.
   @param data The array to sort
   @param last The ending position in the array (1 + index)
   @param first The starting position in the array

    function mergesort(m)
       var list left, right, result
       if length(m) ≤ 1
           return m
       else
           var middle = length(m) / 2
           for each x in m up to middle - 1
               add x to left
           for each x in m at and after middle
               add x to right
           left = mergesort(left)
           right = mergesort(right)
           if last(left) ≤ first(right)
              append right to left
              return left
           result = merge(left, right)
           return result
*/
void sort::merge(long data[], index last, index first) {
    const index SIZE = last - first;
    const index MID = SIZE / 2;

    if (SIZE <= 1)
        return;
    if (SIZE == 2)
    {
        if (data[0] > data[1])
            swap(data[0], data[1]);
        return;
    }

    //create sub-arrays
    long* left = new long[MID];
    const index right_SIZE = SIZE - MID;
    long* right = new long[right_SIZE];

    //fill left array
    for (index l = 0; l < MID; l++)
        left[l] = data[l];

    for (index r = 0; r < right_SIZE; r++)
        right[r] = data[r + MID];

    ///////////////////////////////////////
    sort::merge(left, MID);
    sort::merge(right, right_SIZE);
    if (left[MID - 1] <= right[0]) // end of left <= beginning of right
    {
        //append right to left
        for (index l = 0; l < MID; l++)
            data[l] = left[l];
        for (index r = 0; r < right_SIZE; r++)
            data[r + MID] = right[r];
        delete [] left;
        delete [] right;
        return;
    }

    mergeData(data, left, MID, right, right_SIZE);

    delete [] left;
    delete [] right;
}

/**@brief Implements quick sort
   @param data The array to sort
   @param last The end of the data range within the array (size in most cases)
   @param first The beginning of the data range, primarily used in recursion

**Based off of the following code...**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
 void quick_sort (int *a, int n) {
    if (n < 2)
        return;
    int p = a[n / 2];
    int *l = a;
    int *r = a + n - 1;
    while (l <= r) {
        if (*l < p) {
            l++;
            continue;
        }
        if (*r > p) {
            r--;
            continue;
        }
        int t = *l;
        *l++ = *r;
        *r-- = t;
    }
    quick_sort(a, r - a + 1);
    quick_sort(l, a + n - l);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
*/
void sort::quick(long data[], index size) {
    if (size <= 1)
        return;
    else if (size == 2)
    {
        if (data[0] > data[1])
            swap(data[0], data[1]);
        return;
    }

    long pivot = data[size / 2];
    long *left = data;
    long *right = data + size - 1;
    while (left <= right)
    {
        //the loop condition must be checked every time either left or right
        //is changed
        if (*left < pivot)
        {
            left++;
            continue;
        }
        if (*right > pivot)
        {
            right--;
            continue;
        }

        long temp = *left;
        *left++ = *right;
        *right-- = temp;
    }
    sort::quick(data, right - data + 1);
    sort::quick(left, data + size - left);
}

/**
*/
void sort::heap(long data[], index size) {
    //heapify the data
    for (int64_t start = (size - 2) / 2; start >= 0; start--)
        siftDown(data, start, size);

    for (int64_t end = size - 1; end > 0; end--)
    {
        swap(data[end], data[0]);
        siftDown(data, 0, end);
    }
}
