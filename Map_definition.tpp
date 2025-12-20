#include "Map.hpp"

// -------------------------------
// LinkedList Definitions
// -------------------------------
template <typename T>
LinkedList<T>::LinkedList() : root(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    ListNode<T>* curr = root;
    while (curr) {
        ListNode<T>* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::push(const std::string& key, const T& value) {
    ListNode<T>* newNode = new ListNode<T>{key, value, root};
    root = newNode;
}

template <typename T>
T& LinkedList<T>::get(const std::string& key) {
    ListNode<T>* curr = root;
    while (curr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    throw std::runtime_error("Key not found: " + key);
}

template <typename T>
const T& LinkedList<T>::get(const std::string& key) const {
    ListNode<T>* curr = root;
    while (curr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    throw std::runtime_error("Key not found: " + key);
}

template <typename T>
bool LinkedList<T>::contains(const std::string& key) const {
    ListNode<T>* curr = root;
    while (curr) {
        if (curr->key == key) return true;
        curr = curr->next;
    }
    return false;
}

// -------------------------------
// HashMap Definitions
// -------------------------------
template <typename T>
HashMap<T>::HashMap() : hash_table(TABLE_SIZE) {}

template <typename T>
HashMap<T>::~HashMap() {}

template <typename T>
unsigned int HashMap<T>::hash_function(const std::string& key) const {
    unsigned int hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return hash % TABLE_SIZE;
}

template <typename T>
bool HashMap<T>::insert(const std::string& key, const T& value) {
    unsigned int idx = hash_function(key);
    hash_table[idx].push(key, value);
    return true;
}

template <typename T>
T& HashMap<T>::get(const std::string& key) {
    unsigned int idx = hash_function(key);
    return hash_table[idx].get(key);
}

template <typename T>
const T& HashMap<T>::get(const std::string& key) const {
    unsigned int idx = hash_function(key);
    return hash_table[idx].get(key);
}

template <typename T>
bool HashMap<T>::contains(const std::string& key) const {
    unsigned int idx = hash_function(key);
    return hash_table[idx].contains(key);
}
