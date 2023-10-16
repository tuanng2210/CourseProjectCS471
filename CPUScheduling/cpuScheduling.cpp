#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int priority;
    int cpuBurst;
};

enum SchedulingType {
    FIFO,
    SJF,
    Priority
};


int main() {
    ifstream inputFile("Datafile1-txt.txt");

    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    vector<Process> processes;
    Process process;
    while (inputFile >> process.id >> process.arrivalTime >> process.priority >> process.cpuBurst) {
        processes.push_back(process);
    }
    
   
    return 0;
}
