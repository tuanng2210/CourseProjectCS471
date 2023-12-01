This C++ program simulates the producer-consumer problem using threads. The program reads the number of producers and consumers along with different sleep times in from an input file, creates the producers and consumers using threads with the speed being determined by the sleep time.

Program Structure
The program consists of the following components:

Functions for producer and consumer.

*producer(void *arguments): Implements logic for the producer
*consumer(void *arguments): Implements logic for the consumer 

Main Function:
Reads information from an input file ("SleepTime1.txt" or "SleepTime2.txt" or "SleepTime3.txt").
Creates Threads for producers and consumers after reading in the chosen file and runs process until it ends.
Output:

Once ending, the information is entered into an output file specified for the sleep time chosen being ("processSynchronization_output1.txt" or "processSynchronization_output2.txt" or "processSynchronization_output3.txt").
 
 Steps to run the Producer-Consumer project: 
 1. Open Terminnal
 2. cd Producer-Consumer
 3. Run g++ -std=c++2a -o process processSync.cpp -lpthread
 4. Run ./processSynchronization