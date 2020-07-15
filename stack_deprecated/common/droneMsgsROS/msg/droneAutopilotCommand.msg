# Command sent to the drone's Autopilot usually in "Free" internal flying mode, thus: 
#   thrust, dyaw, pitch, roll

#header
Header header

# Units: deg
float32 pitch
# Units: deg
float32 roll
# Units: deg/s
float32 dyaw
# Units: N
float32 thrust
