
**Action** `FLIP`

The vehicle performs a flip in a certain direction (to the front, to the back, to the right or to the left). The direction by default is to the front.

| Arguments    |   Format  |  Example | 
| :-----------| :---------| :--------|
| direction |{front, back, left, right}|`<argument name=”direction” value=”back”/>`|
	

**Action** `GO_TO_POINT`

The vehicle goes to a given point. The point can be expressed using absolute coordinates (argument “coordinates”) or coordinates relative to the vehicle (argument “relative coordinates”).

| Arguments    |   Format  |  Example |  Comments | 
| :-----------| :---------| :--------|:--------|
| coordinates |Tuple of 3 numbers x, y, z (meters)|`<argument name=”coordinates” value=”(1.23, 2, 0.5)”/>`||			
| relative coordinates |Tuple of 3 numbers x, y, z (meters)|`<argument name=”relative coordinates” value=”(1.23, 2, 0.5)”/>`|Not implemented yet|				 

**Action** `LAND`

The vehicle descends vertically (through the z axis) until it touches the ground. It is assumed that the ground is static.

**Action** `MEMORIZE_POINT`

The vehicle memorizes the coordinates of the current point and assigns a label. The coordinates are absolute respects to the frame of reference.

| Arguments    |   Format  |  Example | 
| :-----------| :---------| :--------|
| coordinates |Tuple of 3 numbers x, y, z (meters)|`<argument name=”coordinates” label=”point A”/>`|

**Action** `MOVE`

The vehicle moves in a certain direction (forward, backward, right, left) a given number of meters.

| Arguments    |   Format  |  Example |  Comments | 
| :-----------| :---------| :--------|:--------|
| direction |{forward, backward, right, left}|`<argument name=”direction” value=”left”/>`|Not implemented yet|
| distance|Number (meters)|`<argument name=”distance” value=”0.5”/>`|Not implemented yet|			

**Action** `ROTATE_YAW`

The vehicle rotates an angle in a the yaw axe. The specified angle can be relative (rotation angle) or absolute respect to a frame of reference (orientation angle).

| Arguments    |   Format  |  Example |  Comments | 
| :-----------| :---------| :--------|:--------|
| rotation angle |Number (degrees)|`<argument name=”rotation angle” value=”90”/>`|Not implemented yet|
| orientation angle |Number (degrees)|`<argument name=”orientation angle” value=”90”/>`||

**Action** `STABILIZE`

The vehicle stops completely in the air, cancelling all the movements, perturbations and turbulences that may affect its position.

**Action** `TAKE_OFF`

The vehicle takes off from its current location to the default altitude.

**Action** `WAIT`

The vehicle waits on the air for a specified number of seconds.

| Arguments    |   Format  |  Example | 
| :-----------| :---------| :--------|
| duration|{Number (seconds)|`<argument name=”duration” value=”2.5”/>`|
