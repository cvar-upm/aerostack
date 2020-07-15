#time
Header header


#HL command
int32 command 

# Drone State Command names declaration:
#  [*] To avoid problems make sure that the corresponding enum<->int values
#  are the same as in lib_cvgutils/src/include/drone_utils/drone_state_command_enum.h

int32 IDLE           = 0    # added, initialization value of DroneStateCommand in MAVwork... [unused in recovered code]
int32 TAKE_OFF       = 1
int32 HOVER          = 2
int32 LAND           = 3
int32 MOVE           = 4
int32 RESET          = 5    # same as EMERGENCY_STOP in MAVwork, thus...
int32 EMERGENCY_STOP = 5
int32 INIT           = 6    # added, initialization value of DroneStateCommand in MAVwork...

int32 UNKNOWN=1000
