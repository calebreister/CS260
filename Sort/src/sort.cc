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
void mergeData(long result[], long a[], index aSize,
               long b[], index bSize) {
    index ri = 0, //result index
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#python2.6 <
from math import log

def getDigit(num, base, digit_num):
    # pulls the selected digit
    return (num // base ** digit_num) % base

def makeBlanks(size):
    # create a list of empty lists to hold the split by digit
    return [ [] for i in range(size) ]

def split(a_list, base, digit_num):
    buckets = makeBlanks(base)
    for num in a_list:
        # append the number to the list selected by the digit
        buckets[getDigit(num, base, digit_num)].append(num)
    return buckets

# concatenate the lists back in order for the next step
def merge(a_list):
    new_list = []
    for sublist in a_list:
       new_list.extend(sublist)
    return new_list

def maxAbs(a_list):
    # largest abs value element of a list
    return max(abs(num) for num in a_list)

def split_by_sign(a_list):
    # splits values by sign - negative values go to the first bucket,
    # non-negative ones into the second
    buckets = [[], []]
    for num in a_list:
        if num < 0:
            buckets[0].append(num)
        else:
            buckets[1].append(num)
    return buckets

def radixSort(a_list, base):
    # there are as many passes as there are digits in the longest number
    passes = int(round(log(maxAbs(a_list), base)) + 1)
    new_list = list(a_list)
    for digit_num in range(passes):
        new_list = merge(split(new_list, base, digit_num))
    return merge(split_by_sign(new_list))
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
bool sort::radix(long data[], index size) {
    if (size == 1)
        return true;
    else if (size == 2)
    {
        if (data[0] > data[1])
            swap(data[0], data[1]);
        return true;
    }

    //make sure there are no negative values and find the largest value
    index places = data[0]; //will store the number of digits
    for (index i = 0; i < size; i++)
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
    for (index d = 0; d < size; d++) //data iteration
    {
        index p = log10(data[d]); //place to use
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
    index d = 0; //data iteration
    //d does not need to be checked, we know that the exact number
    //of list elements matches the size of d
    for (index p = 0; p < places; p++) //place iteration
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
