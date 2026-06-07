#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T*  data;
    int size;
    int capacity;

    // Internal helper to resize the array
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor
    DynamicArray(int initialCapacity = 10) {
        if (initialCapacity <= 0) initialCapacity = 10;
        capacity = initialCapacity;
        size = 0;
        data = new T[capacity];
    }

    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Copy Constructor (Rule of Three)
    DynamicArray(const DynamicArray& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Assignment Operator (Rule of Three)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Adds an element to the end of the array
    void push_back(const T& element) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = element;
    }

    // Removes an element at a specific index and shifts subsequent elements
    void removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    // Getters
    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    // Subscript Operators
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

#endif
