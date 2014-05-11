///@file Process.hh
///@author Caleb Reister <calebreister@gmail.com>
#ifndef PROCESS_HH
#define PROCESS_HH

#include <ostream>
#include <istream>
#include <cstdint>
#include "PriorityQueue.hh"

/**@brief Defines the data necessary for a simple process
   @var done Whether or not the process is completed
   @var _pid The process identifier
   @var _initialPriority The starting priority of the process
   @var _timeRequired The time required in order for the process to be completed
   @var _startTime The time to start according to the main clock
   @var priority The current priority
   @var timeRun The time the process has been run

As a general rule, do not change the variables prefixed with an underscore
after instantiation.
 */
struct Process {
    uint32_t _pid;
    uint32_t _initialPriority;
    uint32_t _timeRequired;
    uint32_t _startTime;
    uint32_t priority;
    uint32_t timeLeft;
};

#endif // PROCESS_HH
