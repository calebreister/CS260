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
void mergeData(long result[], long a[], uint32_t aSize, long b[], uint32_t bSize) {
    uint32_t ri = 0, //result index
             ai = 0, //a index
             bi = 0; //b index

    while (ai < aSize && bi < bSize)
    {
        if (a[ai] <= b[bi])
            result[ri++] = a[ai++];
        else
            result[ri++] = b[bi++];
    }

    if (ai < aSize)
    {
        while (ai < aSize)
            result[ri++] = a[ai++];
    }

    if (bi < bSize)
    {
        while (bi < bSize)
            result[ri++] = b[bi++];
    }
}

///////////////////////////////////////////////////////////////////////////////
//SORTING ALGORITHMS

/**@brief Implements a radix sort, only works for positive integers
   @param data The array to sort
   @param size The size of the array
*/
bool sort::radix(long data[], uint32_t size) {
    if (size == 1)
        return true;
    else if (size == 2)
    {
        if (data[0] > data[1])
            swap(data[0], data[1]);
        return true;
    }

    //make sure there are no negative values and find the largest value
    uint32_t places = data[0]; //will store the number of digits
    for (uint32_t i = 0; i < size; i++)
    {
        if (data[i] < 0)
            return false;
        if (data[i] > places)
            places = data[i];
    }
    places = log10(places) + 1; //the number of decimal places

    //create an array of linked lists to store the values of each place in
    //[0] stores data that is in the 1's place
    //[1] stores data that is in the 10's place...
    forward_list<int>* bucket = new forward_list<int>[places];

    //build lists in order
    for (uint32_t d = 0; d < size; d++) //data iteration
    {
        uint32_t p = log10(data[d]); //place to use
        //insert data into list
        //data is lowest in place
        if (bucket[p].empty() || data[d] < bucket[p].front())
            bucket[p].push_front(data[d]);
        else
        {
            //list iterators
            forward_list<int>::iterator l_lead = bucket[p].begin();
            forward_list<int>::iterator l_trail;
            while (l_lead != bucket[p].end() && *l_lead < data[d])
            {
                l_trail = l_lead;
                l_lead++;
            }
            bucket[p].insert_after(l_trail, data[d]);
        } //else
    } //data

    //move sorted data from the bucket array to the data array
    uint32_t d = 0; //data iteration
    //d does not need to be checked, we know that the exact number
    //of list elements matches the size of d
    for (uint32_t p = 0; p < places; p++) //place iteration
    {
        while (!bucket[p].empty()) //empty list
        {
            data[d++] = bucket[p].front();
            bucket[p].pop_front();
        } //empty
    } //place

    delete [] bucket;
    return true;
}

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
void sort::merge(long data[], uint32_t last, uint32_t first) {
    const uint32_t SIZE = last - first;
    const uint32_t MID = SIZE / 2;

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
    const uint32_t right_SIZE = SIZE - MID;
    long* right = new long[right_SIZE];

    //fill left array
    for (uint32_t l = 0; l < MID; l++)
        left[l] = data[l];

    for (uint32_t r = 0; r < right_SIZE; r++)
        right[r] = data[r + MID];

    ///////////////////////////////////////
    sort::merge(left, MID);
    sort::merge(right, right_SIZE);
    if (left[MID - 1] <= right[0]) // end of left <= beginning of right
    {
        //append right to left
        for (uint32_t l = 0; l < MID; l++)
            data[l] = left[l];
        for (uint32_t r = 0; r < right_SIZE; r++)
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

   function quicksort(array)
    if length(array) > 1
        pivot := select any element of array
        left := first index of array
        right := last index of array
        while left ≤ right
            while array[left] < pivot
                left := left + 1
            while array[right] > pivot
                right := right - 1
            if left ≤ right
                swap array[left] with array[right]
                left := left + 1
                right := right - 1
        quicksort(array from first index to right)
        quicksort(array from left to last index)
*/
void sort::quick(long data[], uint32_t last, uint32_t first) {
    uint32_t size = last - first;
    if (size <= 1)
        return;
    else if (size == 2)
    {
        if (data[0] > data[1])
            swap(data[0], data[1]);
        return;
    }

    uint32_t pivot = size / 2;

    //putting data in linked lists should be more
    //time-efficient than having to constantly reorganize an array
    //theoretically, it should be possible to organize the array
    //without a bunch of extra copying
    //note that I'm not sorting the data within the lists like I did
    //with radix sort

    forward_list<int> bin[3];
    //bin[0]: data < pivot
    //bin[1]: data == pivot
    //bin[2]: data > pivot

    //sort data
    for (uint32_t i = first; i < last; i++)
    {
        if (data[i] < data[pivot]) //less
            bin[0].push_front(data[i]);
        else if (data[i] > data[pivot]) //greater
            bin[2].push_front(data[i]);
        else //equal
            bin[1].push_front(data[i]);
    }

    uint32_t pivotRange[2];
    //the starting and ending indices of the data == pivot

    //put sorted data in array
    uint32_t index = first;
    for (uint8_t b = 0; b < 3; b++) //cycle thru bins
    {
        if (b == 1)
            pivotRange[0] = index;

        while (!bin[b].empty()) //copy list contents to array
        {
            data[index] = bin[b].front();
            bin[b].pop_front();
            index++;
        }

        if (b == 1)
            pivotRange[1] = index;
    }

    //recursion recursion recursion recursion....
    sort::quick(data, pivotRange[0], first);
    sort::quick(data, last, pivotRange[1]);
}
