The operator can specify the tasks of a mission using the TML language (task-based mission specification language) specifically designed for Aerostack. TML uses XML syntax.

The following sections describe how to write in TML language a mission specification. As a complete example, a mission specification file is provided at the end of this document.

### 1. Mission

The mission is defined with the tag `<mission>` and the attribute `root_task`. The `root_task` attribute indicates which task tree should be executed when the mission starts. For example:

```xml
<mission name="example task">
</mission>
```

The body of the mission is separated in two main parts: (1) task tree definitions and (2) event handlers.

### 2. Task Trees

The first part of the mission specification includes one or more task trees with the tag `<task_tree>`. Each task tree contains a series of tasks organized in a tree, and can be identified by the name of its root task. Each task is specified using the tag `<task>` and the attribute `name`. For example:

```xml
<task_tree>
  <task name= "example root task">
    <task name="example child task">
      <task name="example leaf task 1">
      </task>
    </task>
    <task name="example leaf task 2">
    </task>
  </task>
</task_tree>
```

The body of a task can include the tag `<behavior>` with the attribute `name` to specify an interpretable behavior (e.g., TAKE_OFF, LAND, etc.). The body of a task can also include one or several tags `<recurrent_behavior>` with the attribute `name` to specify the recurrent_behaviors to be activated at the start of the task and deactivated at the end. For example:

```xml
<task name="track image">
  <recurrent_behavior name="SELF_LOCALIZE_BY_VISUAL_MARKERS"/>
  <behavior name="FOLLOW_IMAGE">
      <argument name="duration" value="60"/>
  </behavior>
</task>
```

A behavior can optionally include arguments. Arguments use the tag `<argument>` and the optional attribute `name`. For example:

```xml
<task name="move to the first point">
  <behavior name="GO_TO_POINT">
      <argument name="coordinates" value="[3.0, 4.2, 1.5]"/>
  </behavior>
</task>
```

Instead of a behavior, a task may contain an operation with the belief memory. These operations are: `<add>`, `<remove>` and `<consult>`. Each of these contain a `belief` argument that specifies the belief to add or remove, or the belief expression to consult. Consulting an expression is used to obtain values from the belief memory that can be later used with  the operand `+`. For example:

```xml
<task name="go to pickup site">
  <task name="obtain target coordinates">
    <consult belief="position(object_1, (?X, ?Y, ?Z))" />
  </task>
  <task name="hover over object to pick up">
    <behavior name="GO_TO_POINT">
      <argument name="coordinates" value="[+X, +Y, 1.5]" />
    </behavior>
  </task>
</task>
```

Tasks can be organized in a hierarchy. The body of a complex task (i.e., a task that use other tasks) can include skills that are active during the task execution. The body of a complex task does not include behaviors or belief operations. Instead, the body includes one or several simpler tasks that are executed in sequence. For example:

```xml
<task name="move then land">
  <task name="move to the first point">
    <behavior name="GO_TO_POINT">
        <argument name="coordinates"  value="[3.0, 4.2, 1.5]"/>
    </behavior>
  </task>
  <task name="land">
    <behavior name="LAND" />
  </task>
</task>
```

### 3. Event handlers

The second part of a mission is the a list of event handlers. This part of the mission specification is defined with the tag `<event_handling>`:

```xml
<event_handling>
</event_handling>
```

Each event handler describes how to react to a particular event, while the mission planner is waiting the completion of a behavior. Events are defined with the tag `<event>` and the attribute `name`. Each event includes a `<condition>` tag, a `<call>` tag and a `<termination>` tag. The `<condition>` tag contains a `belief` attribute which specifies the belief expression that has to be true in order to activate the event. The `<call>` tag contains a `root_task` attribute with the name of the root task of the task tree to activate when the condition is met. The `<termination>` tag contains a `mode` attribute that specifies what to do when the task tree executed finishes. The termination mode can be any of: `REPEAT_TASK`, `NEXT_TASK`, `END_MISSION`, `ABORT_MISSION`.

```xml
<event_handling>

  <event name="search for image when drone_1 reaches its objective">
    <condition belief="objective(drone_1, ?X), position(drone_1, ?X)"/>
    <call root_task="search for image" />
    <termination mode="REPEAT_TASK"/>
  </event>

  <event name="low battery">
    <condition belief="battery_level(self, LOW)"/>
    <call root_task="emergency land"/>
    <termination mode="ABORT_MISSION"/>
  </event>

</event_handling>
```

To know the available behaviors the robot can perform, consult the following list:

- [[Catalog of Behaviors]]

## Name and location of the mission file

