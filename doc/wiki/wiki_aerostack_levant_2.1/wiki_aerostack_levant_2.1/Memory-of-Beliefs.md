Aerostack uses a memory of symbolic beliefs to represent information about what the robot believes about the world. A belief is a proposition about the world that the robot thinks is true (the world here refers to both the external world and the internal state of the robot). 

Beliefs are useful to be used in the specification of mission plans. During the execution of a mission plan, the robot uses beliefs as true facts while it reasons trying to adapt the mission plan to the current circumstances. Beliefs can also be used by the operator to help monitor the correct execution of a mission.

Aerostack stores the set of beliefs and tries to keep their consistency with the world and with the other beliefs. Aerostack represents beliefs using a logic-based approach with predicates. Next table shows examples of such predicates with the general format of predicate(object, value) or simpler forms such as property(object). These predicates are always present in the memory with their corresponding values:

| Predicate    |  Description |   
| :-----------| :---------| 
| flight_state(self, x) |The flight state of the aerial robot is x (e.g., LANDED or FLYING) |
| position(self, x) |The aerial robot is at the spatial position x (in 3D coordinates). For example, x = (4.9, 5.1, 0).| 
| battery_level(self,x) |The level of the battery charge is x (e.g., HIGH or LOW)| 

The examples presented in the next table are for illustration purposes (i.e., not all of them they are not implemented in the current version of Aerostack):

| Predicate    |  Description |   
| :-----------| :---------| 			
| name(x, y) |The name of object x is y| 
| code(x, y) |The numerical code of x is y| 
| color(x, y)  |The color of x is y| 
| frequency(communication,x)  |The frequency of the communications is x| 
| carry(self, x) |The own aerial robot carries the object x| 
| image(x, y) | The image of object x is y| 
| temperature(air, x) |The temperature of the air is x| 
| visible(x) | The object x is visible| 
| stability(ground, x) |The stability of the ground is x| 

To keep the consistency, the representation follows an object-oriented approach. Objects are instances of a class and may have attributes with values. Aerostack assumes that the values of attributes defined for an object using triplets are mutually exclusive. For example, the belief charge(battery, empty) is incompatible with the belief charge(battery, full) because the values empty and full are mutually exclusive. Aerostack keeps consistency among beliefs. When a belief is added, e.g., charge(battery, empty), the incompatible beliefs are automatically retracted, e.g., charge(battery, full).

The operator can consult the state of the memory using belief expressions (e.g., within languages for mission plan specification). For example the user can use the following belief expression to know the coordinates of the current position: 

```
position(self,(?X,?Y,?Z))
```

In this belief expression, X, Y, and Z are variables that store the coordinates corresponding to the current position. The question mark (?) indicates that such variables are substituted by the values found in the belief memory. 