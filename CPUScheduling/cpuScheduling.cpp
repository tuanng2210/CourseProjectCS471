#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int processId;
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

    string header;
    getline(inputFile, header);


    queue<Process> processes;
    Process process;
    int id = 1; 
    while (inputFile >> process.arrivalTime >> process.cpuBurst >> process.priority ) {
        process.processId = id;
        processes.push(process);
        id++;
    }

    inputFile.close(); 

    while (!processes.empty()) {
        Process frontProcess = processes.front();
        processes.pop();

        cout << "Process ID: " << frontProcess.processId
             << ", Arrival Time: " << frontProcess.arrivalTime
             << ", CPU Burst: " << frontProcess.cpuBurst
             << ", Priority: " << frontProcess.priority << endl;
    }
   
    return 0;
}
