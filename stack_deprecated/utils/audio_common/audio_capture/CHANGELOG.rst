^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package audio_capture
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.3.3 (2018-05-22)
------------------

0.3.2 (2018-05-02)
------------------
* [sound_play] add option to select audio device to play / record (`#87 <https://github.com/ros-drivers/audio_common/issues/87>`_)
  * [sound_play] add option to select audio device to play
  * [sound_play] reformat README to markdown; add usage to set device via rosparam
  * audio_capture: add option for selecting device to use
  * audio_play: add option to select device for playing audio
  * add device argument to launch files
  Conflicts:
  audio_capture/launch/capture.launch
  audio_capture/launch/capture_to_file.launch
  audio_capture/src/audio_capture.cpp
  audio_play/launch/play.launch
  sound_play/scripts/soundplay_node.py
* Merge pull request `#102 <https://github.com/ros-drivers/audio_common/issues/102>`_ from EndPointCorp/fix_capture_leak
  Fix audio_capture leak
* Fix audio_capture sample/buffer leak
* Merge pull request `#90 <https://github.com/ros-drivers/audio_common/issues/90>`_ from prarobo/master
  Error checking code and improvements to launch files
* Bug fix
* fix(audio_capture): capturing wave using gst1.0
  0.10-style raw audio caps were being created, according to GStreamer warning. Should be audio/x-raw,format=(string).. now.
* Merge pull request `#1 <https://github.com/ros-drivers/audio_common/issues/1>`_ from prarobo/fixes
  Error checking code and improvements to launch files
* Removed default device
* Added error checking code
* Added parameters to launch files
* Contributors: Austin, Matt Vollrath, Prasanna Kannappan, Rokus, Yuki Furuta, prarobo

0.3.1 (2016-08-28)
------------------
* Update to new gstreamer rosdeps
* #70 can launch these in different namespaces with different microphones, and both are operating.
* #70 can switch between different microphones, but the first microphone doesn't like the hw:1, it only works with device:="" - so must be doing something wrong still.
* Add changelogs
* [audio_capture] add error handler
* [audio_capture] add option to publish captured audio data as wav format
  Conflicts:
  audio_capture/src/audio_capture.cpp
* Fixed memory leak (see #18).
* Removed trailing whitespace.
* Fixed problem that CMake uses gstreamer-0.1 instead of gstreamer-1.0
* Added gstreamer 1.0 dependecies
* Ported to gstreamer 1.0
  package.xml dependencies still missing
* Update maintainer email
* Contributors: Benny, Felix Duvallet, Furushchev, Lucas Walter, trainman419

0.2.11 (2016-02-16)
-------------------
* Add changelogs
* Contributors: trainman419

0.2.10 (2016-01-21)
-------------------
* Add changelogs
* Contributors: trainman419

0.2.9 (2015-12-02)
------------------
* Add changelogs
* [audio_capture] add error handler
* [audio_capture] add option to publish captured audio data as wav format
* Fixed memory leak (see `#18 <https://github.com/ros-drivers/audio_common/issues/18>`_).
* Removed trailing whitespace.
* Contributors: Felix Duvallet, Furushchev, trainman419

0.2.8 (2015-10-02)
------------------
* Update maintainer email
* Contributors: trainman419

0.2.7 (2014-07-25)
------------------
* audio_capture.cpp has to wait for generated AudioData headers
* Contributors: v4hn

0.2.6 (2014-02-26)
------------------
* audio_capture and play _require\_ gstreamer, it's not optional
* Contributors: v4hn

0.2.5 (2014-01-23)
------------------
* "0.2.5"
* Contributors: trainman419

0.2.4 (2013-09-10)
------------------
* Update CMakeLists.txt
* audio_capture: install launchfiles
* Contributors: David Gossow

0.2.3 (2013-07-15)
------------------
* Fix install rule for audio_capture.
* Contributors: Austin Hendrix

0.2.2 (2013-04-10)
------------------

0.2.1 (2013-04-08 13:59)
------------------------

0.2.0 (2013-04-08 13:49)
------------------------
* Finish catkinizing audio_common.
* Catkinize audio_play.
* Catkinize audio_capture.
* Fix typo in package.xml
* Versions and more URLs.
* Convert manifests to package.xml
* Convert audio_capture manifest to package.xml
* Ditch old makefiles.
* Updates manifest
* Updated manifests for rodep2
* oneiric build fixes, bump version to 0.1.6
* Removed redundant thread::thread
* Added a rosdep.yaml file
* Fixed to use audio_common_msgs
* Added ability to use different festival voices
* Updated documentation
* Added ability to capture to file
* Fixed ignore files
* Added hgignore files
* Audio_capture and audio_play working
* Making separate audio_capture and audio_play packages
* Moved audio_transport to audio_capture
* Contributors: Austin Hendrix, Brian Gerkey, Nate Koenig, nkoenig
