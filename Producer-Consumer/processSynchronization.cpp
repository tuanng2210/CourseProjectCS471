#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>

using namespace std;

void * ThreadFunction(void *arguments)
{
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