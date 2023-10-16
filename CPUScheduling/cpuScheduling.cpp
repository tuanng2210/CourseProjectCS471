#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int arrivalTime;
    int cpuBurst;
    int priority;
};

enum SchedulingType {
    FIFO,
    SJF,
    Priority
};


int main() {

    system("pwd");
    ifstream inputFile("Datafile1.txt");

    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    queue<Process> processes;
    Process process;
    int numberOfProcesses = 0; 
    while (inputFile >> process.arrivalTime >> process.cpuBurst >> process.priority ) {
        processes.push(process);
        numberOfProcesses++;
    }

    inputFile.close(); 

    while (!processes.empty()) {
        Process frontProcess = processes.front();
        processes.pop();

        cout << "Arrival Time: " << frontProcess.arrivalTime
             << ", CPU Burst: " << frontProcess.cpuBurst
             << ", Priority: " << frontProcess.priority << endl;
    }

    cout << "Number Processes: " << numberOfProcesses << endl;
   
    return 0;
}
