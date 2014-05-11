#ifndef MULTILEVELQUEUE_HH
#define MULTILEVELQUEUE_HH

#include <queue>
#include <cstdint>
#include "Process.hh"

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
