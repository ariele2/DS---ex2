#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
#include "linked_list.h"
#include "dynamicArray.h"
#include "rankedAVL.h"

class HashChain 
{ 
    int weight;    // weight factor for the hashing
    int elements_num; // current numbr of elements inside of the hash table 
    DynamicArray<linked_list<DynamicArray<Tnode_v2>*>>* data; //the cells of the hash table

public: 
    HashChain(int w);  // Constructor , need to enter weight factor
    // inserts a key into hash table 
    void insertItem(int course_number); 
    // deletes a key from hash table 
    void deleteItem(int course_number); 
    // hash function to map values to key 
    int hashFunction(int course_number, int module) { 
        return (course_number % module); 
    } 
  
    void displayHash(); 
}; 
  
HashChain::HashChain(int w) : weight(w), elements_num(0), data(new DynamicArray<linked_list<DynamicArray<Tnode_v2>*>>) {
    for (int i=0; i<data->getSize(); i++) {
        (*data)[i].add_head(-1);
    }
}
  
void HashChain::insertItem(int course_number) 
{ 
    int curr_hash_size = data->getSize();
    int resize_factor = weight*curr_hash_size;
    if (elements_num == resize_factor) { //need to resize
        DynamicArray<linked_list<DynamicArray<Tnode_v2>*>>* new_data = new DynamicArray<linked_list<DynamicArray<Tnode_v2>*>>(curr_hash_size*2);
        for (int j=0; j<curr_hash_size*2; j++) {
            (*new_data)[j].add_head(-1);
        }
        for (int i=0; i<curr_hash_size; i++) {
            int move_course_num = (*data)[i].get_tail()->id;
            DynamicArray<Tnode_v2>* classes_to_move = (*data)[i].get_tail()->data;
            if (move_course_num != -1) {
                int new_index = hashFunction(move_course_num, curr_hash_size*2);
                (*new_data)[new_index].add_after(move_course_num, classes_to_move, (*new_data)[new_index].get_tail());
            }
        }
        delete data;
        data = new_data;
    }
    int insert_index = hashFunction(course_number, curr_hash_size);
    DynamicArray<Tnode_v2>* classes = new DynamicArray<Tnode_v2>; 
    (*data)[insert_index].add_after(course_number, classes, (*data)[insert_index].get_tail());
} 
  
void HashChain::deleteItem(int course_number) 
{ 
  // get the hash index of key 
  int index = hashFunction(key); 
  
  // find the key in (inex)th list 
  list <int> :: iterator i; 
  for (i = table[index].begin(); 
           i != table[index].end(); i++) { 
    if (*i == key) 
      break; 
  } 
  
  // if key is found in hash table, remove it 
  if (i != table[index].end()) 
    table[index].erase(i); 
} 
  
// function to display hash table 
void Hash::displayHash() { 
  for (int i = 0; i < BUCKET; i++) { 
    cout << i; 
    for (auto x : table[i]) 
      cout << " --> " << x; 
    cout << endl; 
  } 
}


#endif // HASH_CHAIN_H