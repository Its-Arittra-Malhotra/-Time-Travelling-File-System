#ifndef TIME_TRAVELLING_FILE_SYSTEM_HEAP_H
#define TIME_TRAVELLING_FILE_SYSTEM_HEAP_H

// -----------------------------------------------------------------------------
// Project:   [Time-Travelling File System]
// Module:    [Heap]
// Author:    [Arittra Malhotra]
// Purpose:   very general heap , with required comparator classes for bigtree and recent files
// -----------------------------------------------------------------------------

#pragma once

// -------------------------------
// Includes
// -------------------------------
#include <vector>
#include <string>
#include <ctime>   // for time_t
#include"types.hpp"

// -------------------------------
// Comparator Structs
// -------------------------------
struct CompareBigTree {
    bool operator()(big_tree a, big_tree b) const {
        return a.size < b.size; // max heap by size
    }
};

struct CompareRecentFile {
    bool operator()( recent_file a,  recent_file b) const {
        return a.modif_time < b.modif_time; // max heap by modification time
    }
};

// -------------------------------
// Class Template Declaration
// -------------------------------
template <typename T, typename Comparator>
class Heap {
public:
    Heap();
    explicit Heap( Comparator comparator);

    void push(T value);
    void pop();
    const T& top() const;
    bool empty() const;
    int  size() const; 
    friend class System;
private:
    std::vector<T> data;
    Comparator comp;

    int heapify(int index); //make heapify return the final index in the array 
};

#endif // TIME_TRAVELLING_FILE_SYSTEM_HEAP_H
#include "Heap_definition.tpp"
