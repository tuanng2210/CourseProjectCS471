#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <chrono>
#include <unistd.h>

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

    //Create semaphores
    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    //Record start time
    auto startTime = chrono::high_resolution_clock::now();

    //Make the threads
    pthread_t producerThreads[numProducers];
    pthread_t consumerThreads[numConsumers];

    for(int i = 0; i < numProducers; i++)
    {
        pthread_create(&producerThreads[i], NULL, producer, NULL);
    }

    for(int i = 0; i < numConsumers; i++)
    {
        pthread_create(&consumerThreads[i], NULL, consumer, NULL);
    }

    //this_thread::sleep_for(chrono::milliseconds(sleepTime));

    //Sleep in milliseconds
    usleep(sleepTime * 1000);

    //Join the threads together
    for(int i = 0; i < numProducers; i++)
    {
        pthread_join(producerThreads[i], NULL);
    }

    for(int i = 0; i < numConsumers; i++)
    {
        pthread_join(consumerThreads[i], NULL);
    }

    //Record end time
    auto end_time = chrono::high_resolution_clock::now();

    //Destroy the semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    //Turnaround time
    auto duration = chrono::duration_cast<chrono::milliseconds> (end_time - startTime);

    cout << "Turnaround time: " << duration.count() << " ms\n";

    return 0;

    ofstream outfile;
    outfile.open("processSynchronization.txt");

}