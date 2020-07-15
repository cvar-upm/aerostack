sound_play
=========

## Dependencies

- python-pygame
- festival
- festvox-don
- alsa-base
- alsa-tools

## Checking that the speaker/sound card is recognized by the kernel

`cat /proc/asound/cards`

Your card should be in the list. Make note of the number in front of the
card, it will be used to tell alsa where to play sound from.

If your sound device does not show up, your kernel may not support it, or
the module may not be loaded. For usb speakers, you may want to try:

`modprobe snd-usb-audio`

(not sure if this list is exhaustive)

## Telling alsa which sound card/speaker to use

Run (replace 75 with the number of the sound device to use):

`asoundconf set-default-card 75`

This will create .asoundrc.asoundconf in your home directory.
To make alsa use these settings, add the following line to `~/.asoundrc`

`include ".asoundrc.asoundconf"`

To set this default to all users, copy this to the system-wide alsa
configuration file:

`mv ~/.asoundrc.asoundconf /etc/asound.conf`

## Getting started

Start the sound play node, and have a look at the scripts in the scripts
directory that exercise the node's functionality. 

## Specify Device via ROS Param

Besides setting default device as system wide settings, you can also specify audio device via `rosparam`:

``` xml
<launch>
  <node name="soundplay_node" pkg="sound_play" type="soundplay_node.py">
    <param name="device" value="hw:1,0" />
  </node>
</launch>
```

or simply run: `rosrun sound_play soundplay_node.py _device:="hw:1,0"`

In the launch file above, `~device` parameter is set to `hw:1,0`, which tells `soundplay_node` to use audio device No. `0` connected to audio card No.`1`.
To find card/device number which you want to use, execute:

``` bash
sudo aplay -l
```

