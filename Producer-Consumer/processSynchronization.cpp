#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

const int bufferSize = 5;

vector<int> buffer;

sem_t emptySem;
sem_t full;
sem_t theMutex;

void *producer(void *arguments)
{
    //produce a new item
    int theItem = 0;

    
    while (true)
    {
        theItem++;

        //wait for an empty slot to appear in the buffer
        sem_wait(&emptySem);

        //wait for mutex to appear
        sem_wait(&theMutex);

        //add the item to the buffer
        buffer.push_back(theItem);
        cout << "Producer " << *((int *)arguments) << ": Item " << theItem << " is produced." << endl;

        //let go of mutex
        sem_post(&theMutex);

        //change the status of the buffer from emptySem to full
        sem_post(&full);

    }
}

void *consumer(void *arguments)
{
    while (true)
    {
        //wait for an full slot to appear in the buffer
        sem_wait(&full);
        //wait for mutex to appear
        sem_wait(&theMutex);

        //remove the item from the buffer
        int item = buffer.back();
        buffer.pop_back();
        cout << "Consumer " << *((int *)arguments) << ": Item " << item << " is consumed." << endl;

        //let go of mutex
        sem_post(&theMutex);
        //change the status of the buffer from full to emptySem
        sem_post(&emptySem);
    }
}

int main()
{
    for (int fileIndex = 1; fileIndex <= 3; fileIndex++)
    {
        //form the input file name
        string inputFileName = "SleepTime" + to_string(fileIndex) + ".txt";

        ifstream inputFile(inputFileName);
        if (!inputFile)
        {
            cerr << "Error opening input file: " << inputFileName << "\n";
            return 1;
        }

        //form the output file name
        string outputFileName = "processSynchronization_output" + to_string(fileIndex) + ".txt";

        //open an output file for results
        ofstream outputFile(outputFileName);
        if (!outputFile)
        {
            cerr << "Error opening output file: " << outputFileName << "\n";
            return 1;
        }

        int sleepTime, numProducers, numConsumers;

        //create semaphores
        sem_init(&emptySem, 0, bufferSize);
        sem_init(&full, 0, 0);
        sem_init(&theMutex, 0, 1);

        string header;
        getline(inputFile, header);

        //read the input parameters from the file
        outputFile << " SleepTime Producers Consumers Turnaround" << endl;
        while (inputFile >> sleepTime >> numProducers >> numConsumers)
        {

            //create threads for producers and consumers
            pthread_t producerThreads[numProducers];
            pthread_t consumerThreads[numConsumers];

            //create arguments for producer and consumer threads
            int producerArgs[numProducers];
            int consumerArgs[numConsumers];

            //record start time
            auto startTime = chrono::high_resolution_clock::now();

            //create and start producer threads
            for (int i = 0; i < numProducers; i++)
            {
                producerArgs[i] = i + 1; // Producer number
                pthread_create(&producerThreads[i], NULL, producer, (void *)&producerArgs[i]);
            }

            //create and start consumer threads
            for (int i = 0; i < numConsumers; i++)
            {
                consumerArgs[i] = i + 1; // Consumer number
                pthread_create(&consumerThreads[i], NULL, consumer, (void *)&consumerArgs[i]);
            }

            //allow threads to run for a certain sleep time
            this_thread::sleep_for(chrono::milliseconds(sleepTime));

            //join the threads together
            for (int i = 0; i < numProducers; i++)
            {
                pthread_cancel(producerThreads[i]);
            }

            for (int i = 0; i < numConsumers; i++)
            {
                pthread_cancel(consumerThreads[i]);
            }

            //record end time
            auto end_time = chrono::high_resolution_clock::now();

            //turnaround time
            auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - startTime);

            //print the turnaround time to the console and write to the output file
            outputFile << setw(6) << sleepTime << setw(10) << numProducers << setw(10) << numConsumers << setw(11) << duration.count() << endl;
        }

        //destroy the semaphores
        sem_destroy(&emptySem);
        sem_destroy(&full);
        sem_destroy(&theMutex);

        //close files
        inputFile.close();
        outputFile.close();
    }

    return 0;
}
