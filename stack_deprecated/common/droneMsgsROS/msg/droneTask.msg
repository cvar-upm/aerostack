#Task struct 

int32 time


int32 mpCommand 

int32 TAKE_OFF                   = 1
int32 HOVER                      = 2
int32 LAND                       = 3
int32 START_CONTROLLER           = 4
int32 SLEEP                      = 5
int32 ABORT_LANDING_AND_TAKE_OFF = 6
int32 MOVE_MANUAL_ALTITUD        = 7
int32 MOVE_MANUAL_THRUST         = 8
int32 MOVE_POSITION              = 9
int32 MOVE_SPEED                 = 10
int32 MOVE_TRAJECTORY            = 11
int32 MOVE_VISUAL_SERVOING       = 12
int32 HOVERING_VISUAL_SERVOING   = 13
int32 EMERGENCY                  = 14
int32 MOVE_FLIP                  = 15
int32 MOVE_FLIP_RIGHT            = 16
int32 MOVE_FLIP_LEFT             = 17
int32 MOVE_FLIP_FRONT            = 18
int32 MOVE_FLIP_BACK             = 19
int32 MOVE_EMERGENCY             = 20
int32 LAND_AUTONOMOUS            = 21
int32 MOVE_VISUAL_SERVOING_RL    = 22
int32 UNKNOWN                    = 100

float32 yaw

string speech_name

#This Modules are going to be sent by the Mission Planner or HMI
#to the ManagerOfActions for activating some optional modules
string[] module_names

#Used for Moving Tasks
vector3f point

vector3f pointToLook

int32 yawSelector
#yawSelector == 0 means no Yaw nor PointToLook
#yawSelector == 1 means MOVE in YAW
#yawSelector == 2 means MOVE with PointToLook

