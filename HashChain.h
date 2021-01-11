#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H

#include "linked_list.h"
#include "dynamicArray.h"
#include "rankedAVL.h"

class HashChain 
{ 
    int weight;    // weight factor for the hashing
    int elements_num; // current numbr of elements inside of the hash table 
    // pointer to dynamic array
    DynamicArray<linked_list<DynamicArray<Tnode_v2*>*>>* data; 
    node<DynamicArray<Tnode_v2*>*>* findCourse(int course_number);
    int hashFunction(int course_number, int module) { 
        return (course_number % module); 
    } 
    void clearHash();

public: 
    HashChain(int w);  // Constructor , need to enter weight factor
    // inserts a key into hash table 
    void insertCourse(int course_number); 
    // deletes a key from hash table 
    void deleteCourse(int course_number); 
    // hash function to map values to key 
    void insertClass(int course_number);
    void displayHash(); 
    ~HashChain() {
       clearHash();
       delete data;
    }
}; 
  
HashChain::HashChain(int w) : weight(w), elements_num(0), data(new DynamicArray<linked_list<DynamicArray<Tnode_v2*>*>>) {
    for (int i=0; i<data->getSize(); i++) {
        (*data)[i].add_head(-1);
    }
}
  
void HashChain::insertCourse(int course_number) 
{ 
    int curr_hash_size = data->getSize();
    int resize_factor = weight*curr_hash_size;
    if (elements_num == resize_factor) { //need to resize
        DynamicArray<linked_list<DynamicArray<Tnode_v2*>*>>* new_data = new DynamicArray<linked_list<DynamicArray<Tnode_v2*>*>>(curr_hash_size*2);
        for (int j=0; j<curr_hash_size*2; j++) {
            (*new_data)[j].add_head(-1); //add head to all the hash table cells
        }
        for (int i=0; i<curr_hash_size; i++) { //copy all the former elements with the new hash function
            node<DynamicArray<Tnode_v2*>*>* move_course = (*data)[i].get_tail();
            DynamicArray<Tnode_v2*>* classes_to_move = move_course->data;
            while (move_course->id != -1) {
                int new_index = hashFunction(move_course->id, curr_hash_size*2);
                (*new_data)[new_index].add_after(move_course->id, classes_to_move, (*new_data)[new_index].get_tail());
                move_course = move_course->prev;
                classes_to_move = move_course->data;
            }
        }
        delete data;
        data = new_data;
    }
    int insert_index = hashFunction(course_number, curr_hash_size);
    DynamicArray<Tnode_v2*>* classes = new DynamicArray<Tnode_v2*>; 
    (*data)[insert_index].add_after(course_number, classes, (*data)[insert_index].get_tail()); //adds the element to the end of the linked list
    elements_num++;
} 
  
void HashChain::deleteCourse(int course_number) 
{ 
    int curr_hash_size = data->getSize();
    int remove_index = hashFunction(course_number, curr_hash_size);
    auto course = findCourse(course_number); 
    if (!course) {
        return;
    }
    delete course->data;
    (*data)[remove_index].remove(course);
    elements_num--;
    //check if the table is 4 times bigger then the elements, if so - should divide its size by 2
    if (curr_hash_size>2 && curr_hash_size>=elements_num*2) { 
        DynamicArray<linked_list<DynamicArray<Tnode_v2*>*>>* new_data = new DynamicArray<linked_list<DynamicArray<Tnode_v2*>*>>(curr_hash_size/2);
        for (int j=0; j<curr_hash_size/2; j++) {
            (*new_data)[j].add_head(-1); //add head to all the hash table cells
        }
        for (int i=0; i<curr_hash_size; i++) { //copy all the former elements with the new hash function
            node<DynamicArray<Tnode_v2*>*>* move_course = (*data)[i].get_tail();
            DynamicArray<Tnode_v2*>* classes_to_move = move_course->data;
            while (move_course->id != -1) {
                int new_index = hashFunction(move_course->id, curr_hash_size/2);
                (*new_data)[new_index].add_after(move_course->id, classes_to_move, (*new_data)[new_index].get_tail());
                move_course = move_course->prev;
                classes_to_move = move_course->data;
            }
        }
        delete data;
        data = new_data;
    }
} 

node<DynamicArray<Tnode_v2*>*>* HashChain::findCourse(int course_number) {
    int index = hashFunction(course_number, data->getSize());
    node<DynamicArray<Tnode_v2*>*>* course = (*data)[index].get_tail();
    while (course->id != -1) {
        if (course->id == course_number) {
            return course;
        }
        course = course->prev;
    }
    return nullptr;
}

void HashChain::insertClass(int course_number) {
    auto course = findCourse(course_number);
    if (course) {
        course->data->insert();
        (*(course->data))[course->data->getCapacity()-1] = nullptr;
    }
}

void HashChain::clearHash() {
    int curr_hash_size = data->getSize();
    for (int i=0; i<curr_hash_size; i++) {
        auto course = (*data)[i].get_tail();
        while (course->id != -1) {
            delete course->data;
            course = course->prev;
        }
    }
}
  
// function to display hash table 
void HashChain::displayHash() { 
    for (int i = 0; i < data->getSize(); i++) { 
        std::cout << "index:" << i << std::endl; 
        std::cout << "elements:";
        node<DynamicArray<Tnode_v2*>*>* course = (*data)[i].get_tail();
        while (course->id != -1) {
            int classes_num = course->data->getCapacity();
            std::cout << " --> " << "course:" << course->id <<", classes:" << classes_num;
            course = course->prev;
        }
        std::cout<<std::endl;
    } 
}


#endif // HASH_CHAIN_H