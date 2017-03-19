# HolySee

This repository contains Team 4141's Robot Vision solution. 

![HolySee Block Architecture](https://github.com/MDHSRobotics/TeamWiki/blob/master/images/CV%20Block%20Arch.png)

For background information, see [Robot Vision Concepts](https://github.com/MDHSRobotics/TeamWiki/wiki/Robot%20Vision%20Concepts).


This repository contains the following projects:

1. __MSee__ a C++ application which is the orchestrator of the vision system.  
   * MSee manages system configuration
   * MSee discovers connected input devices (cameras and lidar)
   * MSee discovers Roborio presence and established a communication channel with RoboRio (WebSockets)
   * MSee uses CSee, a library of custom gsteamer plugins for computer vision and augmented reality
   * MSee enables control over which channel is streamed to the operator console
   
1. __CSee__  a c++ shared library which contains custom gstreamer image processing (OpenCV) plugins required for computer vision and augmented reality.

1. __ISee__  UI components running on the operator console.
   * ISee enables the operator to select which channel is streamed from the robot to the console
   * ISee provides the operator with a video streamer viewer to view the selected feed
   
For more information, see For background information, see [Understanding HolySee](https://github.com/MDHSRobotics/TeamWiki/wiki/Understanding%20HolySee).
