#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct Process
{
    int processId;
    int arrivalTime;
    int cpuBurst;
    int priority;
    int remainingBurst; // To keep track of remaining burst time for SJF
    int startTime;      // To calculate response time
    int endTime;
};

void runFIFO(queue<Process> &processes)
{
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int processesExecuted = 0;

    while (!processes.empty() && processesExecuted < 500)
    {
        Process currentProcess = processes.front();
        processes.pop();

        // If the process arrives after the current time, update the current time
        if (currentTime < currentProcess.arrivalTime)
        {
            currentTime = currentProcess.arrivalTime;
        }

        // Update start time, end time, waiting time, and turnaround time for the process
        currentProcess.startTime = currentTime;
        currentProcess.endTime = currentProcess.startTime + currentProcess.cpuBurst;
        totalWaitingTime += currentTime - currentProcess.arrivalTime;
        totalTurnaroundTime += currentProcess.endTime - currentProcess.arrivalTime;
        totalResponseTime += currentProcess.startTime - currentProcess.arrivalTime;

        // Update current time to the end time of the current process
        currentTime = currentProcess.endTime;

        // Print information about the executed process
        cout << "Process ID: " << currentProcess.processId
             << ", Arrival Time: " << currentProcess.arrivalTime
             << ", CPU Burst: " << currentProcess.cpuBurst
             << ", Priority: " << currentProcess.priority << endl;

        processesExecuted++;
    }

    // Calculate and print statistics
    int totalProcesses = processesExecuted;
    double throughput = static_cast<double>(totalProcesses) / currentTime;
    double cpuUtilization = static_cast<double>(totalTurnaroundTime) / currentTime;
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / totalProcesses;
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / totalProcesses;
    double avgResponseTime = static_cast<double>(totalResponseTime) / totalProcesses;

    cout << "\nStatistics for the Run" << endl;
    cout << "Number of processes: " << totalProcesses << endl;
    cout << "Total elapsed time: " << currentTime << " CPU burst units" << endl;
    cout << "Throughput: " << throughput << " processes per unit of CPU burst time" << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time: " << avgWaitingTime << " CPU burst units" << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << " CPU burst units" << endl;
    cout << "Average response time: " << avgResponseTime << " CPU burst units" << endl;

    ofstream outfile;
    outfile.open("fifo.txt");

    outfile << "\nStatistics for the Run" << endl;
    outfile << "Number of processes: " << totalProcesses << endl;
    outfile << "Total elapsed time: " << currentTime << " CPU burst units" << endl;
    outfile << "Throughput: " << throughput << " processes per unit of CPU burst time" << endl;
    outfile << "CPU utilization: " << cpuUtilization << endl;
    outfile << "Average waiting time: " << avgWaitingTime << " CPU burst units" << endl;
    outfile << "Average turnaround time: " << avgTurnaroundTime << " CPU burst units" << endl;
    outfile << "Average response time: " << avgResponseTime << " CPU burst units" << endl;

    outfile.close();
    
}

void runSJF(queue<Process> &processes)
{
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int processesExecuted = 0;
    int processesToProcess = 0;
    vector<Process> sortedProcesses;

    while (!processes.empty() && processesToProcess < 500)
    {
        sortedProcesses.push_back(processes.front());
        processes.pop();
        processesToProcess++;
    }

    sort(sortedProcesses.begin(), sortedProcesses.end(), [](const Process &a, const Process &b)
         {
         if (a.cpuBurst == b.cpuBurst)
         {
             return a.arrivalTime < b.arrivalTime; 
         }
         return a.cpuBurst < b.cpuBurst; });

    for (const auto &currentProcess : sortedProcesses)
    {
        // If the process arrives after the current time, update the current time
        if (currentTime < currentProcess.arrivalTime)
        {
            currentTime = currentProcess.arrivalTime;
        }

        // Create a copy of currentProcess to modify its members
        Process executingProcess = currentProcess;

        // Update start time, end time, waiting time, and turnaround time for the process
        executingProcess.startTime = currentTime;
        executingProcess.endTime = executingProcess.startTime + executingProcess.cpuBurst;
        totalWaitingTime += currentTime - executingProcess.arrivalTime;
        totalTurnaroundTime += executingProcess.endTime - executingProcess.arrivalTime;
        totalResponseTime += executingProcess.startTime - executingProcess.arrivalTime;

        // Update current time to the end time of the current process
        currentTime = executingProcess.endTime;

        // Print information about the executed process
        cout << "Process ID: " << executingProcess.processId
             << ", Arrival Time: " << executingProcess.arrivalTime
             << ", CPU Burst: " << executingProcess.cpuBurst
             << ", Priority: " << executingProcess.priority << endl;

        processesExecuted++;
    }

    // Calculate and print statistics
    int totalProcesses = processesExecuted;
    double throughput = static_cast<double>(totalProcesses) / currentTime;
    double cpuUtilization = static_cast<double>(totalTurnaroundTime) / currentTime;
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / totalProcesses;
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / totalProcesses;
    double avgResponseTime = static_cast<double>(totalResponseTime) / totalProcesses;

    cout << "\nStatistics for the Run" << endl;
    cout << "Number of processes: " << totalProcesses << endl;
    cout << "Total elapsed time: " << currentTime << " CPU burst units" << endl;
    cout << "Throughput: " << throughput << " processes per unit of CPU burst time" << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time: " << avgWaitingTime << " CPU burst units" << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << " CPU burst units" << endl;
    cout << "Average response time: " << avgResponseTime << " CPU burst units" << endl;

    ofstream outfile;
    outfile.open("sjf.txt");

    outfile << "\nStatistics for the Run" << endl;
    outfile << "Number of processes: " << totalProcesses << endl;
    outfile << "Total elapsed time: " << currentTime << " CPU burst units" << endl;
    outfile << "Throughput: " << throughput << " processes per unit of CPU burst time" << endl;
    outfile << "CPU utilization: " << cpuUtilization << endl;
    outfile << "Average waiting time: " << avgWaitingTime << " CPU burst units" << endl;
    outfile << "Average turnaround time: " << avgTurnaroundTime << " CPU burst units" << endl;
    outfile << "Average response time: " << avgResponseTime << " CPU burst units" << endl;

    outfile.close();

}

