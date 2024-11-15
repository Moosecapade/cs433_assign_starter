/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @brief The main program for the producer consumer problem using POSIX semaphores.
 * @version 0.1
 */

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include "buffer.h"

using namespace std;

// Global objects
Buffer buffer(5); // Initialize buffer with size 5
sem_t empty;      // Semaphore to track empty slots in the buffer
sem_t full;       // Semaphore to track full slots in the buffer
mutex buffer_mutex; // Mutex for critical sections in the buffer

// Producer thread function
void *producer(void *param) {
    int id = *((int *) param); // Each producer gets a unique ID
    buffer_item item = id;

    while (true) {
        usleep(rand() % 1000000); // Simulate random production delay

        sem_wait(&empty); // Wait for an empty slot

        {
            lock_guard<mutex> lock(buffer_mutex); // Lock critical section
            if (buffer.insert_item(item)) {
                cout << "Producer " << id << ": Inserted item " << item << endl;
                buffer.print_buffer();
            } else {
                cout << "Producer " << id << ": Buffer is full (error condition)" << endl;
            }
        }

        sem_post(&full); // Signal that an item was added
    }
}

// Consumer thread function
void *consumer(void *param) {
    int id = *((int *) param); // Each consumer gets a unique ID
    buffer_item item;

    while (true) {
        usleep(rand() % 1000000); // Simulate random consumption delay

        sem_wait(&full); // Wait for a full slot

        {
            lock_guard<mutex> lock(buffer_mutex); // Lock critical section
            if (buffer.remove_item(&item)) {
                cout << "Consumer " << id << ": Removed item " << item << endl;
                buffer.print_buffer();
            } else {
                cout << "Consumer " << id << ": Buffer is empty (error condition)" << endl;
            }
        }

        sem_post(&empty); // Signal that an item was removed
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " 'sleep duration', 'number of producers', 'number of consumers'" << endl;
        exit(1);
    }

    // Parse command-line arguments
    int main_sleep = stoi(argv[1]);
    int num_producers = stoi(argv[2]);
    int num_consumers = stoi(argv[3]);

    // Initialize semaphores
    sem_init(&empty, 0, 5); // Buffer has 5 empty slots initially
    sem_init(&full, 0, 0);  // Buffer starts with 0 full slots

    vector<pthread_t> producer_threads(num_producers);
    vector<pthread_t> consumer_threads(num_consumers);

    vector<int> producer_ids(num_producers);
    vector<int> consumer_ids(num_consumers);

    // Create producer threads
    for (int i = 0; i < num_producers; ++i) {
        producer_ids[i] = i + 1;
        pthread_create(&producer_threads[i], nullptr, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; ++i) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], nullptr, consumer, &consumer_ids[i]);
    }

    // Main thread sleeps for the specified time
    sleep(main_sleep);

    // Cleanup: Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
