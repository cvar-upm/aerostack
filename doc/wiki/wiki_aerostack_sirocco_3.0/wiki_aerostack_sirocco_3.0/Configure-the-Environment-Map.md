#Configure the Environment Map

This page describes how the operator can create the environment map for a mission by using the graphical user interface. This tool allows the operator to set the size of the environment map and to place the static physical objects and the visual markers used to the self-localization of the vehicle. In addition, this tool allows the operator to import or export a map using external files and to load or save the current map to internal config files used by Aerostack. To edit the current map or to create a new one, press the 'Edit' button in the upper bar and then select the option 'Environment Map'. It will pop-up a window as the following one.

[[Files/EnvironmentMapEditor.png]]

Alternatively, the operator can also configure the environment map using a set of XML files. Please, consult the following link to know how to write these files:

- [Configure the Environment Map Using XML Files](https://github.com/Vision4UAV/Aerostack/wiki/Configure-the-Environment-Map-Using-XML-Files)

## Creating a new map

To start the creation of a new map in the environment viewer widget, you have to press the 'New' button. A new window dialog will be displayed, allowing the user to set the X size and the Y size of the map and its starting point. Press accept and the new map will be created. Four walls will be created to delimit the map zone.

[[Files/CreatingNewMap.png]]

## Creating new objects

A set of tools were created to add a new object to the mission environment. To create a new object, just select the tool with the required object and right-click in the desired position. This will create an object of the specified type, that can be modified with the edition tool.

[[Files/CreatingNewObject.png]]

## Editing an existing object

To edit an existing object, just use the selection tool and press the desired object in the map. That will display a dialog in the right side of the window allowing the user to modify the selected object. To delete an object, just select it and press the 'supr' key.

Additionally, the user can drag the objects and drop them wherever he desires to move them.

In order to improve the precision when selecting, creating or moving an object, you can use the precision tool or press 'shift' in order to adapt the selection pointer to the grid.

[[Files/EditEnvironment.png]]

When you're finished editing your new Environment Map you can click the 'Accept' button. The new map will be ready to be used.

## File management

The map creation tool allows the user to save a file with all the current information of the map by pressing the 'Export' button. Likewise, the 'Import' button allows the user to select a file created by the tool in order to load a map created earlier.

To use the map in a mission, just press the button 'Accept', and the configuration files will be overwritten.

Here you can watch a video showing an example of map environment configuration:

[![](https://img.youtube.com/vi/3vDRoh7D8-A/0.jpg)](https://youtu.be/3vDRoh7D8-A)