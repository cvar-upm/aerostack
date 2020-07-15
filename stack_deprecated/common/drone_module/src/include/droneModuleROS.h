//////////////////////////////////////////////////////
//  droneModule.h
//
//  Created on: Jul 3, 2013
//      Author: joselusl
//
//  Last modification on: Oct 23, 2013
//      Author: joselusl
//
//////////////////////////////////////////////////////

#ifndef DRONE_MODULE_H
#define DRONE_MODULE_H




//I/O stream
//std::cout
#include <iostream>

//String
//std::string
#include <string>

//String stream
//std::ostringstream
#include <sstream>

//Thread
#include <pthread.h>



//ROS
#include "ros/ros.h"


//Services
#include "std_srvs/Empty.h"
//#include "droneModule/isStarted.h"


//Topics
#include "std_msgs/Bool.h"
#include <droneMsgsROS/AliveSignal.h>

namespace droneModule
{
    enum droneModuleTypes
    {
        active, //Writes
        monitor //Reads
    };
        typedef enum
    {
        FirstValue,
        Initializing,
        Running,
        Sleeping,
        Waiting,
        Stopping,
        Recovering,
        Started,
        NotStarted,
        LastValue
    } State;
//    enum droneModuleLoggerTypes
//    {
//        non_logger, // logs data
//        logger      // does not log data
//    };
}


/////////////////////////////////////////
// Class Module
//
//   Description
//
/////////////////////////////////////////
class Module
{
    //Ros node
protected:
    ros::NodeHandle n;

protected:
    std::string stackPath;



    //Module vars
protected:
    //module started
    bool moduleStarted;
    //module opened
    bool droneModuleOpened;


protected:
    //Type of module
    droneModule::droneModuleTypes droneModuleType;
    //Rate
    ros::Rate moduleRate;




    //Reset
public:
    bool reset();
private:
    std_srvs::Empty emptySrv;
    ros::ServiceServer resetServerSrv;
  //  ros::ServiceClient resetClientSrv;
    bool resetServCall(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);
protected:
    virtual bool resetValues();


    //Start
public:
    bool start();
private:
    //std_srvs::Empty emptySrv; //Compartido. Ya puesto antes
    bool startServCall(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);
    ros::ServiceServer startServerSrv;
   // ros::ServiceClient startClientSrv;
protected:
    virtual bool startVal();


    //Stop
public:
    bool stop();
private:
    //std_srvs::Empty emptySrv; //Compartido. Ya puesto antes
    bool stopServCall(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);
    ros::ServiceServer stopServerSrv;
  //  ros::ServiceClient stopClientSrv;
protected:
    virtual bool stopVal();


    //is Started
public:
    bool isStarted();
//private:
//    //bool isStartedServCall(droneModule::isStarted::Request& request, droneModule::isStarted::Response& response);
//    void isStartedSubCallback(const std_msgs::Bool::ConstPtr &msg);
//protected:
//    void isStartedPublish();
//    //Topics
//private:
//    std_msgs::Bool isStartedMsg;
//    ros::Publisher isStartedPub;
  //  ros::Subscriber isStartedSub;



public:
//    Module(droneModule::droneModuleTypes droneModuleTypeIn=droneModule::active, double moduleRateIn=0.0, droneModule::droneModuleLoggerTypes droneModuleLoggerTypesIn = droneModule::non_logger);
        Module(droneModule::droneModuleTypes droneModuleTypeIn=droneModule::active, double moduleRateIn=10.0);
    ~Module();

    virtual void open(ros::NodeHandle & nIn, std::string moduleName=""); //moduleName deprecated
    //virtual void open(ros::NodeHandle & nIn);

protected:
    void init();
    void close();


    //Run
public:
    virtual bool run();

    //Sleep
public:
    void sleep();
    inline void set_moduleRate(double moduleRateIn) { moduleRate = moduleRateIn; }

    //Thread
private:
  /*!******************************************************************************************************************
   * \brief This function has the only purpose to serve as the thread execution point.
   * \param [in] argument Function which has to be exacuted by the thread.
   *******************************************************************************************************************/
  static void * threadRun(void * argument);
  //!  This function implements the thread's logic.
  void threadAlgorithm();
  pthread_t t1; //!< Thread handler.
  ros::Publisher state_pub;
  std::string hostname; 
  droneMsgsROS::AliveSignal state_message; //!< Message of type state.
  
    // droneLogger
//protected:
    // pointer to logging function
//    droneModule::droneModuleLoggerTypes droneModuleLoggerType;
//    void (DroneLogger::*ploggingfunction)( const std::string &);
//    DroneLogger *pdronelogger;
//public:
//    inline void setLoggingFunction( void (DroneLogger::*ploggingfunctionIn)( const std::string &) ) { ploggingfunction = ploggingfunctionIn; }
//    inline void setDroneLogger( DroneLogger *pdroneloggerIn ) { pdronelogger = pdroneloggerIn; }



};



/////////////////////////////////////////
// Class DroneModule
//
//   Description
//
/////////////////////////////////////////
class DroneModule : public Module
{	


protected:
    int idDrone;
    std::string stringId;






public:

    //DroneModule(droneModule::droneModuleTypes droneModuleTypeIn=droneModule::active, double moduleRateIn=0.0, droneModule::droneModuleLoggerTypes droneModuleLoggerTypesIn = droneModule::non_logger);
    DroneModule(droneModule::droneModuleTypes droneModuleTypeIn=droneModule::active, double moduleRateIn=10.0);
    ~DroneModule();


    void open(ros::NodeHandle & nIn, std::string moduleName="");
    //void open(ros::NodeHandle & nIn);

    std::string getStringId() {return stringId;}
    int getId() {return idDrone;}

};
        
        
        
 

#endif /* DRONE_MODULE_H_ */
