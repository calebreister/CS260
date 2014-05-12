///@file Simulation.cc
///@author Caleb Reister <calebreister@gmail.com>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PriorityQueue.hh"
#include "Process.hh"
using namespace std;

void buildFutureQueue(ifstream& source, queue<Process>& dest);
void printProcessHeading(ostream& stream);
void printProcessData(ostream& stream, const Process& data, const uint32_t& clock);
void runSimulation(queue<Process>& future, PriorityQueue& running,
                   const uint32_t& SLICE, const uint32_t& PULL_FREQ = 1);

/**@mainpage CPU Scheduler Simulation
This project is a demonstration of the capabilities of queues and is a simple
implementation of a Multilevel Feedback Queue. This program is designed to take
any number of data files as input and it simulates a multilevel feedback queue.
The console output can be copied into a CSV file and opened in a spreadsheet.

Command Line Arguments:\n
This program takes a file or a list of files as input, if no input file is
provided, it will exit with an error. The files list should be space delimited,
and any spaces in the path must be escaped.

Links:

- The input file format is described in buildFutureQueue()
- The simulation logic is documented in runSimulation()
- Process data is stored in the Process struct
- The running processes are stored in a PriorityQueue

Terminology:

- The **clock** refers to the system timer
    - It always counts up, and any time that passes is added to it
    - It measures everything in *ticks*, an imaginary time unit that is
      defined relative to itself. Because this is a simulation, it does not
      increment at a constant rate.
- A **time slice** or **slice** is a cycle of the CPU, it defines how long the CPU
  works on a single process
  - A slice defines the most that the clock can possibly increment per CPU cycle
  - It defines how often the CPU switches jobs
- A **process** is a task for the CPU that spans multiple time slices
  - Running processes are stored in a priority queue, called *running*
  - Processes that the CPU does not know about yet, the part that makes
    this program a simulation, are stored in a queue called *future*
- A **job** refers to the current process being run by the CPU
  - Always points to a process
  - A job runs for a single slice or less, depending on the time the process
    the job refers to has left
  - Once a job is completed, one of two things will happen
    1. It is re-added to the priority queue with a lower priority
    2. If the time left is 0, its data is printed to the console and the
       process is discarded
- The **pull frequency** refers to the number of slices that pass before a new
  process is automatically pulled from the future processes queue
  - If the CPU runs out of running processes, this will be triggered
    automatically, and a new process will be pulled from the future
    queue early
  - If both the future and running process queues are empty, the program exits
 */

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
        buildFutureQueue(simFile, futureProcesses);
        simFile.close();
        runningProcesses = new PriorityQueue(PRIORITIES);

        runSimulation(futureProcesses, *runningProcesses, TIME_SLICE, FUTURE_PULL);

        //clean up
        delete runningProcesses;
        cout << "------------------------------------\n\n";
    }
}

/**@brief Builds a future processes queue from an input file

   @param source The input file stream to use
   @param dest The destination queue in which to put the processes

This function expects a file formatted like the following:

    <PRIORITIES>
    <TIME_SLICE>
    <FUTURE_PULL>

    <priority> <time_needed>
    <priority> <time_needed>
    ...

* Anything in brackets should be replaced by an unsigned integer.
* The type and layout of whitespace used does not matter.
* PRIORITIES, TIME_SLICE, and FUTURE_PULL are not input in this function, they
  must be dealt with beforehand
* PRIORITIES: the number of priorities to use in the simulation
* TIME_SLICE: the time quantum (amount of time per cycle) any process can run
* FUTURE_PULL: the number of slices between automatic future process pulls
* priority: the starting priority of the process
* time_needed: the time the process will take to complete
* Create at many processes as necessary
* This is a simulation, it runs as fast as possible, the unit of
  time used is completely irrelevant.

Working example:

    10
    15
    2

    0 5000
    5 50
    7 100
    1 100
    3 124
    9 330

After each piece of data is input:
- *priority* is set to *initialPriority*
- *timeLeft* is set to *timeRequired*
 */
void buildFutureQueue(ifstream& source, queue<Process>& dest) {
    Process current;
    //using the inFile.eof() method results in the last line being read
    //twice, it is only triggered after the end it actually reached
    while (source >> current._initialPriority >> current._timeRequired)
    {
        current.priority = current._initialPriority;
        current.timeLeft = current._timeRequired;

        dest.push(current);
    }
}

/**@brief Prints a heading for the completed processes table
   @param stream The output stream to use

Sample output (whitespace is different):
 PID, PRIORITY_INIT, PRIORITY_FINAL, TIME_REQUIRED, START_TIME, END_TIME
 */
void printProcessHeading(ostream& stream) {
    cout << setw(5) << "PID,"
         << setw(20) << "PRIORITY_INIT,"
         << setw(20) << "PRIORITY_FINAL,"
         << setw(15) << "TIME_REQUIRED,"
         << setw(15) << "START_TIME,"
         << setw(15) << "END_TIME" << endl;
}

/**@brief Prints the data members of a completed process, fits the output of
          "::"printProcessHeading
   @param stream The output stream to use
   @param data The process to output
   @param clock The current time (in ticks), meant to be the time the process
          ended
 */
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

/**@brief Runs the CPU scheduling simulation
   @param future The future processes queue
   @param running The queue of currently running processes organized by priority
   @param SLICE The number of ticks a single time slice takes
   @param PULL_FREQ The number of slices that run before a new process is pulled
          from the future processes queue automatically

The scheduler operates as follows...

    initialize the clock to 0
    get the first process and add it to the priority queue
    do
        if x number of time slices have passed
            get the next process from the future queue
        else
            increment time slices passed

        if the CPU is idle
            force a new job to be pulled
        else
            if the current job has < a time slice left
                increment the clock the amount of ticks the process took to complete
                set the current job's time left to 0
            else
                add a full slice to the clock
                subtract a slice from the process' time left

            if the job is done (time left == 0)
                print the process data out
                discard the process
            else
                decrement the priority of the process
                re-add the process to the running queue
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
