#include "dronelogfileswritter.h"

DroneLogfilesWritter::DroneLogfilesWritter(std::string stackPath)
    {
    // creating events_logfile and fligth_diary_logfile
    std::stringstream s0, s1, s2, s3, s4, s5, s6, s7, msg;
    s0 << stackPath << "logs/drone_logger";
    // getting unique folder names, examples:
    //   date_y2014m03d21
    //   time_11:35:47.428712
    time_t rawtime;
    struct tm * timeinfo;
    char date_buffer [30];
    char time_buffer [30];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime ( date_buffer, 30, "date_y%Ym%md%d", timeinfo);
    strftime ( time_buffer, 30, "time_h%Hm%Ms%S", timeinfo);
//    std::cout << date_buffer << std::endl;
//    std::cout << time_buffer << std::endl;
    s1 << s0.str() << "/" << date_buffer;
    s2 << s1.str() << "/" << time_buffer;
    s3 << s2.str() << "/frontImage";
    s4 << s2.str() << "/bottomImage";
    s5 << s2.str() << "/leftImage";
    s6 << s2.str() << "/backImage";
    s7 << s2.str() << "/rightImage";

    std::string logs_path; logs_path = std::string(s0.str());
//    std::cout << "is_directory " << logs_path   << ": " << cvg_is_directory(logs_path) << std::endl;
    if ( !(cvg_is_directory(logs_path)) ) {
        cvg_create_directory(logs_path);
    }

    std::string daylogs_path = std::string(s1.str());
//    std::cout << "is_directory " << daylogs_path << ": " << cvg_is_directory(daylogs_path) << std::endl;
    if ( !(cvg_is_directory(daylogs_path)) ) {
        cvg_create_directory(daylogs_path);
    }

    currentlog_path = std::string(s2.str());
//    std::cout << "is_directory " << currentlog_path << ": " << cvg_is_directory(currentlog_path) << std::endl;
    if ( !(cvg_is_directory(currentlog_path)) ) {
        cvg_create_directory(currentlog_path);
    }


    if ( !(cvg_is_directory(std::string(s3.str()))) )
    {
        cvg_create_directory(std::string(s3.str()));
    }

    if ( !(cvg_is_directory(std::string(s4.str()))) )
    {
        cvg_create_directory(std::string(s4.str()));
    }

    if ( !(cvg_is_directory(std::string(s5.str()))) )
    {
        cvg_create_directory(std::string(s5.str()));
    }

    if ( !(cvg_is_directory(std::string(s6.str()))) )
    {
        cvg_create_directory(std::string(s6.str()));
    }

    if ( !(cvg_is_directory(std::string(s7.str()))) )
    {
        cvg_create_directory(std::string(s7.str()));
    }

    eventslog_ofs.open( (currentlog_path + "/" + std::string("events_log.txt")).c_str() );

    flight_diary_ofs.open( (currentlog_path + "/" + std::string("flight_diary.txt")).c_str(), std::ofstream::out);
    flight_diary_ofs << "Start time: " << time_buffer
                     << " of"
                     << date_buffer
                     << std::endl;
    return;
}

DroneLogfilesWritter::~DroneLogfilesWritter() {
    // Note: for the buffer to be emptied into the logfile, the program must be closed with control+c
    eventslog_ofs.close();
    flight_diary_ofs.close();
}

void DroneLogfilesWritter::writeString2Logfile(std::string string_in) {
    eventslog_ofs << string_in;
}
