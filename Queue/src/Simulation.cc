/**@file
 * @author Caleb Reister <calebreister@gmail.com>
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

/*NEW LAYOUT:
- Everything from file comes into a future jobs queue
- Every slice, a new process is pulled from the future queue
  and placed into the feedback queue
---------------------------------------------------------------
struct process:
    pid
    initial priority
    time required
    current priority
    time started
    time finished (optional)
    time remaining
----------------------------------------------------------------
SimTime=0
NextJobArrivesTime=0
CpuAvailableTime=0
while (!futureProcesQ.empty() or !PriorityQ.empty() or CPU ! busy)
	//new job shows up to be run
	If (SimTime == NextJobArrivesTime)
		Take Job Off FutureProcessQue
		Initialize it (PID, start time, etc..)
		Put it in the Priorty Q
		NextJobArrivesTime+=15;
	if (SimTime == CpuAvailableTime)
		If it's currently running a job
			Adjust it's properties (time ran, priority, etc..)
			If it's done
				print out process data and delete it
			else
				Insert that job back into PriorityQ (priority less)
		If PriorityQ is not empty
			DeQueue next job to run, assign to cpu
			if (timeremaining<TIMESLICE
				cpuAvailableTime+=timeRemaining
			else
				cpuAvailable+=TIMESLICE
		else
			cpuAvailableTime = NextJobArriveTime
	Increment SimTime to either NextJobArrivesTime or CpuAvailableTime (whichever is lower)
*/

int main(int argc, char* argv[]) {
    /*if (argc <= 1)
    {
        cout << "No input file specified.\n";
        return 1;
    }*/

    PriorityQueue* runningProcesses;
    //sim is the simulation index, this program supports
    //multiple input files
    /*for (uint32_t sim = 1; sim < argc; sim++)
    {*/
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
    //}
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
    uint32_t pid = 0;
    while (!inFile.eof())
    {
        Process current;
        inFile >> current._initialPriority >> current._timeRequired;
        current.priority = current._initialPriority;
        current.timeLeft = current._timeRequired;

        jobs.push(current);
        pid++;
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
    stream << setw(5) << data._pid << ","
           << setw(20) << data._initialPriority << ","
           << setw(20) << data.priority << ","
           << setw(15) << data._timeRequired << ","
           << setw(15) << data._startTime << ","
           << setw(20) << clock;
}

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