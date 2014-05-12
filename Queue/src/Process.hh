///@file Process.hh
///@author Caleb Reister <calebreister@gmail.com>
#ifndef PROCESS_HH
#define PROCESS_HH

#include <ostream>
#include <istream>
#include <cstdint>
#include "PriorityQueue.hh"

/**@brief Defines the data necessary for a simple process

As a general rule, do not change the variables prefixed with an underscore
after instantiation.
 */
struct Process {
    uint32_t _pid; ///< The process identifier
    uint32_t _initialPriority; ///< The starting priority of the process
    uint32_t _timeRequired; ///< The time the process will take to run
    uint32_t _startTime; ///< The time the process was started
    uint32_t priority; ///< The current priority
    uint32_t timeLeft; ///< The time the process has left until it is completed
};

#endif // PROCESS_HH
