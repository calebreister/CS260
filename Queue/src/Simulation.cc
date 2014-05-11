/**@file Simulation.cc
   @author Caleb Reister <calebreister@gmail.com>
 */
/**@mainpage CPU Scheduler Simulation
This project is a demonstration of the capabilities of queues and is a simple
implementation of a priority queue. This program is designed to take any number
of data files as input and it simulates a multilevel feedback queue. The console
output can be copied into a CSV file and opened in a spreadsheet.

- The input file is described in "::"buildJobQueue
- The simulation is documented in "::"runSimulation
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PriorityQueue.hh"
#include "Process.hh"
using namespace std;

void buildJobQueue(ifstream& inFile, queue<Process>& jobs);
void printProcessHeading(ostream& stream);
void printProcessData(ostream& stream, const Process& data, const uint32_t& clock);
void runSimulation(queue<Process>& future, PriorityQueue& running,
                   const uint32_t& SLICE, const uint32_t& PULL_FREQ);

int main(int argc, char* argv[]) {
    if (argc <= 1)
    {
        cout << "No input file specified.\n";
        return 1;
    }

    PriorityQueue* runningProcesses;
    //sim is the simulation index, this program supports
    //multiple input files
    for (uint32_t sim = 1; sim < argc; sim++)
    {
        queue<Process> futureProcesses;
        //cout << argv[sim] << endl;
        printProcessHeading(cout);

        //initialize the queues
        uint32_t PRIORITIES, TIME_SLICE, FUTURE_PULL;
        ifstream simFile;
        simFile.open("test.txt");//argv[sim]);
        simFile >> PRIORITIES >> TIME_SLICE >> FUTURE_PULL;
        buildJobQueue(simFile, futureProcesses);
        simFile.close();
        runningProcesses = new PriorityQueue(PRIORITIES);

        runSimulation(futureProcesses, *runningProcesses, TIME_SLICE, FUTURE_PULL);

        //clean up
        delete runningProcesses;
        cout << "------------------------------------\n\n";
    }
}

//TODO: fix this comment, it is outdated
/** @brief Builds a PriorityQueue from an input file
    @param file The name of the input file to use
    @param slice The length of a time slice
    @return A pointer to a PriorityQueue, must be deleted manually

This function expects a file formatted like the following:

    <PRIORITIES>
    <TIME_SLICE>

    <priority> <time_needed>
    <priority> <time_needed>
    ...

* Anything in brackets should be replaced by an unsigned integer.
* The type and layout of whitespace used does not matter.
* PRIORITIES: the number of priorities to use in the simulation
* TIME_SLICE: the time quantum (amount of time per cycle) any process can run
* priority: the starting priority of the process
* time_needed: the time the process will take to complete
* Create at many processes as necessary
* This is a simulation, it runs as fast as possible, the unit of
  time is completely irrelevant.

Working example:

    10
    15

    5 50
    7 100
    1 100
 */
void buildJobQueue(ifstream& inFile, queue<Process>& jobs) {
    Process current;
    //using the inFile.eof() method results in the last line being read
    //twice, it is only triggered after the end it actually reached
    while (inFile >> current._initialPriority >> current._timeRequired)
    {
        current.priority = current._initialPriority;
        current.timeLeft = current._timeRequired;

        jobs.push(current);
    }
}

void printProcessHeading(ostream& stream) {
    cout << setw(5) << "PID,"
         << setw(20) << "PRIORITY_INIT,"
         << setw(20) << "PRIORITY_FINAL,"
         << setw(15) << "TIME_REQUIRED,"
         << setw(15) << "START_TIME,"
         << setw(15) << "END_TIME" << endl;
}

void printProcessData(ostream& stream, const Process& data,
                      const uint32_t& clock) {
    //PID, INITIAL_PRIORITY, FINAL_PRIORITY, TIME_REQUIRED,
    //TIME_SUBMITTED, TIME_COMPLETED"
    stream << setw(4) << data._pid << ","
           << setw(19) << data._initialPriority << ","
           << setw(19) << data.priority << ","
           << setw(14) << data._timeRequired << ","
           << setw(14) << data._startTime << ","
           << setw(15) << clock << endl;
}

/**
The scheduler operates as follows...

    initialize the clock to 0
    get the first process and add it to the priority queue
    do
        if x number of time slices have passed:
            get the next item from the future queue
        else
            increment time slices passed

        if the CPU is idle
            force a new job to be pulled
        else
            if the current job has < a time slice left
                increment the clock the amount of ticks the process took to complete
            else
                add a full slice to the clock
                subtract a slice from the process' time left

            if the job is done
                print it out and discard it
            else
                decrement the priority

        get the next job from the priority queue
    while the priority queue or future job queue is not empty
 */
void runSimulation(queue<Process>& future, PriorityQueue& running,
                   const uint32_t& SLICE, const uint32_t& PULL_FREQ) {
    //naming rule: a job refers to what the CPU is running for a single SLICE
    //a process spans multiple slices

    Process* currentJob = NULL; //the process currently being run
    uint32_t clock = 0; //the system clock, always counts up

    running.push(future, clock); // get and run the first process
    currentJob = running.getNext();

    do
    {
        //counts the number of times the loop has gone through and
        //adds a new process if necessary
        static uint32_t sliceCount = 0;

        //get a new process from the future queue
        if (sliceCount == PULL_FREQ && !future.empty())
        {
            running.push(future, clock);
            sliceCount = 0;
        }
        else
            sliceCount++;

        //manage the priority queue
        if (currentJob == NULL) //CPU is idle
        {
            clock += PULL_FREQ * SLICE - sliceCount * SLICE; //push clock forward
            sliceCount = PULL_FREQ;
        }
        else
        {
            //run process
            if (currentJob->timeLeft < SLICE)
            {
                clock += currentJob->timeLeft;
                currentJob->timeLeft = 0;
            }
            else
            {
                currentJob->timeLeft -= SLICE;
                clock += SLICE;
            }

            //re-add process to priority queue or consider it complete
            if (currentJob->timeLeft == 0)
                printProcessData(cout, *currentJob, clock);
            else
            {
                if (currentJob->priority > 0)
                    currentJob->priority--;
                running.push(*currentJob);
            }
            delete currentJob;
        }

        currentJob = running.getNext();
    } while (currentJob != NULL || !future.empty());
}
