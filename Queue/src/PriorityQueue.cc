///@file PriorityQueue.cc
///@author Caleb Reister <calebreister@gmail.com>

#include "PriorityQueue.hh"
using namespace std;

///@brief Initializes a priority queue with 10 priorities
PriorityQueue::PriorityQueue() {
    LEVELS = 10;
    schedule = new std::queue<Process>[LEVELS];
}

///@brief Initializes a priority queue with a user-defined number of priorities
PriorityQueue::PriorityQueue(uint32_t priorities) {
    LEVELS = priorities;
    schedule = new std::queue<Process>[LEVELS];
}

PriorityQueue::~PriorityQueue() {
    delete [] schedule;
}

///@brief Adds a process to the queue within the priority array
void PriorityQueue::push(Process add) {
    schedule[add.priority].push(add);
}

/**@brief Adds a process to the priority queue from an std::queue
   @param source The std::queue where the process popped from
   @param clock The system clock (in ticks) logged as the start time
          of the process

Initialized values:
- The PID is added to the process and increments from the from 0 starting at
  instantiation
- The start time is set to be equal to the clock
 */
void PriorityQueue::push(queue<Process>& source, const uint32_t& clock) {
    Process newProcess;
    static uint32_t nextPID = 0;

    newProcess = source.front();
    source.pop();

    newProcess._pid = nextPID;
    newProcess._startTime = clock;

    nextPID++;
    this->push(newProcess);
}

/**@brief Gets the highest priority process from the queue array,
          pops the process
   @return A pointer to a copy of the process from the front of the highest
           priority in the priority queue, must be deleted by the user
 */
Process* PriorityQueue::getNext() {
    if (this->empty())
        return NULL;
    uint32_t i = LEVELS - 1;
    while (schedule[i].empty() && i != 0)
        i--;

    Process* output = new Process;
    *output = schedule[i].front();
    schedule[i].pop();
    return output;
}

///@return Whether or not the priority queue is empty
bool PriorityQueue::empty() {
    for (uint32_t i = 0; i < LEVELS; i++)
        if (!schedule[i].empty())
            return false;
    return true;
}

///@return The number of priorities in the PriorityQueue
uint32_t PriorityQueue::getPriorities() {
    return LEVELS;
}
