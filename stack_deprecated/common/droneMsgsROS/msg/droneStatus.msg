#Header
Header header


#Status of the drone
int32 status

# Drone State names declaration
#  [*] To avoid problems make sure that the corresponding enum<->int values
#  are the same as in lib_cvgutils/src/include/drone_utils/drone_state_enum.h
#  [*] Important, drone_state_enum is defined to have the same enum<->int value
#  correspondance as the ardrone (when using the ardrone_autonomy).

#Predefined status
int32 UNKNOWN          = 0  # Emergency mode in parrot, Unknown for other quads
int32 INITED           = 1
int32 LANDED           = 2
int32 FLYING           = 3
int32 HOVERING         = 4
# int32 TEST           = 5
int32 TAKING_OFF       = 6
# int32 GOTO_FIX_POINT = 7
int32 LANDING          = 8
int32 LOOPING          = 9  # Only used with the parrot
int32 EMERGENCY        = 0  # Emergency mode for other quads

