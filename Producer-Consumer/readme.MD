# CS 471/571 - Problem 2

## Authors

Shawn Bryant and Tuan Nguyen

## Description

This C++ program simulates the producer-consumer problem using threads. The program reads the number of producers and consumers along with different sleep times in from an input file, creates the producers and consumers using threads with the speed being determined by the sleep time.

## Input File

The program can read in one of three files being one for each sleep time. The input files are ("SleepTime1.txt" or "SleepTime2.txt" or "SleepTime3.txt") which contain the sleep times, number of producers, and number of consumers.

## Compiling the program

 Starting from the source code, the program can be compiled by using the following command:
 g++ -std=c++2a -o processSynchronization processSynchronization.cpp -lpthread

 ## Running the program

The program can be run in the terminal using the following commmand:
./processSynchronization

## Output

The output files have the following structure "processSynchronization_output[ Number based on lowest sleep time ].txt"

processSynchronization_output1.txt
processSynchronization_output2.txt
processSynchronization_output3.txt

Each output file will have the following contents:

## Result's summary and explanation

There are several factors that can affect a turnaround time with the most obvious ones being the number of producers and consumers. The more producers there are, the more items are being created causing more work for the computer to do which will directly affect the turnaround time. In the same way, the more consumers there are, the more items are being consumed also affecting the turnaround time. Wait times are also very important because of the producers and consumers don't have enough time to finish the way they are supposed to, the turnaround time will be directly affected. So with that being said, the sleep timing also has a direct effect on the turnaround time.
