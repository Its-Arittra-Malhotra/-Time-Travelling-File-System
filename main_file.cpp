#include <string>
#include <iostream>
#include <sstream>


#include "Version.hpp"
#include "File.hpp"
#include "System.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(&std::cout); // tie back cin to cout

    System FileSystem;
    std::cout << "Time-Travel File System Ready. Enter commands:\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "CREATE") {
            std::string filename;
            if (!(ss >> filename)) { std::cerr << "Error: Missing filename\n"; continue; }
            bool flag = FileSystem.create(filename);
            if(flag == true) std::cout<<"File Created!\n" ;

        } else if (command == "READ") {
            std::string filename;
            if (!(ss >> filename)) { std::cerr << "Error: Missing filename\n"; continue; }
            std::string red = FileSystem.read(filename);
            std::cout << red;

        } else if (command == "INSERT") {
            std::string filename; ss >> filename;
            std::string content; std::getline(ss, content);
            if (filename.empty() || content.empty()) { std::cerr << "Error: INSERT <filename> <content>\n"; continue; }
            bool flag = FileSystem.insert(filename, content.substr(1));
            if(flag == true) std::cout<<"Successful\n" ;


        } else if (command == "UPDATE") {
            std::string filename; ss >> filename;
            std::string content; std::getline(ss, content);
            if (filename.empty() || content.empty()) { std::cerr << "Error: UPDATE <filename> <content>\n"; continue; }
            bool flag = FileSystem.update(filename, content.substr(1));
            if(flag == true) std::cout<<"Successful\n" ;


        } else if (command == "SNAPSHOT") {
            std::string filename; ss >> filename;
            std::string message; std::getline(ss, message);
            if (filename.empty() || message.empty()) { std::cerr << "Error: SNAPSHOT <filename> <message>\n"; continue; }
            bool flag = FileSystem.snapshot(filename, message.substr(1));
            if(flag == true) std::cout<<"Successful\n" ;

        } else if (command == "ROLLBACK") {
            std::string filename; ss >> filename;
            if (filename.empty()) { std::cerr << "Error: ROLLBACK <filename> [versionID]\n"; continue; }
            int versionId;
            bool flag;
            if (ss >> versionId) flag = FileSystem.rollback(filename, versionId);
            else flag = FileSystem.rollback(filename);
            if(flag == true) std::cout<<"Successful\n" ;


        } else if (command == "HISTORY") {
            std::string filename;
            if (!(ss >> filename)) { std::cerr << "Error: Missing filename\n"; continue; }
            std::vector<return_snapshot> ans = FileSystem.history(filename);
            for (auto elem : ans) {
                char* dt = ctime(&elem.timestamp);       // convert to string

                std::cout<<elem.id<< " snapshot timestamp " << dt  << "snapshot message :"<< elem.message <<"\n";
            }
        } else if (command == "RECENT") {
            std::string subcmd; ss >> subcmd;
            if (subcmd != "FILES") { std::cerr << "Error: RECENT FILES <num>\n"; continue; }
            int num; if (!(ss >> num)) { std::cerr << "Error: Missing number\n"; continue; }
            std::vector<recent_file> ans = FileSystem.recentFiles(num);
            for (auto elem : ans) {
                char* dt = ctime(&elem.modif_time);       // convert to string

                std::cout<<elem.file_name << "  last modified at " << dt  << "\n";
            }

        } else if (command == "BIGGEST") {
            std::string subcmd; ss >> subcmd;
            if (subcmd != "TREES") { std::cerr << "Error: BIGGEST TREES <num>\n"; continue; }
            int num; if (!(ss >> num)) { std::cerr << "Error: Missing number\n"; continue; }
            std::vector<big_tree> ans = FileSystem.biggestTrees(num);
            for (auto elem : ans) {
                std::cout<<elem.file_name << "  " << elem.size << " versions\n";
            }

        } else if (command == "EXIT") {
            std::cout << "Exiting system.\n";
            break;

        } else {
            std::cerr << "Error: Unknown command \"" << command << "\"\n";
        }
    }

    return 0;
}
