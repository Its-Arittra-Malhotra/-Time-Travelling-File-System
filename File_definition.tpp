#include "File.hpp"

File::File(){}               // Constructhor
File::~File(){}               // Destructhor

bool File::create(std::string name){
    file_name = name;
    root = new TreeNode;
    root->version_id = 0;
    root->created_timestamp = time(nullptr);
    root->snapshot_timestamp = root->created_timestamp;
    root->content = "EMPTY";
    root->message = "";
    root->parent = nullptr;
    version_map.push_back(root);

    active_version = root;
    modified_time = root->created_timestamp;

    total_versions = 1;
    return true;
}  // constructorr

std::string File::read(){
    return active_version->content;
} 
bool File::insert(std::string add_content){
    if(active_version->snapshot_timestamp == 0){
        active_version->content.append(add_content);
        modified_time = time(nullptr);
        return true;
    }
    else{
        total_versions ++;
        TreeNode* child = new TreeNode;
        child->content = add_content;
        child->created_timestamp = time(nullptr);
        child->parent =active_version;
        child->version_id = total_versions-1;
        active_version->children.push_back(child);
        active_version = child; 
        modified_time = child->created_timestamp;
        version_map.push_back(child);
        return true;
    }
    return false;
}
bool File::update(std::string upd_content){
    if(active_version->snapshot_timestamp == 0){
        active_version->content = upd_content ;
        modified_time = time(nullptr);
        return true;
    }
    else{
        total_versions ++;
        TreeNode* child = new TreeNode;
        child->content = upd_content;
        child->created_timestamp = time(nullptr);
        child->parent =active_version;
        child->version_id = total_versions-1;
        active_version->children.push_back(child);
        active_version = child; 
        modified_time = child->created_timestamp;
        version_map.push_back(child);
        return true;

    }
}
bool File::snapshot(std::string message){
    active_version->snapshot_timestamp = time(nullptr);
    active_version->message = message;
    return true;
}
bool File::rollback(){
    if(active_version->version_id == 0){
        return false;
    }
    active_version = active_version->parent;
    return true;
}
bool File::rollback(int version_id){
    if(version_id < 0 || version_id >= total_versions) return false;
    active_version = version_map[version_id];
    return true;
}
std::vector<return_snapshot> File::history(){
    TreeNode* temp = active_version;
    std::vector<return_snapshot> ans;
    while(temp){
        if(temp->snapshot_timestamp != 0){
            ans.push_back(return_snapshot{temp->version_id,temp->snapshot_timestamp,temp->message});
        }
        temp = temp->parent;
    }
    return ans;
}




// string file_name;
//     TreeNode* root;
//     TreeNode* active_version;
//     int total_versions;
//     map<int,TreeNode*>version_map;
//     struct return_snapshot {
//         int id;                // unique version ID
//         time_t timestamp; // formatted time string
//         std::string message;   // commit / snapshot message
//      };
///////////////////////////////////////////////////////////
//     int version_id;
//     string content;
//     string message;  //message for snapshot;null otherwise
//     time_t created_timestamp;
//     time_t snapshot_timestamp; // null if not a snapshot
//     TreeNode* parent;
//     vector<TreeNode*> children;
//     friend class File;