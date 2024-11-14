/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Erin Bailey and Zach Miller
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <semaphore>
#include <mutex>
#include <vector>

using namespace std;

// global buffer object
Buffer buffer;

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
    }
}

int main(int argc, char *argv[]) {
    /* 1. Get command line arguments argv[1],argv[2],argv[3] */
    int main_sleep = stoi(argv[1]),
        num_prod = stoi(argv[2]),
        num_con = stoi(argv[3]);

    /* 2. Initialize buffer and synchronization primitives */
    
    counting_semaphore<5> empty(5);
    counting_semaphore<5> full(0);
    mutex buff_mtx;


    /* 3. Create producer thread(s). */
    vector<pthread_t> producer_threads(num_prod);
    int argprod[num_prod];
    for(int i = 0; i < num_prod; i++){
        argprod[i] = i + 1;
    }
    for(vector<pthread_t>::iterator it = producer_threads.begin(); it != producer_threads.end(); it++){
        int i = 0;
        int r = pthread_create(&*it, NULL, producer, &argprod[i]); 
        i++;
    }

    /* You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* 4. Create consumer thread(s) */

    vector<pthread_t> consumer_threads(num_prod);
    int argcon[num_prod];
    for(int i = 0; i < num_prod; i++){
        argcon[i] = i + 1;
    }
    for(vector<pthread_t>::iterator it = consumer_threads.begin(); it != producer_threads.end(); it++){
        int i = 0;
        int r = pthread_create(&*it, NULL, consumer, &argcon[i]); 
        i++;
    }

    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
}
