#ifndef TRIO_H
#define TRIO_H

class trio {
    int data1;
    int data2;
    int data3;
    public:
    trio() = default;
    trio (int d1, int d2, int d3);
    ~trio() = default;
    trio(const trio &t) = default; //default copy c'tor
    friend bool operator<(const trio &t1, const trio &t2);
    friend bool operator==(const trio &t1, const trio &t2);
    int getData1();
    int getData2();
    int getData3();
};

bool operator<=(const trio &t1, const trio &t2);
bool operator>=(const trio &t1, const trio &t2);
bool operator>(const trio &t1, const trio &t2);
bool operator!=(const trio &t1, const trio &t2);



#endif // TRIO_H