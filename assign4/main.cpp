/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Erin Bailey and Zach Miller
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore>
#include <thread>
#include <mutex>

using namespace std;

// global buffer object
Buffer buffer;
const int MAX_SIZE = 5;
counting_semaphore<MAX_SIZE> empty_slots(MAX_SIZE);    // Initialize with max buffer slots
counting_semaphore<MAX_SIZE> full_slots(MAX_SIZE);     // Initialize with 0 full slots
mutex buffer_mutex;                                    // Mutex for critical sections in buffer

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);    // each producer had a unique ID

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);

        empty_slots.acquire();  // wait for empty slot
        {
            // TODO: Add synchronization code here
            if (buffer.insert_item(item)) {
                cout << "Producer " << item << ": Inserted item " << item << endl;
                buffer.print_buffer();
            } else {
                cout << "Producer error condition"  << endl;    // shouldn't come here
            }
        }

        full_slots.release();   // Signal that there is a new full slot
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;
    int consumer_id = *((int *) param);  // Unique consumer ID
    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        full_slots.acquire();  // Wait for a full slot

        {
            // TODO: Add synchronization code here
            if (buffer.remove_item(&item)) {
                cout << "Consumer " << item << ": Removed item " << item << endl;
                buffer.print_buffer();
            } else {
                cout << "Consumer error condition" << endl;    // shouldn't come here
            }
        }

        empty_slots.release();  // Signal that there is a new empty slot
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */

    // iterate through buffer and populate (producer) for testing
    // for(int i = 0; i <= buffer.get_size(); i++){
    //     buffer_item item = i; 
    //     cout << "try insert " << i << endl;
    //     if(buffer.insert_item(item)) buffer.print_buffer();
    // }

    // // consumer for testing
    // for(int i = buffer.get_size() - 1; i >= 0; i--){
    //     buffer_item *item;
    //     buffer.remove_item(item);
    //     cout << "item removed was " << *item << endl;
    //     buffer.print_buffer();
    // }
    int producer_count = 3;  // Default or set via command line
    int consumer_count = 3;

    // Initialize producer and consumer threads
    pthread_t producers[producer_count];
    pthread_t consumers[consumer_count];

    int producer_ids[producer_count];
    int consumer_ids[consumer_count];

    // Create producer threads
    for (int i = 0; i < producer_count; ++i) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], nullptr, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < consumer_count; ++i) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], nullptr, consumer, &consumer_ids[i]);
    }

    // Wait for threads to finish (in this case, they run indefinitely)
    for (int i = 0; i < producer_count; ++i) {
        pthread_join(producers[i], nullptr);
    }
    for (int i = 0; i < consumer_count; ++i) {
        pthread_join(consumers[i], nullptr);
    }

    return 0;


}
