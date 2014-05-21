#ifndef TIME_PATCH_H
#define TIME_PATCH_H

/**@file timePatch.h
   @brief This is a C-style header that deals with Microsoft's standard library
          implementation incorrectly handling the <ctime> clock() function. This
          code should work equally well in both C and C++.
*/

#ifdef _WIN32 // Windows
#include <Windows.h>
double get_wall_time() {
    LARGE_INTEGER time, freq;
    if (!QueryPerformanceFrequency(&freq))
        return 0; //handle error
    if (!QueryPerformanceCounter(&time))
        return 0; //handle error
    return (double)time.QuadPart / freq.QuadPart;
}

double get_cpu_time() {
    FILETIME a, b, c, d;
    if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0){
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }
    else
        return 0; //handle error
}

#else // POSIX/Linux
#include <sys/time.h>
double get_wall_time() {
    struct timeval time;
    if (gettimeofday(&time,NULL))
        return 0; //handle error
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
double get_cpu_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}
#endif // _WIN32

#endif // TIME_H
