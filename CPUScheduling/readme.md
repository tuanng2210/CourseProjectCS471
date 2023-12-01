This C++ program simulates three different CPU scheduling algorithms: First-Come-First-Serve (FIFO), Shortest Job First (SJF), and Priority Scheduling. The program reads process information from an input file, performs scheduling based on the selected algorithm, and outputs the results, including statistics, to corresponding output files.

Program Structure
The program consists of the following components:

Struct Process: Represents a process with attributes such as process ID, arrival time, CPU burst, priority, remaining burst time (for SJF), start time, and end time.

Functions for Each Scheduling Algorithm:

runFIFO(queue<Process> &processes): Implements FIFO scheduling.
runSJF(queue<Process> &processes): Implements SJF scheduling.
runPriority(queue<Process> &processes): Implements Priority Scheduling.

Main Function:
Reads process information from an input file ("Datafile1.txt").
Prompts the user to choose a scheduling algorithm.
Calls the corresponding scheduling function.
Output:

The program outputs scheduling results and statistics to separate text files (fifo.txt, sjf.txt, priority.txt).
