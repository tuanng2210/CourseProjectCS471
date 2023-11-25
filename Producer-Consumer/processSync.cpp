#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cstdlib>

#define BUFFER_SIZE 5
#define TRUE 1

std::mutex mtx;
std::condition_variable empty, full;

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void insert_item(int item) {
    std::unique_lock<std::mutex> lock(mtx);

    // Wait until there is space in the buffer
    while ((in + 1) % BUFFER_SIZE == out) {
        full.wait(lock);
    }

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    // Signal that the buffer is not empty anymore
    empty.notify_all();

    // Print debug information
    std::cout << "Insert_item inserted item " << item << " at position " << in - 1 << " [";
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i == in - 1) std::cout << buffer[i];
        else std::cout << ((i == 0) ? "empty" : "," + std::to_string(buffer[i]));
    }
    std::cout << "] in = " << in << ", out = " << out << std::endl;
}

int remove_item() {
    std::unique_lock<std::mutex> lock(mtx);

    // Wait until there is an item in the buffer
    while (in == out) {
        empty.wait(lock);
    }

    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    // Signal that the buffer is not full anymore
    full.notify_all();

    // Print debug information
    std::cout << "Remove_item removed item " << item << " at position " << out - 1 << " [";
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i == out - 1) std::cout << "empty";
        else std::cout << ((i == 0) ? std::to_string(buffer[i]) : "," + std::to_string(buffer[i]));
    }
    std::cout << "] in = " << in << ", out = " << out << std::endl;

    return item;
}

void producer(int id) {
    while (TRUE) {
        // Generate random sleep time
        int sleep_time = (rand() % 3) + 1;
        std::cout << "Producer thread " << id << " sleeping for " << sleep_time << " seconds\n";
        std::this_thread::sleep_for(std::chrono::seconds(sleep_time));

        // Generate a random product
        int item = rand();

        // Insert the item into the buffer
        insert_item(item);
    }
}

void consumer(int id) {
    while (TRUE) {
        // Generate random sleep time
        int sleep_time = (rand() % 3) + 1;
        std::cout << "Consumer thread " << id << " sleeping for " << sleep_time << " seconds\n";
        std::this_thread::sleep_for(std::chrono::seconds(sleep_time));

        // Remove an item from the buffer
        int item = remove_item();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <runtime> <num_producers> <num_consumers>\n";
        return -1;
    }

    int runtime = std::atoi(argv[1]);
    int num_producers = std::atoi(argv[2]);
    int num_consumers = std::atoi(argv[3]);

    std::cout << "Main thread beginning\n";

    // Create producer threads
    std::vector<std::thread> producer_threads;
    for (int i = 0; i < num_producers; i++) {
        std::cout << "Creating producer thread with id " << i << std::endl;
        producer_threads.emplace_back(producer, i);
    }

    // Create consumer threads
    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < num_consumers; i++) {
        std::cout << "Creating consumer thread with id " << i << std::endl;
        consumer_threads.emplace_back(consumer, i);
    }

    std::cout << "Main thread sleeping for " << runtime << " seconds\n";
    std::this_thread::sleep_for(std::chrono::seconds(runtime));

    std::cout << "Main thread exiting\n";

    // Join threads
    for (auto& thread : producer_threads) {
        thread.join();
    }

    for (auto& thread : consumer_threads) {
        thread.join();
    }

    return 0;
}
