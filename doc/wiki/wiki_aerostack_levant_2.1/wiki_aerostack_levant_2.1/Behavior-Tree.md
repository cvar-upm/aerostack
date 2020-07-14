A behavior tree is a visual modelling language that employs a defined graphical notation to represent the behavior of a system. It is commonly used to create the artificial intelligence of games, thanks to their easy implementation and understanding.

[[Files/GUIBehaviorTree.png]]

## Node types

A behavior tree is defined by a hierarchy of nodes. During the execution of a behavior tree, each node can succeed or can fail. When the operator creates a behavior tree, the operator gives a name to each node and associates a particular type.

Leaf nodes are used to execute simple actions. The types of leaf nodes are the following:

- **Behavior**: A behavior node specifies a particular behavior that Aerostack can execute, such as TAKE_OFF, LAND or GO_TO_POINT. To know the available list of behaviors, consult the following link: [[catalog of behaviors]]. If the behavior type is goal-based, this node succeeds when the behavior goal is accomplished. If the behavior type is recurrent, this node succeeds if the behavior is correctly initiated (or if it is correctly deactivated).

- **Add belief**: This node adds a belief expression to the [[memory of beliefs]]. It succeeds if the belief is correctly added, otherwise fails.

- **Remove belief**: This node removes a belief expression from the [[memory of beliefs]]. It succeeds if the belief is correctly removed, otherwise fails.

- **Query**: A query node corresponds to a question that is verified in the [[memory of beliefs]]. The question is formulated with a belief expression with a set of predicates that, optionally, can include variables. This node succeeds if the belief expression is true, otherwise it fails. Queries are useful to help control the mission workflow. 

Intermediate nodes are used to control the execution of child nodes. The types of intermediate nodes are the following:

- **Sequence**: This node executes all its child nodes in sequence and succeeds when all the children succeed. Otherwise it fails.

- **Selector**: This node executes all its child nodes in sequence and succeeds when one of the children succeeds. If none of them succeed, it fails.

- **Parallel**: This node executes all its child nodes in parallel. Let N be the number of child nodes. It returns success if the number of succeeding children is larger or equal than a local constant S, specified by the user. Returns failure if the number of failing children is larger than F = N - S.

- **Repeater**: This node repeats the execution of a child node a number of times. Returns success. It can only have one child node.

- **Repeat until fail**: This node repeats the execution of child nodes until the child node returns failure. Returns success. The child nodes are executed in sequence.

- **Inverter**: This node returns failure if the child node succeeds. Otherwise it succeeds.

- **Succeeder**: This node executes its child node and, no matter what is the result of the execution, it always succeeds. 

## Editing a behavior tree

The operator can specify a mission plan using the behavior tree editor of the graphical user interface of Aerostack. Details about the graphical user interface can be consulted here:

- [[Graphical user interface]]

Keep in mind the behavior trees are not saved within the Aerostack configuration files. This means that a behavior tree is not persistent between different executions of Aerostack. If the operator wants to save his progress when editing a tree or doesn't want to lose the tree he just created, he can save the tree onto a *.yaml* file using the 'Export' button. Likewise you can import any tree using the 'Import' button.

The following steps describe how to create a behavior tree.

- Change the operation mode to 'Guided by behavior trees' in the control panel. 

[[Files/GUIBTGuideStep1.png]]

- Press the 'Edit mission' button at the right bottom corner of the window to edit the current behavior tree or to create a new one.

[[Files/GUIBTGuideStep2.png]]

- Press 'New' button to create a new behavior tree or to replace the previous one. A dialog window is displayed asking for the name of the mission. It creates a new *sequence* root node.

[[Files/GUIBTGuideStep3.png]]

- By right-clicking in the desired node, a local menu is displayed to add a new child or sibling to the node, modify the node or remove it. The edition/creation dialog is displayed if those actions are chosen. It allows the user to select the type of node and its options. To make the changes available press 'Accept'.

[[Files/GUIBTGuideStep4_1.png]]

[[Files/GUIBTGuideStep4_2.png]]

- The operator can save the behavior tree in an external file (a *.yaml* file) by pressing the 'Export' button. Likewise, an existing external file corresponding to a mission that was previously saved, can be imported by pressing the 'Import' button. 

- Finally, the user clicks 'Accept' button to exit from the edition mode and the behavior tree is ready to be executed.

[[Files/GUIBTGuideStep5.png]]

## Arguments, belief expressions and variables

When the user creates a node corresponding to a behavior, the user can write specific arguments. For example, if the user creates a node corresponding to the behavior GO_TO_POINT, the user can write the arguments in the corresponding box of the window as follows: 

```
coordinates: [5, 4.2, 0.7]
```

When the user creates a node corresponding to a query for the [[memory of beliefs]], the user can write the specific belief expression. For example the user can create a query node called "Save current position" with the belief expression: 

```
position(self,(?X,?Y,?Z))
```

In this belief expression, X, Y, and Z are variables that store the coordinates corresponding to the current position. The question mark (?) indicates that such variables are substituted by the values found in the belief memory. 

These variables can be used later in other behaviors or queries. For example the user can write a behavior node GO_TO_POINT with the following argument:

```
coordinates: [+X, +Y, +Z]
```

The sign plus (+) as a prefix of the variable name indicates that the variable is substituted by the value that the variable has in this moment.

The GUI shows a specific window box (below the behavior tree) with the list of variables used by the behavior tree and the values. 

## Complete example

Here's an example of a complex mission with different types of intermediate nodes.

[[Files/GUIComplexBTExample.png]]