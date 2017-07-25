# robot_markers
[![Build Status](https://travis-ci.org/jstnhuang/robot_markers.svg?branch=indigo-devel)](https://travis-ci.org/jstnhuang/robot_markers)

Generates markers for a robot given a URDF.

![image](https://cloud.githubusercontent.com/assets/1175286/26433797/93c5f92e-40b9-11e7-8d20-070e9c4787fc.png)

Demo:
```
roslaunch fetch_gazebo playground.launch
rosrun rviz rviz
# Add MarkerArray display on the "robot" topic
rosrun robot_markers demo
```
