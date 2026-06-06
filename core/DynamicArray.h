#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

// TEMPLATE CLASS
 
#include <iostream>
using namespace std;

template <typename T>
class DynamicArray {
private:
     T* arr;
     int size;
     int capacity;

     //Private resize helper
     void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for(int i = 0; i < size; i++) 
           newArr[i] = arr[i];
        delete [] arr;
        arr = newArr;
     }
public:
     //Constructor
     DynamicArray(int inititalCapacity = 10) {
         capacity = initialCapacity;
         size = 0;
         arr = new T[capacity];
     }

     //Destructor 
     ~DynamicArray() {
        delete [] arr;
     }

     //Copy Constructor (Deep Copy) 
     DynamicArray(const DynamicArray& other) {
         capacity = other.capacity;
         size = other.size;
         arr = new T[capacity];
         for(int i = 0; i < size; i++) 
             arr[i] = other.arr[i];
     }

     //Assignment Operator (Deep Copy)
     DynamicArray& operator=(const DynamicArray& other) {
           if(this !=& other) {
            delete [] arr;
            capacity = other.capacity;
            size = other.size;
            arr = new T[capacity];
            for(int i = 0; i < size; i++) 
              arr[i] = other.arr[i];
           }
           return *this;
     }

     //Core Methods
     void add(T item) {
        if(size == capacity) resize();
        arr[size++] = item;
     }

     bool removeAt(int index) {
        if(index < 0 || index >= size) return false;
        for(int i = index; i <= size - 1; i++) 
          arr[i] = arr[i + 1];
          size--;
        return true;
     }

     //Operator Overloading
     T& operator[](int index) {
        return arr[index];
     }

     const T& operator[](int index const) {
        return arr[index];
     }

     //Utility Getters
     int getSize() const { return size; }
     bool isEmpty() const { return size == 0; }
};
#endif 