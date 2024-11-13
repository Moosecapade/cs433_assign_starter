/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Erin Bailey and Zach Miller
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <iostream>


/**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
    Buffer::Buffer(int size = 5){
        this->size  = size;
        front = 0; // front is where items are to be inserted in the buffer
        back = 0;  // back is where items are to be removed from
        buffer = new int[size];
    }

    /**
     * @brief Destroy the Buffer object
     */
    Buffer::~Buffer(){
        delete buffer;
    }

    /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
    bool Buffer::insert_item(buffer_item item){
        if(front != mod(back - 1, size)){//buffer not empty
            buffer[front] = item;
            front = (front + 1) % size;
            return true;
        }else return false;
    }

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    bool Buffer::remove_item(buffer_item *item){
        if(front != back){
            *item = buffer[back];
            back = (back + 1) % size;
            return true;
        }else return false;

    }

    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
    int Buffer::get_size(){
        return size;

    }

    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
    int Buffer::get_count(){
        //cases
        //1: count = 0
        //2: front > back
        //3: front < back

        //case 1
        if(front == back){
            return 0;
        }else
        if(front > back){
            return front - back;
        }else{//front < back
            return size - (back - front);
        }
    }

    /**
     * @brief Chceck if the buffer is empty
     * @return true if the buffer is empty, else false
     */
    bool Buffer::is_empty(){
        if(front == back) return true;
        else return false;
    }
    /**
     * @brief Check if the buffer is full
     * @return true if the buffer is full, else false
     */
    bool Buffer::is_full(){
        if(front == mod(back - 1, size)) return true;
        else return false;
    }

    /**
     * @brief Print the buffer
     */
    void Buffer::print_buffer(){
        std::cout << "Buffer: [";
        for(int i = 0; i < size; i++){
            std::cout << buffer[i];
            if(i != size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
// TODO: Add your implementation of the buffer class here

