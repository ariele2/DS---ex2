#include "dynamicArray.h"
#include <iostream>

using namespace std;
int main() {
    DynamicArray<int> array1;
    array1[0] = 8;
    array1[1] = 7;
    array1.resize(array1.getSize()*2);
    array1[2] = 3;
    array1[3] = 2;
    for (int i=0; i<array1.getSize(); i++) {
        cout << array1[i] << endl;
    }
    return 0;
}