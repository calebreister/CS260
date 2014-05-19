/**@file
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "sort.hh"
#include "time.h"
using namespace std;

void generateDataOrdered(int a[], uint32_t size);
void generateDataReverse(int a[], uint32_t size);
void generateDataRandom(int a[], uint32_t size);

int main() {

}

///////////////////////////////////////////////////////////////////////////////
//DATA GENERATORS
void generateDataOrdered(int a[], uint32_t size) {
    for (uint32_t i = 0; i < size; i++)
        a[i] = i;
}

void generateDataReverse(int a[], uint32_t size) {
    for (int i = size - 1; i >= 0; i--)
        a[i] = i;
}

void generateDataRandom(int a[], uint32_t size) {
    srand(42);
    for (uint32_t i = 0; i < size; i++)
        a[i] = rand();
}
