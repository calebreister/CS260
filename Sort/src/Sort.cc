/**@file Sort.cc
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
using namespace std;

namespace sort {
    void radix(int data[], uint32_t size);
    void merge(int data[], uint32_t first, uint32_t last);
    void quick(int data[], uint32_t size);
}

int main() {
    int x[8] = {3, 5, 1, 2, 4, 0, 10, 3};
    for (int i = 0; i < 8; i++)
        cout << x[i] << endl;
    sort::merge(x, 0, 8);
    cout << endl;
    for (int i = 0; i < 8; i++)
        cout << x[i] << endl;
}

void sort::radix(int data[], uint32_t size) {

}

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
