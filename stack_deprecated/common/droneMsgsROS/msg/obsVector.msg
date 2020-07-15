#time stamp
float64 time

#vector of landmarks
Observation3D[] obs

# YPR_system:
#  [*] wYvPuR
#  [*] xYyPzR
#  [*] note that: wYvPuR equals to xRyPzY
#  [*] note that: xYyPzR equals to wRvPuY
# This is, homogeneous transformation of the target_frame with respect to the reference_frame
string YPR_system
string target_frame
string reference_frame

