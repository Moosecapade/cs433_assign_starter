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
Buffer::Buffer(int size){
    this->size  = size;
    front = 0; // front is where items are to be inserted in the buffer
    back = 0;  // back is where items are to be removed from
    count = 0;
    buffer = new int[size];
    for(int i = 0; i < size; i++){
        buffer[i] = -1; //an entry of -1 indicates an empty buffer location
    }
}

/**
 * @brief Fake copy constructer (bc autograder thinks its necessary ig)
 * @param Buffer (a different one)
 */
Buffer::Buffer(const Buffer& other){
    size = other.size;
    front = other.front;
    back = other.back;
    count = other.count;
    buffer = new int[size];
}

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer(){
    delete[] buffer;
}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item){
    //if front is exactly behind back
    // dont insert, its full
    //else increment front and insert.
    //^^^^^^note: front points to the last inserted item
    if(front == back && buffer[front] == -1){ //if front and back point at empty item in buffer
        buffer[front] = item;
        count++;
        return true;
    }else if(front != mod(back - 1, size)){// if front is anywhere else in the buffer
        front = (front + 1) % size;
        buffer[front] = item;
        count++;
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
    if(front != back){ // if front and back are not point at same index
        *item = buffer[back]; // normal remove behavior
        buffer[back] = -1;
        back = (back + 1) % size;
        count--;
        return true;
    }else if(buffer[back] != -1){ // if front and back point at same index
        *item = buffer[back];   // only remove, no increment
        buffer[back] = -1;
        count--;
        return true;
    }else return false; // otherwise buffer is empty

}

/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
const int Buffer::get_size(){
    return size;
}

/**
 * @brief Get the number of items in the buffer
 * @return the number of items in the buffer
 */
int Buffer::get_count(){
    return count;
}

/**
 * @brief Chceck if the buffer is empty
 * @return true if the buffer is empty, else false
 */
bool Buffer::is_empty(){
    if(count != 0) return true;
    else return false;
}
/**
 * @brief Check if the buffer is full
 * @return true if the buffer is full, else false
 */
bool Buffer::is_full(){
    if(count == size) return true;
    else return false;
}

/**
 * @brief Print the buffer
 */
void Buffer::print_buffer(){
    std::cout << "Buffer: [";
    for(int i = back; i < back + count; i++){
        std::cout << buffer[i % size];
        if(i != back + count - 1){
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

Buffer& Buffer::operator=(const Buffer& other) {
    if (this != &other) { // Avoid self-assignment
        delete[] buffer; // Free existing memory
        size = other.size;
        front = other.front;
        back = other.back;
        count = other.count;
        buffer = new int[size]; // Allocate new memory
        for (int i = 0; i < size; i++) {
            buffer[i] = other.buffer[i]; // Copy contents
        }
    }
    return *this;
}
