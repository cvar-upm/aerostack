This page describes how the operator can create the environment map for a mission by using the graphical user interface. This tool allows the operator to set the size of the environment map and to place the static physical objects and the visual markers used to the self-localization of the vehicle. In addition this tool allows the operator to import or export a map using external files and to load or save the current map to internal config files used by Aerostack. To edit the current map or to create a new one, press the 'Edit Map' button in the 'Environment' tab at the lower right corner.

[[Files/GUIEnvironmentViewer.png]]

Alternatively, the operator can also configure the environment map using a set of XML files. Please, consult the following link to know how to write these files:

- [[Configure the Environment Map Using XML Files]]

## Creating a new map

To start the creation of a new map in the environment viewer widget, you have to press the 'New' button. A window dialog will be displayed, allowing the user to set the X size and the Y size of the map and its starting point. Press accept and the new map will be created. Four walls will be created to delimit the map zone.

[[Files/GUINewMap.png]]

## Creating new objects

A set of tools were created to add a new object to the mission environment. To create a new object, just select the tool with the required object and right-click in the desired position. This will create an object of the specified type, that can be modified with the edition tool.

[[Files/GUIMapEditionTools.png]]

## Editing an existing object

To edit an existing object, just use the selection tool and press the desired object in the map. That will display a dialog in the right side of the window allowing the user to modify the selected object. To delete an object, just select it and press the 'supr' key.

Additionally, the user can drag the objects and drop them wherever he desires to move them.

In order to improve the precision when selecting, creating or moving an object, you can use the precision tool or press 'shift' in order to adapt the selection pointer to the grid.

Here's a couple of screenshots that show how the addition and customization of a drone, a pole and a wall is done. Keep in mind that each object's ID number must all be different. If a pair of ID's are the same number the operator will be asked to check them and set them up properly.

[[Files/GUIMapEditionMode1.png]]

[[Files/GUIMapEditionMode2.png]]

[[Files/GUIMapEditionMode3.png]]

When you're finished editing your new Environment Map you can click the 'Accept' button. This will prompt a window as shown in the next picture that explains to you the new map wont be available until Aerostack is restarted.

[[Files/GUIMapEditionModeFinal.png]]

Whenever you choose to restart Aerostack the latest map exported to the Aerostack configuration folder will be displayed.

[[Files/GUIMapEditionModeFinal2.png]]

## File management

The map creation tool allows the user to save a file with all the current information of the map by pressing the 'Export' button. Likewise, the 'Import' button allows the user to select a file created by the tool in order to load a map created earlier.

To use the map in a mission, just press the button 'Accept', and the configuration files will be overwritten. In addition, the program will ask the user to restart Aerostack to make the changes available to use.

## Example

Here you can download a video showing an example of map environment configuration:

- [Example video](https://raw.githubusercontent.com/wiki/Vision4UAV/Aerostack/Files/VideoMapConfiguration.mp4)

See here another video that presents this process:

[![](https://img.youtube.com/vi/KqlVdzQnSf0/0.jpg)](https://www.youtube.com/watch?v=KqlVdzQnSf0)