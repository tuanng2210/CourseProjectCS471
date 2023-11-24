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
sem_t mutex;

void *producer(void *arguments)
{
    int theItem = 0;

    while (true)
    {
        theItem++;

        sem_wait(&emptySem);
        sem_wait(&mutex);

        buffer.push_back(theItem);
        cout << "Item: " << theItem << " is produced." << endl;

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arguments)
{
    while (true)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer.back();
        buffer.pop_back();
        cout << "Item: " << item << " is consumed." << endl;

        sem_post(&mutex);
        sem_post(&emptySem);
    }
}

int main()
{
    ifstream inputFile("Datafile2.txt");
    if (!inputFile)
    {
        cerr << "Error opening input file.\n";
        return 1;
    }

    // Open an output file for results
    ofstream outputFile("processSynchronization.txt");
    if (!outputFile)
    {
        cerr << "Error opening output file.\n";
        return 1;
    }

    int testCases, numProducers, numConsumers, sleepTime;

    // Create semaphores
    sem_init(&emptySem, 0, bufferSize);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Record start time
    auto startTime = chrono::high_resolution_clock::now();

    string header;
    getline(inputFile, header);

    // Read the number of test cases from the file
    inputFile >> testCases;

    for (int testCase = 0; testCase < testCases; testCase++)
    {
        // Read input parameters for each test case
        inputFile >> numProducers >> numConsumers;

        cout << "Test Case: " << testCase + 1 << "\n";
        cout << "Producers: " << numProducers << "\n";
        cout << "Consumers: " << numConsumers << "\n";

        // Create threads for producers and consumers
        pthread_t producerThreads[numProducers];
        pthread_t consumerThreads[numConsumers];

        for (int i = 0; i < numProducers; i++)
        {
            pthread_create(&producerThreads[i], NULL, producer, NULL);
        }

        for (int i = 0; i < numConsumers; i++)
        {
            pthread_create(&consumerThreads[i], NULL, consumer, NULL);
        }

        // Allow threads to run for a certain sleep time
        cout << "Enter sleep time (in milliseconds) for Test Case " << testCase + 1 << ": ";
        cin >> sleepTime;

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
    sem_destroy(&mutex);

    // Turnaround time
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - startTime);

    // Print the turnaround time to the console and write to the output file
    cout << "Overall Turnaround Time: " << duration.count() << " ms\n";
    outputFile << "Overall Turnaround Time: " << duration.count() << " ms\n";

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
