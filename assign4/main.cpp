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

    /* TODO: 2. Initialize buffer and synchronization primitives */
    
    counting_semaphore<5> empty(5);
    counting_semaphore<5> full(0);
    mutex buff_mtx;


    /* TODO: 3. Create producer thread(s). */

    for(int i = 1; i <= num_prod; i++){
        
    }

    /* You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */


/*buffer test
    for(int i = 0; i <= buffer.get_size(); i++){
        buffer_item item = i; 
        cout << "try insert " << i << endl;
        if(buffer.insert_item(item)) buffer.print_buffer();
    }
    for(int i = buffer.get_size() - 1; i >= 0; i--){
        buffer_item *item;
        buffer.remove_item(item);
        cout << "item removed was " << *item << endl;
        buffer.print_buffer();
    }
*/
}
