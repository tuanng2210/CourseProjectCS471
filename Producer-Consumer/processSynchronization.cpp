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

        buffer.push_back(theItem);
        cout << "Item was produced";

        //let go of mutex
        sem_post(&mutex);

        //change the status of the buffer from empty to full
        sem_post(&full);

    }
    printf("Thread is running\n");
    return NULL;
}

int main()
{

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