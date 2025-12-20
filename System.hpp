#ifndef TIME_TRAVELLING_FILE_SYSTEM_SYSTEM_H
#define TIME_TRAVELLING_FILE_SYSTEM_SYSTEM_H

// -----------------------------------------------------------------------------
// Project:   [Time-Travelling File System]
// Module:    [System]
// Author:    [Arittra Malhotra]
// Purpose:   [ two trees of the files]
// -----------------------------------------------------------------------------

#pragma once   

// -------------------------------
// Includes (only what’s needed)
// -------------------------------
#include <string>
#include <iostream>

#include"Map.hpp"
#include"Heap.hpp"
#include"Version.hpp"
#include"File.hpp"
#include"types.hpp"


// -------------------------------
// Class Declaration
// -------------------------------
class System {
private:
    HashMap<File> file_system;

    // struct big_tree {
    //     std::string file_name; 
    //     int size;   
    // };
    // struct recent_file {
    //     std::string file_name; 
    //     time_t modif_time;   
    // };
    Heap<big_tree,CompareBigTree> heap_biggestTrees;//whenever new file push it here
    Heap<recent_file,CompareRecentFile> heap_recentFiles;//whenever new version push it here
    friend class TreeNode;
    friend class File;


public:
    System();                // Constructor
    ~System();               // Destructor

    bool create(std::string name);  // constructorr
    std::string read(std::string name);
    bool insert(std::string name , std::string content);
    bool update(std::string name , std::string content);
    bool snapshot(std::string name , std::string message);
    bool rollback(std::string name , int version_id);
    std::vector<return_snapshot> history(std::string name);
    bool rollback(std::string name);
    std::vector<recent_file> recentFiles(int num);
    std::vector<big_tree> biggestTrees(int num);
    
};


#endif // TIME_TRAVELLING_FILE_SYSTEM_SYSTEM_H
#include "System_definition.tpp"
