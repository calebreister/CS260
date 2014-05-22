#ifndef TIME_PATCH_H
#define TIME_PATCH_H

//This file is valid C code

/**@file timePatch.h
   @author http://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-
           time-and-wall-clock-time-on-both-linux-windows
*/

#ifdef __cplusplus //only add if being compiled under C++
extern "C" {
#endif

double get_wall_time();
double get_cpu_time();

#ifdef __cplusplus
}
#endif

#endif // TIME_PATCH_H
