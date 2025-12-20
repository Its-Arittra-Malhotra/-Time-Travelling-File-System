#ifndef TIME_TRAVELLING_FILE_SYSTEM_VERSION_H
#define TIME_TRAVELLING_FILE_SYSTEM_VERSION_H

// -----------------------------------------------------------------------------
// Project:   [Time-Travelling File System]
// Module:    [Version]
// Author:    [Arittra Malhotra]
// Purpose:   [Version of a file]
// -----------------------------------------------------------------------------

#pragma once   

// -------------------------------
// Includes (only what’s needed)
// -------------------------------
#include <string>
#include<ctime>
#include<vector>


// -------------------------------
// Class Declaration
// -------------------------------
class TreeNode {
public:
    TreeNode(){}               // Constructor
    ~TreeNode(){}
    
private:
    int version_id;
    std::string content = "";
    std::string message = "";  //message for snapshot;null otherwise
    time_t created_timestamp;
    time_t snapshot_timestamp = 0; // null if not a snapshot
    TreeNode* parent;
    std::vector<TreeNode*> children;
    friend class File;
};


#endif // TIME_TRAVELLING_FILE_SYSTEM_VERSION_H