void runPriority(queue<Process> &processes)
{
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int processesExecuted = 0;

    priority_queue<Process, vector<Process>, function<bool(Process, Process)>> priorityQueue(
        [](Process a, Process b)
        { return a.priority > b.priority; });

    while (!processes.empty() && processesExecuted < 500)
    {
        // Check if any new processes have arrived
        while (!processes.empty() && processes.front().arrivalTime <= currentTime)
        {
            priorityQueue.push(processes.front());
            processes.pop();
        }

        // If the priority queue is not empty, select the highest priority process
        if (!priorityQueue.empty())
        {
            Process currentProcess = priorityQueue.top();
            priorityQueue.pop();

            // Update start time, end time, waiting time, and turnaround time for the process
            currentProcess.startTime = currentTime;
            currentProcess.endTime = currentTime + currentProcess.cpuBurst;
            totalWaitingTime += currentTime - currentProcess.arrivalTime;
            totalTurnaroundTime += currentProcess.endTime - currentProcess.arrivalTime;
            totalResponseTime += currentProcess.startTime - currentProcess.arrivalTime;

            // Update current time to the end time of the current process
            currentTime = currentProcess.endTime;

            // Print information about the executed process
            cout << "Process ID: " << currentProcess.processId
                 << ", Arrival Time: " << currentProcess.arrivalTime
                 << ", CPU Burst: " << currentProcess.cpuBurst
                 << ", Priority: " << currentProcess.priority << endl;

            processesExecuted++;
        }
        else
        {
            // No processes in the priority queue; increment time
            currentTime++;
        }
    }

    // Calculate and print statistics
    int totalProcesses = processesExecuted;
    double throughput = static_cast<double>(totalProcesses) / currentTime;
    double cpuUtilization = static_cast<double>(totalTurnaroundTime) / currentTime;
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / totalProcesses;
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / totalProcesses;
    double avgResponseTime = static_cast<double>(totalResponseTime) / totalProcesses;

    cout << "\nStatistics for the Run" << endl;
    cout << "Number of processes: " << totalProcesses << endl;
    cout << "Total elapsed time: " << currentTime << " CPU burst units" << endl;
    cout << "Throughput: " << throughput << " processes per unit of CPU burst time" << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time: " << avgWaitingTime << " CPU burst units" << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << " CPU burst units" << endl;
    cout << "Average response time: " << avgResponseTime << " CPU burst units" << endl;

    ofstream outfile;
    outfile.open("priority.txt");

    outfile << "\nStatistics for the Run" << endl;
    outfile << "Number of processes: " << totalProcesses << endl;
    outfile << "Total elapsed time: " << currentTime << " CPU burst units" << endl;
    outfile << "Throughput: " << throughput << " processes per unit of CPU burst time" << endl;
    outfile << "CPU utilization: " << cpuUtilization << endl;
    outfile << "Average waiting time: " << avgWaitingTime << " CPU burst units" << endl;
    outfile << "Average turnaround time: " << avgTurnaroundTime << " CPU burst units" << endl;
    outfile << "Average response time: " << avgResponseTime << " CPU burst units" << endl;

    outfile.close();

}

int main()
{
    queue<Process> processes;
    ifstream inputFile("Datafile1.txt");

    if (!inputFile)
    {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    else if (inputFile)
    {
        string header;
        getline(inputFile, header);

        Process process;
        int id = 1;
        while (inputFile >> process.arrivalTime >> process.cpuBurst >> process.priority)
        {
            process.processId = id;
            processes.push(process);
            id++;
        }
    }

    inputFile.close();

    int schedulingType;
    cout << "Enter scheduling type (1 for FIFO, 2 for SJF, 3 for Priority): ";
    cin >> schedulingType;

    switch (schedulingType)
    {
    case 1:
        runFIFO(processes);
        break;
    case 2:
        runSJF(processes);
        break;
    case 3:
        runPriority(processes);
        break;
    default:
        cout << "Invalid scheduling type." << endl;
        return 1;
    }

    return 0;
}
