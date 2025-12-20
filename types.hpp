#ifndef TIME_TRAVELLING_FILE_SYSTEM_TYPES_H
#define TIME_TRAVELLING_FILE_SYSTEM_TYPES_H

#include <string>
#include <ctime>

struct big_tree {
    std::string file_name;
    int size;
};

struct recent_file {
    std::string file_name;
    time_t modif_time;
};

struct return_snapshot {
    int id;
    time_t timestamp;
    std::string message;
};

#endif
