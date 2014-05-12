///@file PriorityQueue.hh
///@author Caleb Reister <calebreister@gmail.com>

#ifndef MULTILEVELQUEUE_HH
#define MULTILEVELQUEUE_HH

#include <queue>
#include <cstdint>
#include "Process.hh"

///@brief Defines a priority queue that stores processes and can return
///       the highest priority process
///The queues are stored in an array where 0 is treated as the lowest priority
class PriorityQueue {
private:
    uint32_t LEVELS;  //should not be changed after initialization
    std::queue<Process>* schedule;
public:
    PriorityQueue();
    PriorityQueue(uint32_t priorities);
    ~PriorityQueue();
    void push(Process add);
    void push(std::queue<Process>& source, const uint32_t& clock);
    Process* getNext();
    bool empty();
    uint32_t getPriorities();
};

#endif // MULTILEVELQUEUE_HH
