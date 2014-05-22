///@file
///@author Caleb Reister <calebreister@gmail.com>

/**@mainpage
The goal of this program is to test merge sort, heap sort, and quick sort with
automatically-generated data. The time that each algorithm takes is output to a
file.

Arguments:
* This program is designed to take a single command line argument in the form
  of a file path, it outputs CSV data. If no argument is provided, it will
  output to a file in the working directory called output.csv
* **The output file will be overwritten if it has any contents**

Example output (this data can be imported into Microsoft Excel or
LibreOffice and turned into a table/chart). I have added whitespace in order to
make the columns more visible, the actual output file has no whitespace, but is
otherwise identical.

                 , 100,      1000,     10000,    100000,   1000000,  10000000
    QUICK ORDERED, 0.000004, 0.00004,  0.000447, 0.005532, 0.070136, 0.757814
    QUICK REVERSE, 0.000005, 0.00004,  0.000449, 0.005514, 0.066805, 0.759007
    QUICK RANDOM,  0.000011, 0.00004,  0.000452, 0.005474, 0.066582, 0.743742
    MERGE ORDERED, 0.000016, 0.000153, 0.001863, 0.020695, 0.225298, 2.77994
    MERGE REVERSE, 0.000025, 0.000168, 0.002042, 0.023959, 0.25781,  3.09252
    MERGE RANDOM,  0.000023, 0.00015,  0.001851, 0.021467, 0.223056, 2.7143
    HEAP ORDERED,  0.000018, 0.000237, 0.003063, 0.038072, 0.46797,  5.45641
    HEAP REVERSE,  0.000022, 0.000214, 0.002866, 0.036252, 0.444201, 5.21247
    HEAP RANDOM,   0.000025, 0.000236, 0.003231, 0.038466, 0.466028, 5.45737

The top row is the size of the dataset tested. 100 is referring to an array of
100 longs (int64_t), 1000 is an array of size 1000...

Below that, the sort mode and data starting order is listed, each with a time
corresponding to the appropriate array size.

Testable data:
* The smallest dataset that is tested is an array of 100
* The maximum size is defined by the constant maxSize in main.cc
* The size is incremented by multiples of 10, so this program will test 100,
  1000, 10000...

See sort for documentation and base code/psuedocode on the sorting
algorithms used in this program.

Links:

- @ref sort
- timeSort()

*/

//#define CHECK_SORT

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <string>
#include "sort.hh"
#include "timePatch.h"
using namespace std;

const index maxSize = 10000000; ///<The biggest array size to test

enum SortMode {QUICK, MERGE, HEAP};
enum DataOrder {ORDERED, REVERSE, RANDOM};

double timeSort(SortMode mode, DataOrder order, uint32_t size);
string sortModeStr(SortMode mode);

int main(int argc, char* argv[]) {
    ofstream out;
    if (argc == 1)
        out.open("output.csv");
    else
        out.open(argv[1]);

    out << ",";
    for (index i = 100; i <= maxSize; i *= 10)
        out << i << ",";

    for (int i = 0; i < 3; i++)
    {
        SortMode mode = static_cast<SortMode>(i);
        out << endl << sortModeStr(mode) << " ORDERED,";
        for (index size = 100; size <= maxSize; size *= 10)
            out << timeSort(mode, ORDERED, size) << ",";
        out << endl << sortModeStr(mode) << " REVERSE,";
        for (index size = 100; size <= maxSize; size *= 10)
            out << timeSort(mode, REVERSE, size) << ",";
        out << endl << sortModeStr(mode) << " RANDOM,";
        for (index size = 100; size <= maxSize; size *= 10)
            out << timeSort(mode, ORDERED, size) << ",";
        cout << "Finished " << sortModeStr(mode) << " tests." << endl;
    }

    out.close();
}

///////////////////////////////////////////////////////////////////////////////
/**@brief Uses the CPU clock to count how long a sorting algorithm takes to run
          on a set of test data
   @param mode The sorting algorithm to use (QUICK, MERGE, HEAP)
   @param order The test data to use (RANDOM, REVERSE, or ORDERED)
   @param size The max size of the array to generate and test
   @return The time it took (in seconds) to run the algorithm
*/
double timeSort(SortMode mode, DataOrder order, uint32_t size) {
    double startTime;
    double timeTaken;

    long* data = new long[size];

    switch (order) {
    case RANDOM:
        srand(42);
        for (uint32_t i = 0; i < size; i++)
            data[i] = rand();
        break;
    case ORDERED:
        for (uint32_t i = 0; i < size; i++)
            data[i] = i;
        break;
    case REVERSE:
        long val = static_cast<long>(size - 1);
        for (uint32_t i = 0; i < size; i++)
            data[i] = val--;
        break;
    }

    //TIMED ZONE
    startTime = get_cpu_time();
    switch (mode) {
    case QUICK:
        sort::quick(data, size);
        break;
    case MERGE:
        sort::merge(data, size);
        break;
    case HEAP:
        sort::heap(data, size);
        break;
    }
    timeTaken = get_cpu_time() - startTime;
    //END TIMED ZONE

    #ifdef CHECK_SORT
    for (uint32_t i = 1; i < size; i++)
        assert(data[i] >= data[i - 1]);
    cout << "data valid";
    #endif

    delete [] data;
    return timeTaken;
}

/**@brief Outputs a string corresponding to the SortMode enum
   @param The SortMode to output as a string
   @return A string containing the sort mode (in ALL CAPS)
*/
string sortModeStr(SortMode mode) {
    switch (mode) {
    case QUICK:
        return "QUICK";
        break;
    case MERGE:
        return "MERGE";
        break;
    case HEAP:
        return "HEAP";
        break;
    }
    return "";
}

