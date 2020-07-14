A behavior tree is a visual modelling language that uses a graphical notation to represent the behavior of a system. Aerostack provides a graphical editor to create a mission plan as a behavior tree. 

[[Files/GUIBehaviorTree.png]]

## Node types

Each behavior tree is represented with a hierarchy of executable nodes. Nodes can succeed or fail during the execution of the mission plan. When the operator creates a behavior tree, the operator gives a name to each node and associates a particular type.

Leaf nodes are used to execute simple actions. The types of leaf nodes are the following:

- Behavior. A behavior node specifies a particular behavior that Aerostack can execute, such as TAKE_OFF, LAND or GO_TO_POINT. To know the available list of behaviors, consult the following link: [[catalog of behaviors]]. If the behavior type is goal-based, this node succeeds when the behavior goal is accomplished. If the behavior type is recurrent, this node succeeds if the behavior is correctly initiated (or if it is correctly deactivated).
- Add belief. This node adds a belief expression to the [[memory of beliefs]]. It succeeds if the belief is correctly added, otherwise fails.
- Remove belief. This node removes a belief expression from the [[memory of beliefs]]. It succeeds if the belief is correctly removed, otherwise fails.
- Query. A query node corresponds to a question that is verified in the [[memory of beliefs]]. The question is formulated with a belief expression with a set of predicates that, optionally, can include variables. This node succeeds if the belief expression is true, otherwise it fails. Queries are useful to help control the mission workflow. 

Intermediate nodes of the tree establish the control regime (e.g., a sequence, a loop, etc.). The types of intermediate nodes are the following: 

- Sequence. This node executes the child nodes in sequence and succeeds when all the children succeed. Otherwise it fails.
- Selector. This node executes the child nodes in sequence and succeeds when one of the children succeeds. If none of them succeeds, it fails.
- Parallel. This node executes its child nodes in parallel. Let N be the number of child nodes. It returns success if the number of succeeding children is larger or equal than a local constant S, specified by the user. Returns failure if the number of failing children is larger N - S.
- Repeat. This node repeats the execution of a child node a number of times. Returns success. It can only have one child node.
- Repeat until fail. This node repeats the sequential execution of child nodes until a child node fails. This node always succeeds. 
- Inverter. This node returns failure if the child node succeeds. Otherwise it succeeds.
- Succeeder. This node executes its child node and, no matter what is the result of the execution, it always succeeds.

---
## Launching the behavior tree editor

To launch the behavior tree editor, you can execute a script file with the following content (for example, for the drone drone111 and the project `basic_behavior_tree_drone_simulator`):

````
#!/bin/bash

NUMID_DRONE=111
export AEROSTACK_PROJECT=${AEROSTACK_STACK}/projects/basic_behavior_tree_drone_simulator

. ${AEROSTACK_STACK}/setup.sh

gnome-terminal \
--tab --title "Executive Coordinator" --command "bash -c \"
roslaunch behavior_coordinator_process behavior_coordinator_process.launch --wait \
  drone_id_namespace:=drone$NUMID_DRONE \
  behavior_catalog_path:=${AEROSTACK_PROJECT}/configs/mission/behavior_catalog.yaml \
  drone_id:=$NUMID_DRONE \
  my_stack_directory:=${AEROSTACK_PROJECT};
exec bash\"" \
--tab --title "Behavior Tree Editor" --command "bash -c \"
roslaunch behavior_tree_editor behavior_tree_editor.launch --wait \
  robot_namespace:=drone$NUMID_DRONE \
  drone_id:=$NUMID_DRONE \
  my_stack_directory:=${AEROSTACK_PROJECT} \
  mission_config_path:=${AEROSTACK_PROJECT}/configs/drone$NUMID_DRONE;
exec bash\""  &
````
## Editing a behavior tree

The operator can specify a mission plan using the behavior tree editor of Aerostack. Aerostack presents graphically the behavior tree using a hierarchy browser. The editor uses standard edition mechanisms to allow users create a behavior tree by adding, modifying or deleting nodes of the tree. The editor provides guidance and assistance to users presenting valid options on menu bars and checking the presence of user errors in texts describing parameter values or belief expressions. The created behavior tree is stored in yaml file (with the name behavior_tree_mission_file.yaml).

[[Files/BehaviorTreeEditor.png]]

The editor window has a set of buttons at the bottom with the following functionality:

- New: Creates the root node of a new behavior tree with a name given by the user.
- Import: Imports a behavior tree defined in a yaml file selected by the user.
- Export: Stores the behavior tree in a yaml file selected by the user. 
- Save: Saves the behavior tree in the file "behavior_tree_mission_file.yaml" (in the configuration folder).
- Cancel: Finishes the edition.
- Accept: Saves the behavior tree in the file "behavior_tree_mission_file.yaml" (in the configuration folder) and the edition is finished.

When the operator clicks the right mouse button on any of the nodes, a context menu is displayed showing a list of possible actions:

- Add child: Adds a new child node.
- Add sibling: Adds a new sibling node.
- Delete this node: Deletes a node from the tree.
- Modify this node: Allows to modify the characteristics of the node.

[[Files/BehaviorTreeNodeOptions.png]]

## Arguments, belief expressions and variables

When the user creates a node corresponding to a behavior, the user can write specific arguments. For example, if the user creates a node corresponding to the behavior GO_TO_POINT, the user can write the arguments in the corresponding box of the window as follows: 

```
coordinates: [5, 4.2, 0.7]
```

Behavior trees in Aerostack can use variables to communicate information between leaf nodes. For example, the user can create a query node called "Identify current position" with the belief expression: 

```
position(self,(?X,?Y,?Z))
```

In this expression, X, Y, and Z are preceded by a question mark (?) to represent that they are variables. When this node is executed, the expression matches the corresponding predicate in the belief memory. For example, if the belief memory has the predicate `position(self, (3.3, 8.7, 0.6))`, the variables get the values X = 3.3, Y = 8.7, Z = 0.6.

The values of these variables can be used by other nodes of the mission plan. For instance, there may be an operation node in another place of the same mission plan that uses the behavior GO_TO_POINT with the following argument: 

```
coordinates: [+X, +Y, +Z]
```

The sign plus (+) as a prefix of the variable name indicates that the variable will be substituted during the execution by the value that the variable has in this moment. Considering the previous example, this means that the robot will requested to go to a destination with the coordinates (3.3, 8.7, 0.6).

The GUI shows a specific window box (below the behavior tree) with the list of variables used by the behavior tree and the values. 

[[Files/BehaviorTreeVariables.png]]

## Complete example

Here's an example of a complex mission with different types of intermediate nodes.

[[Files/GUIComplexBTExample.png]]