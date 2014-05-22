///@file Sort.cc
///@author Caleb Reister <calebreister@gmail.com>

#include "sort.hh"
using namespace std;

/**@brief an array-merging function used by sort::merge(), used to merge two arrays,
          only locally accessible
   @param result the destination array (should be big enough to hold a and b
   @param a the first array to merge
   @param aSize the size of a
   @param b the second array to merge
   @param bSize the size of b

> function merge(left,right)
>> var list result
>> while length(left) > 0 and length(right) > 0
>>> if first(left) ≤ first(right)
>>>> append first(left) to result
>>>> left = rest(left)
>>> else
>>>> append first(right) to result
>>>> right = rest(right)
>> if length(left) > 0
>>> append rest(left) to result
>> if length(right) > 0
>>> append rest(right) to result
>> return result
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

/**@brief A function used in sort::heap(), sifting is a term used to describe the
          deletion of a parent node in a binary tree. This basically does the
          same in an array.
   @param data The array to sift
   @param start The starting bound index
   @param end The last index to evaluate

1. Find the highest element
2. Find a non-parent element
3. "Remove" the child element and replace the parent element
4. Swap the formerly child element if necessary


    function siftDown(a, start, end) is
        (end represents the limit of how far down the heap to sift)
        root := start
        while root * 2 + 1 ≤ end do       (While the root has at least one child)
            child := root * 2 + 1           (root*2+1 points to the left child)
            (If the child has a sibling and the child's value is less than its sibling's...)
            if child + 1 ≤ end and a[child] < a[child + 1] then
                child := child + 1           (... then point to the right child instead)
            if a[root] < a[child] then     (out of max-heap order)
                swap(a[root], a[child])
                root := child                (repeat to continue sifting down the child now)
            else
                return


~~~~~{.c}
void siftDown( ValType *a, int start, int end)
{
    int root = start;

    while ( root*2+1 < end ) {
        int child = 2*root + 1;
        if ((child + 1 < end) && IS_LESS(a[child],a[child+1])) {
            child += 1;
        }
        if (IS_LESS(a[root], a[child])) {
            SWAP( a[child], a[root] );
            root = child;
        }
        else
            return;
    }
}
~~~~~
*/
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

/**@brief A recursive merge sort algorithm
   @param data The array to sort
   @param last The ending position in the array (1 + index)
   @param first The starting position in the array

Also See mergeData().

Best case: O(n*lg(n))\n
Worst case: O(n^2)\n
Average case: O(n*lg(n))

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


/**@brief Implements recursive quick sort
   @param data The array to sort
   @param size The length of the array

Best case: O(n*lg(n))\n
Worst case: O(n^2)\n
Average case: O(n*lg(n))

###Based off of the following code...

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

~~~~~~~~~~{.c}
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
     }
~~~~~~~~~~
*/
void sort::quick(long data[], index size) {
    if (size <= 1)
        return;

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
            continue; //I could not think of a better way to do this
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


/**@brief Implements recursive heap sort, treats the array similar to a binary
          tree
   @param data The array to sort
   @param size The size of the array

Also see siftDown().

Best case: O(n*lg(n))\n
Worst case: O(n^2)

* Treats the array as a binary tree
* Repeatedly removes the highest element

> The basic idea is to turn the array into a binary heap structure, which has
> the property that it allows efficient retrieval and removal of the maximal
> element. We repeatedly "remove" the maximal element from the heap, thus
> building the sorted list from back to front. ~Definition on rosettacode.org

###Based off of the following code...

    function heapSort(a, count) is
       input: an unordered array a of length count

       (first place a in max-heap order)
       heapify(a, count)

       end := count - 1
       while end > 0 do
          (swap the root(maximum value) of the heap with the
           last element of the heap)
          swap(a[end], a[0])
          (decrement the size of the heap so that the previous
           max value will stay in its proper place)
          end := end - 1
          (put the heap back in max-heap order)
          siftDown(a, 0, end)

    function heapify(a,count) is
       (start is assigned the index in a of the last parent node)
       start := (count - 2) / 2

       while start ≥ 0 do
          (sift down the node at index start to the proper place
           such that all nodes below the start index are in heap
           order)
          siftDown(a, start, count-1)
          start := start - 1
       (after sifting down the root all nodes/elements are in heap order)

~~~~~~~~~~{.c}
#include <stdio.h>
#include <stdlib.h>

#define ValType double
#define IS_LESS(v1, v2)  (v1 < v2)

void siftDown( ValType *a, int start, int count);

#define SWAP(r,s)  do{ValType t=r; r=s; s=t; } while(0)

void heapsort( ValType *a, int count)
{
    int start, end;

    // heapify
    for (start = (count-2)/2; start >=0; start--) {
        siftDown( a, start, count);
    }

    for (end=count-1; end > 0; end--) {
        SWAP(a[end],a[0]);
        siftDown(a, 0, end);
    }
}
~~~~~~~~~~
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
