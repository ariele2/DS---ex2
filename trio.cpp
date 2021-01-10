#include "trio.h"

trio::trio(int d1, int d2, int d3): data1(d1),data2(d2),data3(d3) {};

bool operator<(const trio &t1, const trio &t2) {
    if (t1.data1 < t2.data1) {
        return true;
    }
    else if (t1.data1 == t2.data1 && t1.data2 > t2.data2) { // time is equivalent, then the one with the smaller course number is bigger
        return true;
    }
    else if (t1.data1 == t2.data1 && t1.data2 == t2.data2 && t1.data3 > t2.data3) { //time and course number are the same, but class is bigger
        return true;
    }
    return false;
}

bool operator==(const trio &t1, const trio &t2) {
    return (t1.data1==t2.data1 && t1.data2==t2.data2 && t1.data2==t2.data2);
}

bool operator>(const trio &t1, const trio &t2) {
    return !(t1<t2 || t1==t2);
}

bool operator>=(const trio &t1, const trio &t2) {
    return (t1>t2 || t1==t2);
}

bool operator<=(const trio &t1, const trio &t2) {
    return (t1<t2 || t1==t2);
}

int trio::getData1() {
    return data1;
}

int trio::getData2() {
    return data2;
}

int trio::getData3() {
    return data3;
}