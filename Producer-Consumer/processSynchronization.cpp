// #include <iostream>
// #include <fstream>
// #include <pthread.h>
// #include <semaphore.h>
// #include <vector>
// #include <chrono>
// #include <thread>

// using namespace std;

// const int bufferSize = 5;

// vector<int> buffer;

// sem_t emptySem;
// sem_t full;
// sem_t theMutex;

// void *producer(void *arguments)
// {
//     int theItem = 0;

//     while (true)
//     {
//         theItem++;

//         sem_wait(&emptySem);
//         sem_wait(&theMutex);

//         buffer.push_back(theItem);
//         cout << "Item: " << theItem << " is produced." << endl;

//         sem_post(&theMutex);
//         sem_post(&full);
//     }
// }

// void *consumer(void *arguments)
// {
//     while (true)
//     {
//         sem_wait(&full);
//         sem_wait(&theMutex);

//         int item = buffer.back();
//         buffer.pop_back();
//         cout << "Item: " << item << " is consumed." << endl;

//         sem_post(&theMutex);
//         sem_post(&emptySem);
//     }
// }

// int main()
// {
//     for (int fileIndex = 1; fileIndex <= 3; fileIndex++)
//     {
//         // Form the input file name
//         string inputFileName = "SleepTime" + to_string(fileIndex) + ".txt";

//         ifstream inputFile(inputFileName);
//         if (!inputFile)
//         {
//             cerr << "Error opening input file: " << inputFileName << "\n";
//             return 1;
//         }

//         // Form the output file name
//         string outputFileName = "processSynchronization_output" + to_string(fileIndex) + ".txt";

//         // Open an output file for results
//         ofstream outputFile(outputFileName);
//         if (!outputFile)
//         {
//             cerr << "Error opening output file: " << outputFileName << "\n";
//             return 1;
//         }

//         // int testCases, numProducers, numConsumers, sleepTime;
//         int sleepTime, numProducers, numConsumers;

//         // Create semaphores
//         sem_init(&emptySem, 0, bufferSize);
//         sem_init(&full, 0, 0);
//         sem_init(&theMutex, 0, 1);

//         // Record start time
//         auto startTime = chrono::high_resolution_clock::now();

//         string header;
//         getline(inputFile, header);

//         while (inputFile >> sleepTime >> numProducers >> numConsumers)
//         {

//             cout << "Sleep Time: " << sleepTime << " milliseconds\n";
//             cout << "Producers: " << numProducers << "\n";
//             cout << "Consumers: " << numConsumers << "\n";

//             // Create threads for producers and consumers
//             pthread_t producerThreads[numProducers];
//             pthread_t consumerThreads[numConsumers];

//             for (int i = 0; i < numProducers; i++)
//             {
//                 pthread_create(&producerThreads[i], NULL, producer, NULL);
//             }

//             for (int i = 0; i < numConsumers; i++)
//             {
//                 pthread_create(&consumerThreads[i], NULL, consumer, NULL);
//             }

//             this_thread::sleep_for(chrono::milliseconds(sleepTime));

//             // Join the threads together
//             for (int i = 0; i < numProducers; i++)
//             {
//                 pthread_cancel(producerThreads[i]);
//             }

//             for (int i = 0; i < numConsumers; i++)
//             {
//                 pthread_cancel(consumerThreads[i]);
//             }
//         }

//         // Record end time
//         auto end_time = chrono::high_resolution_clock::now();

//         // Destroy the semaphores
//         sem_destroy(&emptySem);
//         sem_destroy(&full);
//         sem_destroy(&theMutex);

//         // Turnaround time
//         auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - startTime);

//         // Print the turnaround time to the console and write to the output file
//         cout << "Overall Turnaround Time: " << duration.count() << " ms\n";
//         outputFile << "Overall Turnaround Time: " << duration.count() << " ms\n";

//         // Close files
//         inputFile.close();
//         outputFile.close();

