#time
time time

#ack
bool ack

#MissionPlanner action
int32 mpAction

int32 TAKE_OFF                   = 1
int32 HOVER                      = 2
int32 LAND                       = 3
int32 STABILIZE                  = 4
int32 MOVE                       = 5
int32 GO_TO_POINT                = 6
int32 ROTATE_YAW                 = 7
int32 FLIP                       = 8
int32 FLIP_RIGHT                 = 9
int32 FLIP_LEFT                  = 10
int32 FLIP_FRONT                 = 11
int32 FLIP_BACK                  = 12
int32 FOLLOW_IMAGE               = 13
int32 APPROACH_POINT             = 14

int32 UNKNOWN                    = 100

#Arguments
actionArguments[] arguments