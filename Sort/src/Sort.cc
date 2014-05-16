/**@file Sort.cc
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <forward_list>
#include <cstdlib>
#include <cstdint>
#include <cmath>
using namespace std;

namespace sort {
    bool radix(int data[], uint32_t size);
    void merge(int data[], uint32_t first, uint32_t last);
    void quick(int data[], uint32_t size);
}

int main() {
    int x[8] = {3, 5, 1, 2, 4, 0, 10, 3};
    for (int i = 0; i < 8; i++)
        cout << x[i] << endl;
    sort::radix(x, 8);
    cout << endl;
    for (int i = 0; i < 8; i++)
        cout << x[i] << endl;
}

/**@brief Implements a radix sort, only works for positive integers
   @param data The array to sort
 */
bool sort::radix(int data[], uint32_t size) {
    //make sure there are no negative values and find the largest value
    int places = data[0]; //will store the number of digits
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
   @param first The starting position in the array
   @param last The ending position in the array (1 + index)
 */
void sort::merge(int data[], uint32_t first, uint32_t last) {
    const uint32_t SIZE = last - first;
    const uint32_t mid = (last - first) / 2;

    if (SIZE == 1)
        return;
    else if (SIZE == 2)
    {
        if (data[0] > data[1])
            swap(data[0], data[1]);
    }
    else
    {
        //separate
        int* left = new int[mid];

        const uint32_t SIZE_right = last - mid;
        int* right = new int[SIZE_right];

        for (uint32_t i = 0; i < mid; i++)
            left[i] = data[i];

        uint32_t r = 0;
        for (uint32_t d = mid; d < last; d++)
        {
            //d = data index
            //r = right index
            right[r++] = data[d];
        }

        ///////////////////////////////////////
        sort::merge(left, 0, mid);
        sort::merge(right, 0, SIZE_right);

        ///////////////////////////////////////
        //merge
        uint32_t l = 0; //left index
        r = 0;          //right index
        uint32_t d = 0; //data index
        while (l < mid && r < SIZE_right)
        {
            if (left[l] < right[r])
                data[d] = left[l++];
            else if (right[r] < left[l])
                data[d] = right[r++];
            else
            {
                data[d++] = right[r++];
                data[d] = left[l++];
            }
            d++;
        }
        //deal with uneven datasets
        while (l < mid)
            data[d++] = left[l++];
        while (r < mid)
            data[d++] = right[r++];

        delete [] left;
        delete [] right;
    }
}

void sort::quick(int data[], uint32_t size) {

}
