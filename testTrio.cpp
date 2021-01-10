#include "trio.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
    trio t1(2,4,6);
    trio t2(3,7,9);
    trio t3(0,2,33);
    trio t4(2,3,7);
    trio t5(2,4,5);
    trio t6(2,4,6);
    if (t1 == t6) {
        cout << "t1 = t6" << endl;
    }
    if (t1 < t2) {
        cout << "t1 < t2" << endl;
    }

    if (t2 > t3) {
        cout << "t2 > t3" << endl;
    }
    if (t1 < t4) {
        cout << "t1 < t4" << endl;
    }
    if (t5 > t1) {
        cout << "t1 < t5" << endl;
    }
    if (t4 > t5) {
        cout << "t1 = t6" << endl;
    }
    return 0;
}
