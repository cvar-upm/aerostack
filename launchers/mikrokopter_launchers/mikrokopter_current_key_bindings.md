// Current key bindings:
// case 't': // take off: take off
// case 'y': // land: hover > land > stop controller
// case ' ': // emergency stop: emergency stop > stop controller
// case 'h': // hover: hover > stop controller
// case 'm': // move: move (set flying mode)
// case 's': // set commands to zero: [open loop] hover, [closed loop] (non internal - with controller) hover
// case 'q': // move upwards: [open loop] upwards speed command; [speed, position control] move altitude reference upwards
// case 'a': // move downwards: same as before but downwards
// case 'z': // (yaw) turn counter-clockwise: [open loop] turn with speed command; [any controller] move yaw reference counter-clockwise
// case 'x': // (yaw) turn clockwise: same as before but clockwise
// case '\'': // set yaw reference to 0 (look parallel to x-axis)
// case ASCII_KEY_RIGHT: // move right, or to[+]y_axis: [open loop] or [speed command] or [position command], ignored during trayectory control
// case ASCII_KEY_LEFT:  // move left: [open loop] or [speed command] or [position command], ignored during trayectory control
// case ASCII_KEY_DOWN:  // move backwards: [open loop] or [speed command] or [position command], ignored during trayectory control
// case ASCII_KEY_UP:    // move frontwards; [open loop] or [speed command] or [position command], ignored during trayectory control
// case 'j': { // reset EKF: stop controller > reset EKF
// case 'k': { // stop  EKF: stop controller > stop EKF
// case 'l': { // start EKF: start EKF and setInitDroneYaw
// case 'u': { // reset controller
// case 'i': { // stop  controller: stop controller > drone_hover
// case 'o': { // start controller: start EKF > start controller
// case '7': { // start speed controller: if controller started > drone_move > start controller (speed)
// case '8': { // start position controller: if controller started > drone_move > start controller (position)
// case '9': { // start trajectory controller (3D quadrilateral) using rel_trajectory_ref channel

