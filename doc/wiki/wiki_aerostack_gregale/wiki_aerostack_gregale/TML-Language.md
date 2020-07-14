The operator can specify the tasks of a mission using the TML language (task-based mission specification language) specifically designed for Aerostack. TML uses XML syntax.



The following sections describe how to write in TML language a mission specification. As a complete example, a mission specification file is provided at the end of this document. 

### 1. Mission

The mission is defined with the tag `<mission>` and the attribute `name`. For example:

```xml
<mission name= "example of mission">
</mission>
```

The body of the mission is separated in two main parts: (1) task tree and (2) event handlers.  

### 2. Task Tree

The first part of the mission specification includes a list of tasks organized in a tree that are executed in sequence. Each task is specified using the tag `<task>` and the attribute `name`. For example:

```xml
<task name= "example of task">
</task>
```

The body of a task can include the tag `<action>` with the attribute `name` to specify an interpretable action (e.g., TAKE_OFF, LAND, etc.). The body of a task can also include one or several tags `<skill>` with the attribute `name` to specify the skills to be active. For example:

```xml
<task name="track image">
  <skill name="AVOID_OBSTACLES"/>
  <action name="WAIT">
      <argument name="duration" value="60"/>
  </action>
</task>
```

An action can include optionally arguments. Arguments use the tag `<argument>` and the optional attribute `name`. For example:

```xml
<task name="move to the first point">
  <action name="GO_TO_POINT">
      <argument name="coordinates" value="(3.0, 4.2, 1.5)"/>
  </action>
</task>
```

Tasks can be organized in a hierarchy. The body of a complex task (i.e., a task that use other tasks) can include skills that are active during the task execution. The body of a complex task does not include actions. Instead, the body includes one or several simpler tasks that are executed in sequence. For example:

```xml
<task name="move and wait">
  <task name="move to the first point">
    <action name="GO_TO_POINT">
        <argument name="coordinates"  value="(3.0, 4.2, 1.5)"/>
    </action>
  </task>
  <task name="wait 20 seconds">
    <action name="WAIT">
        <argument name="duration" value="20"/>
    </action>
  </task>
</task>
```

The linear sequence of task execution can be modified with repetitions and conditioned executions. The tag `<repeat>` and the attribute `times` is used to repeat a task several times. The tag `<condition>` and the attributes `parameter`, `comparison`, `value` are used to establish a condition to execute a task. The allowable values for the attribute comparison between numbers are {"equal", "less than", "less than or equal to", "greater than", "greater than or equal to", “not equal to”}. The comparison can be one of {"equal", "not equal to"} when the parameter is a string. The comparison can be "includes" when the parameter is a set of numbers and the value is a number. For example:

```xml
<task name="flip and move if green">
  <task name="flip three times">
    <repeat times="3"/>
    <action name="FLIP"/>
  </task>
  <task name="move to the first point">
    <condition parameter="OBSERVED_COLOR" comparison="equal" value="green"/>
    <action name="GO_TO_POINT">
        <argument name="coordinates" value="(3.0, 4.2, 1.5)"/>
    </action>
  </task>
</task>
```

### 3. Event handlers

The second part of a mission is the a list of event handlers. This part of the mission specification is defined with the tag `<event_handling>`:

```xml
<event_handling>
</event_handling>
```

Each event handler describes how to react to a particular event, while the mission planner is waiting the completion of an action. Events are defined with the tag `<event>` and the attribute `name`. Each event includes a list of conditions (in a conjunctive form), a list of actions and an ending step defined with the tag <termination> and the attribute `mode`. The allowable values for termination are {NEXT_TASK, REPEAT_TASK, ABORT_MISSION, END_MISSION}. For example:

```xml
<event_handling>

  <event name="time out since action started">
    <condition parameter="ACTION_FAILURE" comparison="equal" value="timeout"/>
    <termination mode="REPEAT_TASK"/>
  </event>

  <event name="low battery">
    <condition parameter="PERCENTAGE_BATTERY_CHARGE" comparison="less than" value="20"/>
    <action name="LAND"/> 
    <termination mode="ABORT_MISSION"/>
  </event>

</event_handling>
```

