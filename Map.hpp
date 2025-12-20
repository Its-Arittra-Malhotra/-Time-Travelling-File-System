#ifndef TIME_TRAVELLING_FILE_SYSTEM_MAP_H
#define TIME_TRAVELLING_FILE_SYSTEM_MAP_H

// -----------------------------------------------------------------------------
// Project:   [Time-Travelling File System]
// Module:    [Hash - Map]
// Author:    [Arittra Malhotra]
// Purpose:   [Hash map complete -- includes linked list for each bucket,
//             hash function, bucket array/hash table, insert and get functions]
// -----------------------------------------------------------------------------

#pragma once   // optional, supported by most modern compilers

// -------------------------------
// Includes (only what’s needed)
// -------------------------------
#include <string>
#include <vector>
#include <stdexcept>

// -------------------------------
// Constants / Macros
// -------------------------------
const int TABLE_SIZE = 10007;

// -------------------------------
// Class Declarations
// -------------------------------
template <typename T>
struct ListNode {
    std::string key;
    T value;
    ListNode* next = nullptr;
};

template <typename T>
class LinkedList {
private:
    ListNode<T>* root;
public:
    LinkedList();
    ~LinkedList();
    void push(const std::string& key, const T& value);
    T& get(const std::string& key);
    const T& get(const std::string& key) const;

    bool contains(const std::string& key) const;
};

template <typename T>
class HashMap {
private:
    std::vector<LinkedList<T>> hash_table;
public:
    HashMap();
    ~HashMap();
    unsigned int hash_function(const std::string& key) const;
            // int hash = 5381;
            // for (char c : key) {
            //     hash = ((hash << 5) + hash) + c; 
            // }
            // return hash % tableSize;
    bool insert(const std::string& key, const T& value);
    T& get(const std::string& key);
    const T& get(const std::string& key) const;

    bool contains(const std::string& key) const;
};

#endif // TIME_TRAVELLING_FILE_SYSTEM_MAP_H

#include "Map_definition.tpp"
