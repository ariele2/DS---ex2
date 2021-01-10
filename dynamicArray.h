#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <class T>
class DynamicArray {
    int size;
    T* array;
public:
    DynamicArray<T>();
    DynamicArray<T>(int size);
    DynamicArray<T>(const DynamicArray<T> &original);
    ~DynamicArray<T>();  
    int getSize();
    void resize(int newSize);
    T& operator[](int index);
};

template <class T>
DynamicArray<T>::DynamicArray(): size(2), array(new T[size]) {}

DynamicArray<T>::DynamicArray(int size): size(size), array(new T[size]) {}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &original) { //copy c'tor
    size  = original.size;
    array = new T[size];
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
void DynamicArray<T>::resize(int newSize) {
    T* temp;
    temp = new T[newSize];
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

#endif