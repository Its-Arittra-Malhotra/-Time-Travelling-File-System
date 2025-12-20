#ifndef TIME_TRAVELLING_FILE_SYSTEM_FILE_H
#define TIME_TRAVELLING_FILE_SYSTEM_FILE_H

// -----------------------------------------------------------------------------
// Project:   [Time-Travelling File System]
// Module:    [File]
// Author:    [Arittra Malhotra]
// Purpose:   [File object , with its functions]
// -----------------------------------------------------------------------------

#pragma once   

// -------------------------------
// Includes (only what’s needed)
// -------------------------------
#include <string>
#include <vector>
#include"Map.hpp"
#include"Heap.hpp"
#include"Version.hpp"
#include"types.hpp"

// -------------------------------
// Class Declaration
// -------------------------------
class File {
private:
    std::string file_name;
    TreeNode* root;
    TreeNode* active_version;
    int total_versions;
    //map<int,TreeNode*>version_map;
    std::vector<TreeNode*> version_map;
    // struct return_snapshot {
    //     int id;                // unique version ID
    //     time_t timestamp; // formatted time string
    //     std::string message;   // commit / snapshot message
    // };
    time_t modified_time;

    friend class TreeNode;
    friend class System;
public:
    File();                // Constructor
    ~File();               // Destructor

    bool create(std::string name);  // constructorr
    std::string read();
    bool insert(std::string content);
    bool update(std::string content);
    bool snapshot(std::string message);
    bool rollback(int version_id);
    std::vector<return_snapshot> history();
    bool rollback();

};


#endif // TIME_TRAVELLING_FILE_SYSTEM_FILE_H
#include "File_definition.tpp"
