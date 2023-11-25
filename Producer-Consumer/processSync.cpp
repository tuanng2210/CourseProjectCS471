#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <queue>
#include <chrono>
#include <ctime>
#include <unistd.h>

using namespace std;

const int bufferSize = 5;

vector<int> buffer;
queue<int> dataQueue;
volatile bool terminateThreads = false;
pthread_mutex_t printMutex;
ofstream outFile;  // Declare a single file stream

pthread_mutex_t TheMutex;
pthread_cond_t notFull, notEmpty;

void *producer(void *arguments)
{
    int theItem = 0;

    while (!terminateThreads)
    {
        theItem++;

        pthread_mutex_lock(&TheMutex);
        while (dataQueue.size() == bufferSize)
        {
            pthread_cond_wait(&notFull, &TheMutex);
        }

        dataQueue.push(theItem);

        // Use mutex for synchronized printing
        pthread_mutex_lock(&printMutex);
        outFile << "Item: " << theItem << " is produced." << endl;
        pthread_mutex_unlock(&printMutex);

        pthread_mutex_unlock(&TheMutex);
        pthread_cond_signal(&notEmpty);
    }

    pthread_exit(NULL);
}

void *consumer(void *arguments)
{
    while (!terminateThreads)
    {
        pthread_mutex_lock(&TheMutex);
        while (dataQueue.empty())
        {
            pthread_cond_wait(&notEmpty, &TheMutex);
        }

        int item = dataQueue.front();
        dataQueue.pop();

        // Use mutex for synchronized printing
        pthread_mutex_lock(&printMutex);
        outFile << "Item: " << item << " is consumed." << endl;
        pthread_mutex_unlock(&printMutex);

        pthread_mutex_unlock(&TheMutex);
        pthread_cond_signal(&notFull);
    }

    pthread_exit(NULL);
}

int main()
{
    // Initialize mutex and condition variables
    pthread_mutex_init(&TheMutex, NULL);
    pthread_cond_init(&notFull, NULL);
    pthread_cond_init(&notEmpty, NULL);
    pthread_mutex_init(&printMutex, NULL);

    // Open the output file in write mode to clear previous content
    outFile.open("output.txt");

    // Test cases
    int testCases[] = {1, 4, 16};
    int numProducers[] = {1, 4, 16};
    int numConsumers[] = {1, 2, 4};

    for (int i = 0; i < 3; i++)
    {
        // Set the termination flag
        terminateThreads = false;

        // Create threads for producers and consumers
        pthread_t producerThreads[numProducers[i]];
        pthread_t consumerThreads[numConsumers[i]];

        // Use mutex for synchronized printing
        pthread_mutex_lock(&printMutex);
        outFile << "Test Case: " << i + 1 << endl;
        outFile << "Number of Producers: " << numProducers[i] << endl;
        outFile << "Number of Consumers: " << numConsumers[i] << endl;
        pthread_mutex_unlock(&printMutex);

        auto startTime = chrono::high_resolution_clock::now();

        for (int j = 0; j < numProducers[i]; j++)
        {
            pthread_create(&producerThreads[j], NULL, producer, NULL);
        }

        for (int j = 0; j < numConsumers[i]; j++)
        {
            pthread_create(&consumerThreads[j], NULL, consumer, NULL);
        }

        // Allow threads to run for a certain sleep time
        usleep(5000000); // Sleep for 5000 milliseconds (5 seconds)

        // Set the termination flag
        terminateThreads = true;

        // Join the threads together
        for (int j = 0; j < numProducers[i]; j++)
        {
            pthread_join(producerThreads[j], NULL);
        }

        for (int j = 0; j < numConsumers[i]; j++)
        {
            pthread_join(consumerThreads[j], NULL);
        }

        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

        // Use mutex for synchronized printing
        pthread_mutex_lock(&printMutex);
        pthread_mutex_unlock(&printMutex);
    }

    // Destroy mutex and condition variables
    pthread_mutex_destroy(&TheMutex);
    pthread_cond_destroy(&notFull);
    pthread_cond_destroy(&notEmpty);
    pthread_mutex_destroy(&printMutex);

    // Close the output file
    outFile.close();

    return 0;
}
