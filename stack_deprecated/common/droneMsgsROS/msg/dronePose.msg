#Header
Header header

#time stamp
float64 time

# position of the target_frame
float32 x
float32 y
float32 z

#attitude of the target_frame
float32 yaw
float32 pitch
float32 roll 



# YPR_system:
#  [*] wYvPuR
#  [*] xYyPzR
#  [*] note that: wYvPuR equals to xRyPzY
#  [*] note that: xYyPzR equals to wRvPuY
# This is, homogeneous transformation of the target_frame with respect to the reference_frame
string YPR_system
string target_frame
string reference_frame
