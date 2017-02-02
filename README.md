# HolySee

This repository contains Team 4141's Robot Vision solution. 

![HolySee Block Architecture](https://github.com/MDHSRobotics/TeamWiki/blob/master/images/CV%20Block%20Arch.png)

For background information, see [Robot Vision Concepts](https://github.com/MDHSRobotics/TeamWiki/wiki/Robot%20Vision%20Concepts).


This repository contains the following projects:

1. __MSee__ a Java application which is the orchestrator of the vision system.  
   * MSee manages system configuration
   * MSee discovers connected input devices (cameras and lidar)
   * MSee discovers Roborio presence and established a communication channel with RoboRio (WebSockets)
   * MSee encapsulates CSee, the native implementation of the vision processing and streaming pipeline
   * MSee enables control over which channel is streamed to the operator console
   
1. __CSee__  a c++ shared library which contains C++ (native) image processing (OpenCV) and video streaming (gstreamer) libraries and custom code required for computer vision and augmented reality.

1. __ISee__  UI components running on the operator console.
   * ISee enables the operator to select which channel is streamed from the robot to the console
   * ISee provides the operator with a video streamer viewer to view the selected feed
   
For more information, see For background information, see [Understanding HolySee](https://github.com/MDHSRobotics/TeamWiki/wiki/Understanding%20HolySee).
