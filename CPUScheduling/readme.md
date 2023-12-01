# CS 471/571 - Problem 1

## Authors

Tuan Nguyen and Shawn Bryant

## Description

This C++ program simulates three different CPU scheduling algorithms: First-Come-First-Serve (FIFO), Shortest Job First (SJF), and Priority Scheduling. The program reads process information from an input file, performs scheduling based on the selected algorithm, and outputs the results, including statistics, to corresponding output files.

## Input File

The program reads in the process information from a text file called "Datafile1.txt" which contains 500 processes which all have arrival time, cpu burst length and priority.

## Compiling the program

 Starting from the source code, the program can be compiled by using the following command:
 g++ cpuScheduling.cpp -o cpuSched -std=c++11 

## Running the program

The program can be run in the terminal using the following commmand:
./cpuScheduling

## Output

The output files have the following structure "[ Scheduling Type ].txt"

fifo.txt
priority.txt
sjf.txt

Each output file will have the following contents:

## Result's summary and explanation

The waiting time, turnaround time, and response time for priority and first in first out were pretty similar becuase of the fact that the only two real differences in those algorithms is the fact that priority is involved and preemption. Shortest job first however, had some very clear differences becuase it is being resorted based off of each process's size. Given the fact that the turnaround time, waiting time, and response time are all affected by the order of processes in a group, it comes to no surprise that the difference between sjf and fifo and priority were magnified through those three statistics.

throughput = totalProcesses / current Time
cpu Utilization = total Turnaround Time / current Time
average Waiting Time = total Waiting Time / total Processes
average Turnaround Time = total Turnaround Time / total Processes
average Response Time = total Response Time / total Processes
