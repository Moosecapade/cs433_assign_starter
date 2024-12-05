/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"

// TODO: Add your implementation of the Replacement member functions here

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	this->num_pages = num_pages;
    this->num_frames = num_frames;
}

// Destructor
Replacement::~Replacement()
{
    // TOOD: Add your code here
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)//all mem accesses are
{
    // If the page is valid, it calls the touch_page function. 
    // If the page is not valid but free frames are available, it calls the load_page function.
    // If the page is not valid and there is no free frame, it calls the replace_page function.
    

    PageEntry* apage = &page_table[page_num];

    if(apage->valid == false){
        //page is not valid
        if(num_frames > used_frames){
            //free frames exist
            //call load_page
        }else{
            //no free frames exist
            //call replace_page
        }

    }else {
        //page IS valid
        //call touch_page
    }

    counter++;

    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        // TODO: print out the number of references, number of page faults and number of page replacements
		std::cout << "Number of references: \t\t"  << num_refs << std::endl;
		std::cout << "Number of page faults: \t\t" << num_fault << std::endl;
		std::cout << "Number of page replacements: \t"  << num_replace << std::endl;
}
