^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package parrot_arsdk
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.12.61 (2017-08-13)
--------------------
* Change package versioning scheme to X.Y.ZP
  3.12.6 (patch 0) to 3.12.60
* Merge pull request `#7 <https://github.com/AutonomyLab/parrot_arsdk/issues/7>`_ from thomas-bamford/indigo-devel
  Patch json-c_avoid_so_version SDK 3.12.6
* Patch json-c_avoid_so_version SDK 3.12.6
* Contributors: Thomas Bamford

3.12.6 (2017-07-06)
-------------------

* Update to SDK 3.12.6
* SDK 3.12.6 Changelog:
  - Fixed Android issues (versioning & link error on API19)
* SDK 3.12.5 Changelog:
  - Declare AccessoryState event as a MAP_ITEM type
  - Handle list flags of AccessoryState and DebugSettingsInfo events directly in libARController.
* SDK 3.12.4 Changelog:
  - Use Python3 for all scripts
  - Added new Mavlink mission items related to Sequoia
  - Added an event to know if there is a Sequoia attached to the drone
  - Renamed the iOS precompiled folders as arsdk-ios and arsdk-ios_sim*
  - Removed appCompat-v7 from the dependencies of ARSDK3.
  - Fixed direct connection to a Disco
* SDK 3.12.3 Changelog:
  - Use Python3 for all scripts
  - Added new Mavlink mission items related to Sequoia
  - Added an event to know if there is a Sequoia attached to the drone
  - Renamed the iOS precompiled folders as arsdk-ios and arsdk-ios_sim
* SDK 3.12.1 Changelog:
  - Fixed reconnection issues on all Wifi products (when the reconnection appears less than 5 seconds after the disconnection).
* SDK 3.12.0 Changelog:
  - Fixed non-ack commands
  - Simplify the way to create ftp managers from a device service
  - Fixed crash when swapping apps using the MPP (Android)
  - Fixed minSDKVersion and targetSDKVersion of libmux (Android)

3.11.0 (2017-02-11)
-------------------
* Update to SDK 3.11.0
  SDK Changelog:
  - Fixed non-ack commands (camera orientation was always sent)
  - Updated features list in the device controllers
  - Old and deprecated Unix samples have been removed
  - Coverity fixes
* Contributors: Mani Monajjemi

3.10.1 (2016-09-27)
-------------------
* Update to SDK 3.10.1 (from 3.9.1) - patch 0
* Changelog for SDK 3.10.1
    - Fixed events as list management
    - Patched curl to avoid using clock_gettime on iOS
    - Renamed internal MD5 symbol
    - Fixed documentation generator
* Changelog for SDK 3.10.0
    - Disco support
    - SkyController 2 support
    - Mambo support
    - Swing support
    - new messages
* Changlog for SDK 3.9.2
    - Support of audio stream for Jumping evos
    - new messages for Bebop and Bebop 2
    - Alchemy updated (python3 needed)
* Contributors: Mani Monajjemi

3.9.1 (2016-07-25)
------------------
* Parrot ARSDK 3.9 Changes
    * New commands:
        * Bebop and Bebop 2:
        * BankedTurn
        * BankedTurnChanged
        * MaxPitchRollRotationSpeed
        * MaxPitchRollRotationSpeedChanged
        * wifiSecurity
        * VideoStabilizationMode
        * VideoStabilizationModeChanged
        * New commands to build the SDK:
    * For iOS: ./build.sh -p arsdk-ios -t build-sdk -j
    * For iOS Simulator: ./build.sh -p arsdk-ios_sim -t build-sdk -j
    * For Android: ./build.sh -p arsdk-android -t build-sdk -j
    * For Unix: ./build.sh -p arsdk-native -t build-sdk -j
    * New outputs directory:
        * For iOS: <SDK>/arsdk-ios
        * For iOS Simulator: <SDK>/arsdk-ios_sim
        * For Android: <SDK>/arsdk-android
        * For Unix: <SDK>/arsdk-native But old output are kept (with simlinks to avoid breaking compatibility).
        * libARController Android bug fix (a big thanks to Synman :+1: )
    * Video decoding bug fix in the iOS Sample (a big thanks to ar.tommy and ka010 :+1: )
    * Other bug fixes
* parrot_arsdk Changes
    * Add travis config file
    * Minor fix for package.xml
    * Initial catkin wrapper for Parrot ARDSDK
        * Include a stripped tarball of the SDK
        * SDK Version: 3.9.1
        * Populate both devel and install spaces
    * Add a patch to disable non-x86 compilation flags for arm platform from
    * Add a script to determine the host arch robustly. This script is used
      by CMake to pass appropriate flags to build_sdk.py
    * Contributors: Mani Monajjemi
