#ifndef DRONELOGGERROSTOPICSUBSCRIBER_H
#define DRONELOGGERROSTOPICSUBSCRIBER_H

#include <ros/ros.h>
#include <string>
#include "debugstringstacker.h"

template<class T>
class DroneLoggerROSTopicSubscriber {
private:
    ros::Time init_rostime;
    ros::Subscriber topic_subscriber;
    void topicSubsCallback(const T &msg);
    DebugStringStacker debug_string_stacker;
    std::string (*p_rosmsg2string_f)(const T &msg);
    std::string tag_name;
public:
    DroneLoggerROSTopicSubscriber(const ros::NodeHandle &n, std::string tag_name_in, const std::string topic_name, std::string (*p_rosmsg2string_f_in)(const T &msg), ros::Time init_rostime_in, int stringStacker_Channel = 0, int subscriber_queue_length = 30);
    ~DroneLoggerROSTopicSubscriber();
};

template<class T>
DroneLoggerROSTopicSubscriber<T>::DroneLoggerROSTopicSubscriber(const ros::NodeHandle &nIn, std::string tag_name_in, const std::string topic_name, std::string (*p_rosmsg2string_f_in)(const T &msg), ros::Time init_rostime_in, int stringStacker_Channel, int subscriber_queue_length) :
    debug_string_stacker(stringStacker_Channel)
{
    init_rostime = init_rostime_in;
    ros::NodeHandle n = nIn;
    tag_name = tag_name_in;
    p_rosmsg2string_f = p_rosmsg2string_f_in;
    topic_subscriber = n.subscribe( topic_name, subscriber_queue_length, &DroneLoggerROSTopicSubscriber<T>::topicSubsCallback, this);
}

template<class T>
DroneLoggerROSTopicSubscriber<T>::~DroneLoggerROSTopicSubscriber() {
}

template<class T>
void DroneLoggerROSTopicSubscriber<T>::topicSubsCallback(const T &msg) {
    ros::Time run_timestamp = ros::Time::now();
    ros::Duration elapsed_rostime = run_timestamp - init_rostime;
    debug_string_stacker << elapsed_rostime.sec << "." << std::setfill('0') << std::setw(9) << elapsed_rostime.nsec;
    debug_string_stacker << " [" + tag_name + "] ";
    debug_string_stacker << (*p_rosmsg2string_f)(msg) << std::endl;
}



template<class T>
class DroneLoggerROSTopicSubscriber_MsgWithHeader {
private:
    ros::Time init_rostime;
    ros::Subscriber topic_subscriber;
    void topicSubsCallback(const T &msg);
    DebugStringStacker debug_string_stacker;
    std::string (*p_rosmsg2string_f)(const T &msg);
    std::string tag_name;
public:
    DroneLoggerROSTopicSubscriber_MsgWithHeader(const ros::NodeHandle &n, std::string tag_name_in, const std::string topic_name, std::string (*p_rosmsg2string_f_in)(const T &msg), ros::Time init_rostime_in, int stringStacker_Channel = 0, int subscriber_queue_length = 3);
    ~DroneLoggerROSTopicSubscriber_MsgWithHeader();
};

template<class T>
DroneLoggerROSTopicSubscriber_MsgWithHeader<T>::DroneLoggerROSTopicSubscriber_MsgWithHeader(const ros::NodeHandle &nIn, std::string tag_name_in, const std::string topic_name, std::string (*p_rosmsg2string_f_in)(const T &msg), ros::Time init_rostime_in, int stringStacker_Channel, int subscriber_queue_length) :
    debug_string_stacker(stringStacker_Channel)
{
    init_rostime = init_rostime_in;
    ros::NodeHandle n = nIn;
    tag_name = tag_name_in;
    p_rosmsg2string_f = p_rosmsg2string_f_in;
    topic_subscriber = n.subscribe( topic_name, subscriber_queue_length, &DroneLoggerROSTopicSubscriber_MsgWithHeader<T>::topicSubsCallback, this);
}

template<class T>
DroneLoggerROSTopicSubscriber_MsgWithHeader<T>::~DroneLoggerROSTopicSubscriber_MsgWithHeader() {
}

template<class T>
void DroneLoggerROSTopicSubscriber_MsgWithHeader<T>::topicSubsCallback(const T &msg) {
    static long last_image_sequence_number = -1;
    if ( last_image_sequence_number == msg->header.seq )
        return;
    else
        last_image_sequence_number = msg->header.seq;

    ros::Time run_timestamp = ros::Time::now();
    ros::Duration elapsed_rostime = run_timestamp - init_rostime;
    debug_string_stacker << elapsed_rostime.sec << "." << std::setfill('0') << std::setw(9) << elapsed_rostime.nsec;
    debug_string_stacker << " [" + tag_name + "] ";
    debug_string_stacker << (*p_rosmsg2string_f)(msg) << std::endl;
}


#endif // DRONELOGGERROSTOPICSUBSCRIBER_H
