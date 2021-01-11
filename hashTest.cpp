#include "HashChain.h"

using namespace std;

int main() {
    HashChain table(4);
    int course_range = 50, classes_range = 12;
    //add courses to the hash table
    cout << "------~Insertion section~------" << endl;
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
    //remove section
    cout << "------~Removing section~------" << endl;
    for (int n=100; n<100+ course_range-6; n++) {
        table.deleteCourse(n);
    }
    table.displayHash();
    return 0;
}