#include "System.hpp"


System::System(){
    //lessgo!
}

System::~System(){}

std::vector<big_tree> System::biggestTrees(int num) {
    std::vector<big_tree> ans;

    while (ans.size() < (long long unsigned int)num && !heap_biggestTrees.empty()) {
        big_tree top = heap_biggestTrees.top();
        heap_biggestTrees.pop();

        File& f = file_system.get(top.file_name);

        // validate: only accept if the current file state matches
        if (f.total_versions == top.size) {
            // prevent duplicates in ans
            bool duplicate = false;
            for (auto &entry : ans) {
                if (entry.file_name == top.file_name) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                ans.push_back(big_tree{top.file_name, f.total_versions});
            }
        }
    }

    // push back valid entries into the heap
    for (auto &entry : ans) {
        heap_biggestTrees.push(big_tree{entry.file_name, entry.size});
    }

    return ans;
}

std::vector<recent_file> System::recentFiles(int num) {
    std::vector<recent_file> ans;

    while (ans.size() < (long long unsigned int)num && !heap_recentFiles.empty()) {
        recent_file top = heap_recentFiles.top();
        heap_recentFiles.pop();

        File& f = file_system.get(top.file_name);

        // validate: only accept if the current file state matches
        if (f.modified_time == top.modif_time) {
            // prevent duplicates in ans
            bool duplicate = false;
            for (auto &entry : ans) {
                if (entry.file_name == top.file_name) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                ans.push_back(recent_file{top.file_name, f.modified_time});
            }
        }
    }

    // push back valid entries into the heap
    for (auto &entry : ans) {
        heap_recentFiles.push(recent_file{entry.file_name, entry.modif_time});
    }

    return ans;
}



bool System::create(std::string name){
     if(file_system.contains(name)) {
        std::cout << "Error: File '" << name << "' already exists.\n";
        return false;
    }
    File newfile;
    bool flag = newfile.create(name);
    file_system.insert(name ,newfile);

    File& stored = file_system.get(name);   // <-- REFERENCE to stored object
    heap_biggestTrees.push(big_tree{name , stored.total_versions});
    heap_recentFiles.push(recent_file{name , stored.modified_time});

    return flag;
}  // constructorr

std::string System::read(std::string name){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return "";
    }
    File& f = file_system.get(name);   // <-- REFERENCE (avoid accidental copy)
    return f.read();
}

bool System::insert(std::string name , std::string content){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return false;
    }
    File& f = file_system.get(name);   // <-- REFERENCE (was using returned value implicitly)
    bool flag = f.insert(content);
    heap_biggestTrees.push(big_tree{name , f.total_versions});
    heap_recentFiles.push(recent_file{name , f.modified_time});
    return flag;
}

bool System::update(std::string name , std::string content){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return false;
    }
    File& f = file_system.get(name);   // <-- REFERENCE
    bool flag = f.update(content);
    heap_biggestTrees.push(big_tree{name , f.total_versions});
    heap_recentFiles.push(recent_file{name , f.modified_time});
    return flag;
}

bool System::snapshot(std::string name , std::string message){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return false;
    }
    File& f = file_system.get(name);   // <-- REFERENCE
    bool flag = f.snapshot(message);
    // keep heaps in sync after snapshot
    heap_biggestTrees.push(big_tree{name , f.total_versions});
    heap_recentFiles.push(recent_file{name , f.modified_time});
    return flag;
}

bool System::rollback(std::string name , int version_id){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return false;
    }
    File& f = file_system.get(name);   // <-- REFERENCE
    bool flag = f.rollback(version_id);
    // keep heaps in sync after rollback
    heap_biggestTrees.push(big_tree{name , f.total_versions});
    heap_recentFiles.push(recent_file{name , f.modified_time});
    if(!flag) std::cout << "Error: Version " << version_id << " not found for file '" << name << "'.\n";
    return flag;
}

std::vector<return_snapshot> System::history(std::string name){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return {};
    }
    File& f = file_system.get(name);   // <-- REFERENCE
    return f.history();
}

bool System::rollback(std::string name){
    if(!file_system.contains(name)){
        std::cout << "Error: File '" << name << "' not found.\n";
        return false;
    }
    File& f = file_system.get(name);   // <-- REFERENCE
    bool flag = f.rollback();
    // keep heaps in sync after rollback
    heap_biggestTrees.push(big_tree{name , f.total_versions});
    heap_recentFiles.push(recent_file{name , f.modified_time});
    if(!flag) std::cout << "Error: Cannot rollback from root version.\n";

    return flag;
}



    // bool create(std::string name);  // constructorr
    // std::string read() const;
    // bool insert(std::string content);
    // bool update(std::string content);
    // bool snapshot(std::string message);
    // bool rollback(int version_id);
    // std::vector<return_snapshot> history();
    // bool rollback();
