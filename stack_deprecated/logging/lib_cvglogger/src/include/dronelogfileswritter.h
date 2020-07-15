#ifndef DRONELOGFILESWRITTER_H
#define DRONELOGFILESWRITTER_H

#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <fstream>

// Class Description:
//  - This class creates two files, events_log.txt and flight_diary.txt.
//  - The idea is to encapsulate I/O for the DroneLoggerROSModule class and node
//  - The class automatically creates two folders <date>/<time_of_day> inside ${DRONE_STACK}/logs/drone_logger

#include <sys/stat.h>

inline bool cvg_is_directory( std::string directory_path) { struct stat st; return (stat(directory_path.c_str(),&st) == 0); }
inline bool cvg_create_directory( std::string directory_path) { return mkdir( directory_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); }

class DroneLogfilesWritter {
private:
    std::string currentlog_path;
    std::ofstream eventslog_ofs;
    std::ofstream flight_diary_ofs;

public:
    DroneLogfilesWritter(std::string stackPath);
    ~DroneLogfilesWritter();
    void writeString2Logfile(std::string string_in);

    inline std::string getCurrentLogPath() { return currentlog_path; }
};

#endif // DRONELOGFILESWRITTER_H