Events can use a particular type of condition with the attribute `currentTask`. This is useful to express that the event happens while a particular task is being executing. The task is identified with a sequence of names of task-subtasks separated by "/". For example:

```xml
  <event name="take off failure">
    <condition parameter="ACTION_FAILURE" comparison="equal" value="general"/>
    <condition currentTask="phase one/take off"/>
    <termination mode="ABORT_MISSION"/>
  </event>
```

To know the available actions, skills and parameters for TML, consult the following lists:

- [[List of Actions for TML]]
- [[List of Skills for TML]]
- [[List of Parameters for TML]]

## Publication

- Martin Molina, Adrian Diaz-Moreno, David Palacios, Ramon A. Suarez-Fernandez, Jose Luis Sanchez-Lopez, Carlos Sampedro, Hriday Bavle and Pascual Campoy (2016): "[Specifying Complex Missions for Aerial Robotics in Dynamic Environments](http://oa.upm.es/43926/1/270_IMAV2016_Proceedings.pdf)". International Micro Air Vehicle Conference and Competition, IMAV 2016. Beijing, China.(submitted)

## Complete Example

This example is a complete specification of a mission in TML language.

```xml
<!--==================================================
| FILE: mission_specification_file.xml
| BRIEF: A mission specification example.
| DETAILS:
|   This file includes basic movements to search in 
|   an area and Aruco visual markers recognition.
|   The vehicle flips when an Aruco visual marker has
|   been found.
| AUTHORS:
|    Adrian Diaz
===================================================-->
<mission name="Mission specification example">
  
<!--==================================================
| TASK: Initial phase
===================================================-->
  <task name="Initial phase">
    <task name="Taking off">
      <action name="TAKE_OFF"/>
    </task>
    <task name="Stabilizing at origin">
      <action name="STABILIZE"/>
    </task>
    <task name="Setting up HOME point ">
      <action name="MEMORIZE_POINT">
        <argument name="coordinates" label="HOME"/>
      </action>
    </task>
    <task name="Waiting 3 seconds">
      <action name="WAIT">
        <argument name="duration" value="3"/>
      </action>
    </task>
  </task>

<!--==================================================
| TASK: Search object
===================================================-->
  <task name="Searching Aruco identifiers">
    <skill name="RECOGNIZE_ARUCO_MARKERS"/>   
    <task name="Moving to point A">
      <action name="MOVE">
        <argument name="coordinates" value="(1, 0, 0)"/>
      </action>
    </task>
    <task name="Stabilizing at point A">
      <action name="STABILIZE"/>
    </task>
    <task name="Moving to point B">
      <action name="MOVE">
        <argument name="coordinates" value="(0, 1, 0)"/>
      </action>
    </task>
    <task name="Stabilizing at point B">
      <action name="STABILIZE"/>
    </task>

    <task name="Moving to point C">
      <action name="MOVE">
        <argument name="coordinates" value="(-1, 0, 0)"/>
      </action>
    </task>
    <task name="Stabilizing at point C">
      <action name="STABILIZE"/>
    </task>
  </task>

<!--==================================================
| TASK: Final phase
===================================================-->
  
  <task name="Final phase">
    <task name="Going home">
      <action name="GO_TO_POINT">
        <argument name="coordinates" label="HOME"/>
      </action>
    </task>

    <task name="Final landing">
      <action name="LAND"/>
    </task>
  </task>

<!--==================================================
| EXCEPTIONS
===================================================-->
  <event_handling>
<!--==================================================
| EVENT: Object found
===================================================-->
    <event name="Object found">
      <condition parameter="RECOGNIZED_ARUCO_MARKERS" comparison="includes" value="0"/>
      <action name="STABILIZE"/> 
      <action name="FLIP">
        <argument name="direction" value="FRONT"/>
      </action>
      <action name="STABILIZE"/>
      <termination mode="REPEAT_TASK"/>
    </event>

<!--==================================================
| EVENT: Low battery
===================================================-->
    <event name="Low battery">
      <condition parameter="percentageBatteryCharge" comparison="less than" value="20"/>
      <action name="LAND"/>   
      <termination mode="ABORT_MISSION"/>
    </event>

  </event_handling>
</mission>
```