To be used by the Aerostack, the mission has to be written in a XML file called `mission_specification_file.xml`. This file must be located in `$AEROSTACK_STACK/configs/` within a folder selected by the operator called `drone{Id}` (`{Id}` = 0, 1, 2, ...). This is the default name, as it is established in the .launch file located within the `launch` directory in the repository `task_based_mission_planner_process`.

## Check syntax errors

To check if the XML file with the mission specification has syntax errors, launch the mission planner executing the following command:

```
> roslaunch task_based_mission_planner_process task_based_mission_planner_process.launch
```

If the xml file does not have any errors, the following message is presented:

```
File loaded without errors! Waiting to start ...
```

## Publications

Please, note that these publications correspond to a previous version of TML that uses "actions" and "skills" instead of "behaviors":

- M. Molina, R. A. Suarez-Fernandez, C. Sampedro, J. L. Sanchez-Lopez, P. Campoy, (2017): [TML: a language to specify aerial robotic missions for the framework Aerostack](https://www.researchgate.net/publication/320309096_TML_a_language_to_specify_aerial_robotic_missions_for_the_framework_Aerostack). International Journal of Intelligent Computing and Cybernetics, Vol. 10 Issue: 4, pp.491-512. 

- M. Molina, A. Diaz-Moreno, D. Palacios, R. A. Suarez-Fernandez, J. L. Sanchez-Lopez, C.s Sampedro, H. Bavle and P. Campoy (2016): "[Specifying Complex Missions for Aerial Robotics in Dynamic Environments](http://oa.upm.es/43926/1/270_IMAV2016_Proceedings.pdf)". International Micro Air Vehicle Conference and Competition, IMAV 2016. Beijing, China.

## Complete Example

This example is a complete specification of a mission in TML language.

```xml
<!--==================================================
| FILE: mission_specification_file.xml
| BRIEF: A mission specification example.
| DETAILS:
|   Mission in which an object is found, picked up and
|   retrieved.
| AUTHORS:
|    Guillermo De Fermin
===================================================-->
<mission root_task="Search for object">

  <task_tree>
    <task name="Search for object">
      <task name="Initial phase">
        <recurrent_behavior name="SELF_LOCALIZE_BY_ODOMETRY" />
        <task name="Take off">
          <behavior name="TAKE_OFF"/>
        </task>
        <task name="Memorize current point">
          <consult belief="position(self, (?HOME_X, ?HOME_Y, ?HOME_Z))" />
        </task>
      </task>

      <task name="Start search">
        <recurrent_behavior name="SELF_LOCALIZE_BY_VISUAL_MARKERS" />
        <task name="Moving to point A">
          <behavior name="GO_TO_POINT">
            <argument name="relative_coordinates" value="[1, 0, 0]"/>
          </behavior>
        </task>
        <task name="Moving to point B">
          <behavior name="GO_TO_POINT">
            <argument name="relative_coordinates" value="[0, 1, 0]"/>
          </behavior>
        </task>
        <task name="Moving to point C">
          <behavior name="GO_TO_POINT">
            <argument name="relative_coordinates" value="[-1, 0, 0]"/>
          </behavior>
        </task>
        <task name="Moving to point D">
          <behavior name="GO_TO_POINT">
            <argument name="relative_coordinates" value="[0, -1, 0]"/>
          </behavior>
        </task>
      </task>

    </task>
  </task_tree>

  <task_tree>
    <task name="Retrieve object">
      <recurrent_behavior name="SELF_LOCALIZE_BY_VISUAL_MARKERS" />
      <task name="Memorize object location">
        <consult belief="position(object_1, (?OBJ_X, ?OBJ_Y, ?))" />
      </task>
      <task name="Hover above object">
        <behavior name="GO_TO_POINT">
          <argument name="coordinates" value="[+OBJ_X, +OBJ_Y, 1.2]" />
        </behavior>
      </task>
      <task name="Pick object up">
        <add belief="picked_up(object_1)" />
      </task>
      <task name="Go to starting point">
        <behavior name="GO_TO_POINT">
          <argument name="coordinates" value="[+HOME_X, +HOME_Y, +HOME_Z]" />
        </behavior>
      </task>
      <task name="Drop oject">
        <remove belief="picked_up(object_1)" />
      </task>
      <task name="Final land">
        <behavior name="LAND" />
      </task>
    </task>
  </task_tree>

  <task_tree>
    <task name="Emergency land">
      <behavior name="LAND" />
    </task>
  </task_tree>

  <event_handling>
    <event name="Object found">
      <condition belief="visible(object_1)"/>
      <call root_task="Retrieve object" />
      <termination mode="END_MISSION" />
    </event>

    <event name="Low battery">
      <condition belief="battery_level(self, LOW)"/>
      <call root_task="Emergency land"/>
      <termination mode="ABORT_MISSION"/>
    </event>
  </event_handling>
</mission>
```