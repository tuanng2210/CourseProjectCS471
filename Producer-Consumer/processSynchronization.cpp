#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <vector>
#include <chrono>

using namespace std;

const int bufferSize = 5;

vector<int> buffer;

sem_t empty;

sem_t full;

sem_t mutex;



void *producer(void *arguments)
{
    int theItem = 0;

    while(true)
    {
        //produce a new item
        theItem++;
        
        //wait for an empty slot to appear in the buffer
        sem_wait(&empty);

        //wait for mutex to appear
        sem_wait(&mutex);

        //add the item to the buffer
        buffer.push_back(theItem);
        cout << "Item: " << theItem << " is produced." << endl;

        //let go of mutex
        sem_post(&mutex);

        //change the status of the buffer from empty to full
        sem_post(&full);

    }
}

void *consumer(void *arguments)
{

    while(true)
    {
        
        //wait for an full slot to appear in the buffer
        sem_wait(&full);

        //wait for mutex to appear
        sem_wait(&mutex);

        //remove the item from the buffer
        int item = buffer.back();
        buffer.push_back(item);
        cout << "Item: " << item << " is consumed." << endl;


        //let go of mutex
        sem_post(&mutex);

        //change the status of the buffer from full to empty
        sem_post(&full);

    }
}



int main(int argc, char *argv[])
{

    if(argc != 4)
    {
        cout << "Usage " << argv[0] << "|Number of Producers| |Number of Consumers| |Sleep Time|\n";
        return 1;
    }

    int numProducers = stoi(argv[1]);
    int numConsumers = stoi(argv[2]);
    int sleepTime = stoi(argv[3]);

    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    auto startTime = chrono::high_resolution_clock::now();
    pthread_t threadOne;

    // Get Command line arguments
    // Initialize buffer
    // Create Producer Threads
    // Create Consumer Threads
    // Sleep
    // Exit

    printf("Calling thread\n");

    //pthread_create(&threadOne, NULL, ThreadFunction, NULL);


    return 0;

    ofstream outfile;
    outfile.open("processSynchronization.txt");

}