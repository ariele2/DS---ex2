#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <class T>
class DynamicArray {
    int size;
    int capacity; //how much elements in the array currently
    T* array;
public:
    DynamicArray<T>();
    DynamicArray<T>(int size);
    DynamicArray<T>(const DynamicArray<T> &original);
    ~DynamicArray<T>();  
    int getSize();
    int getCapacity();
    void resize(int newSize);
    T& operator[](int index);
    void insert();
    class AllocationError{};
};

template <class T>
DynamicArray<T>::DynamicArray(): size(2),capacity(0), array(new T[size]) {}

template <class T>
DynamicArray<T>::DynamicArray(int size): size(size),capacity(0), array(new T[size]) {}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &original) { //copy c'tor
    size  = original.size;
    capacity = original.capacity;
    array = new T[size];
    if (!array) {
        throw AllocationError();
    }
    for (int i = 0; i < size; i++) {
        array[i] = original.array[i];
    }
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] array;
}

template <class T>
int DynamicArray<T>::getSize() {
    return size;
}

template <class T>
int DynamicArray<T>::getCapacity() {
    return capacity;
}

template <class T>
void DynamicArray<T>::resize(int newSize) {
    T* temp;
    temp = new T[newSize];
    if (!temp) {
        throw AllocationError();
    }
    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    size = newSize;
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
    return array[index]; // returned as a reference
}

template <class T>
void DynamicArray<T>::insert() {
    if (capacity == size) {
        resize(size*2);
    }
    capacity++;
}

#endif