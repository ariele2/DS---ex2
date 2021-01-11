#include "HashChain.h"

using namespace std;

int main() {
    HashChain table(4);
    int course_range = 10, classes_range = 4;
    //add courses to the hash table
    for (int i=100; i<100 + course_range; i++) { 
        table.insertCourse(i);
    }
    //add classes to the courses in the hash table
    for (int j=100; j<100 + course_range; j++) {
        for (int k=0; k < classes_range; k++) {
            table.insertClass(j);
        }
    }
    table.displayHash();
    return 0;
}