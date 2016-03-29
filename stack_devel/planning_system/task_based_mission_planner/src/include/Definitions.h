/*!*****************************************************************************
 *  \file      definitions.h
 *  \brief     Allowed actions are defined in this file.  
 *  \author    Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *             Released under license BSD-3.
 ********************************************************************************/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
 
//Action Commands
#define CMD_TAKEOFF                         "TAKE_OFF"
#define CMD_HOVER                           "HOVER"
#define CMD_LAND                            "LAND"
#define CMD_STABILIZE                       "STABILIZE"
#define CMD_FLIP_RIGHT                      "FLIP_RIGHT"
#define CMD_FLIP_LEFT                       "FLIP_LEFT"
#define CMD_FLIP_FRONT                      "FLIP_FRONT"
#define CMD_FLIP_BACK                       "FLIP_BACK"
#define CMD_MOVEMENT_POSITION               "MOVE"
#define CMD_GO_TO_POINT                     "GO_TO_POINT"
#define CMD_ROTATE_YAW                      "ROTATE_YAW"
#define CMD_REMEMBER_POINT                  "REMEMBER_POINT"

//Action arguments name value
#define NAME_DESTINATION                    "point"
#define NAME_DURATION                       "duration"
#define NAME_ROTATION                       "angle"
#define NAME_POINT_NAME                     "point_name"

//Behavior command.
#define BHV_AVOIDING_OBSTACLES              "avoidingObstacles"
#define BHV_RECOGNIZING_ARUCO_MARKERS       "recognizingArucoMarkers"
#define BHV_RECOGNIZING_VISUAL_MARKERS      "recognizingVisualMarkers"
#define BHV_SAYING_OUT_LOUD_CURRENT_TASK    "sayingOutLoudCurrentTask"

//Ending Actions
#define END_REPEAT_TASK                     "REPEAT_TASK"
#define END_NEXT_TASK                       "NEXT_TASK"
#define END_ABORT_MISSION                   "ABORT_MISSION"

namespace missionSchedulerAction
{ 
  //Tasks types.
  enum taskActions
  {
  //Implemented actions.
  takeOff,       
  hover,      
  land,
  stabilize,
  positionMovement,
  goToPoint,
  rotateYaw,
  flipMovement,    
  flipMovementRight,    
  flipMovementLeft,    
  flipMovementFront,   
  flipMovementBack,
  rememberPoint,

  unknown
  };
}

namespace missionSchedulerBehavior
{
  //Behavior types.
  enum taskBehaviors
  {
  avoidingObstacles,
  recognizingArucoMarkers,
  recognizingVisualMarkers,
  sayingOutLoudCurrentTask
  };
}

namespace missionSchedulerEndingStep
{
  //Ending actions (Control actions). This set of actions is different from the previous.
  enum endingStep
  {
  repeatTask,
  nextTask,
  abortMission
  };
}

 /*!************************************************************************
 *  \struct point
 *  \brief  An abstraction of a tridimensional point.
 *************************************************************************/
struct point 
{
  //If z = 0 is set, then it will be considered as a bidimensional point. (Z=0 plane)
  float x; //!< The coordinate x
  float y; //!< The coordinate y
  float z; //!< The coordinate z
};

 /*!************************************************************************
 *  \struct action
 *  \brief  An abstraction of what an action is supossed to have
 *          (i.e. arguments and duration)
 *************************************************************************/
struct action
{
  missionSchedulerAction::taskActions name;
  std::vector<point> arguments;
  double duration;
};

 /*!************************************************************************
 *  \struct duo
 *  \brief  An abstract element of a custom key-value data structure.
 *************************************************************************/
template <typename A, typename B>
struct duo
{
  A key;
  B value;
};
#endif