//         return 0;
//     }
// }
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

const int bufferSize = 5;

vector<int> buffer;

sem_t emptySem;
sem_t full;
sem_t theMutex;

void *producer(void *arguments)
{
    int theItem = 0;

    while (true)
    {
        theItem++;

        sem_wait(&emptySem);
        sem_wait(&theMutex);

        buffer.push_back(theItem);
        cout << "Producer " << *((int *)arguments) << ": Item " << theItem << " is produced." << endl;

        sem_post(&theMutex);
        sem_post(&full);
    }
}

void *consumer(void *arguments)
{
    while (true)
    {
        sem_wait(&full);
        sem_wait(&theMutex);

        int item = buffer.back();
        buffer.pop_back();
        cout << "Consumer " << *((int *)arguments) << ": Item " << item << " is consumed." << endl;

        sem_post(&theMutex);
        sem_post(&emptySem);
    }
}

int main()
{
    for (int fileIndex = 1; fileIndex <= 3; fileIndex++)
    {
        // Form the input file name
        string inputFileName = "SleepTime" + to_string(fileIndex) + ".txt";

        ifstream inputFile(inputFileName);
        if (!inputFile)
        {
            cerr << "Error opening input file: " << inputFileName << "\n";
            return 1;
        }

        // Form the output file name
        string outputFileName = "processSynchronization_output" + to_string(fileIndex) + ".txt";

        // Open an output file for results
        ofstream outputFile(outputFileName);
        if (!outputFile)
        {
            cerr << "Error opening output file: " << outputFileName << "\n";
            return 1;
        }

        int sleepTime, numProducers, numConsumers;

        // Create semaphores
        sem_init(&emptySem, 0, bufferSize);
        sem_init(&full, 0, 0);
        sem_init(&theMutex, 0, 1);

        // Record start time
        auto startTime = chrono::high_resolution_clock::now();

        // Read the input parameters from the file
        while (inputFile >> sleepTime >> numProducers >> numConsumers)
        {
            cout << "Sleep Time: " << sleepTime << " milliseconds\n";
            cout << "Producers: " << numProducers << "\n";
            cout << "Consumers: " << numConsumers << "\n";

            // Create threads for producers and consumers
            pthread_t producerThreads[numProducers];
            pthread_t consumerThreads[numConsumers];

            // Create arguments for producer and consumer threads
            int producerArgs[numProducers];
            int consumerArgs[numConsumers];

            // Create and start producer threads
            for (int i = 0; i < numProducers; i++)
            {
                producerArgs[i] = i + 1; // Producer number
                pthread_create(&producerThreads[i], NULL, producer, (void *)&producerArgs[i]);
            }

            // Create and start consumer threads
            for (int i = 0; i < numConsumers; i++)
            {
                consumerArgs[i] = i + 1; // Consumer number
                pthread_create(&consumerThreads[i], NULL, consumer, (void *)&consumerArgs[i]);
            }

            // Allow threads to run for a certain sleep time
            this_thread::sleep_for(chrono::milliseconds(sleepTime));

            // Join the threads together
            for (int i = 0; i < numProducers; i++)
            {
                pthread_cancel(producerThreads[i]);
            }

            for (int i = 0; i < numConsumers; i++)
            {
                pthread_cancel(consumerThreads[i]);
            }
        }

        // Record end time
        auto end_time = chrono::high_resolution_clock::now();

        // Destroy the semaphores
        sem_destroy(&emptySem);
        sem_destroy(&full);
        sem_destroy(&theMutex);

        // Turnaround time
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - startTime);

        // Print the turnaround time to the console and write to the output file
        cout << "Overall Turnaround Time for " << inputFileName << ": " << duration.count() << " ms\n";
        outputFile << "Overall Turnaround Time: " << duration.count() << " ms\n";

        // Close files
        inputFile.close();
        outputFile.close();
    }

    return 0;
}
