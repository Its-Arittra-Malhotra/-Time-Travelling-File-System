
#pragma once

#include "Heap.hpp"

// -------------------------------
// Constructors
// -------------------------------
template <typename T, typename Comparator>
Heap<T, Comparator>::Heap() : comp(Comparator()) {}

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(Comparator comparator) : comp(comparator) {}


template <typename T, typename Comparator>
void Heap<T, Comparator>::push(T value) {
    data.push_back(value);
    int idx = (int)data.size() - 1;

    // sift up
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (comp(data[parent], data[idx])) { // if parent < child (for max heap)
            std::swap(data[parent], data[idx]);
            idx = parent;
        } else {
            break;
        }
    }
}


template <typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
    if (data.empty()) return;

    std::swap(data[0], data.back());
    data.pop_back();

    if (!data.empty())
        heapify(0);
}


template <typename T, typename Comparator>
const T& Heap<T, Comparator>::top() const {
    return data.front();
}


template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const {
    return data.empty();
}


template <typename T, typename Comparator>
int Heap<T, Comparator>::size() const {
    return (int)data.size();
}


template <typename T, typename Comparator>
int Heap<T, Comparator>::heapify(int index) {
    int n = (int)data.size();
    int largest = index;

    while (true) {
        int left = 2 * largest + 1;
        int right = 2 * largest + 2;
        int newLargest = largest;

        if (left < n && comp(data[newLargest], data[left]))
            newLargest = left;
        if (right < n && comp(data[newLargest], data[right]))
            newLargest = right;

        if (newLargest != largest) {
            std::swap(data[largest], data[newLargest]);
            largest = newLargest;
        } else {
            break;
        }
    }
    return largest;
}
