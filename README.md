# rqt_estop

Basic emergency stop button GUI for ROS. The GUI is a simple toggle push button that can be either depressed to stop the robot or released to allow the robot to continue driving.

This package is currently implemented to listen to command velocities on one topic (`\cmd_vel_estop`) and then either forward the messages to the `\cmd_vel` topic if the e-stop is released, or send a zero twist and then stop sending messages if the e-stop is depressed. This means that in most systems, any or all nodes that were sending commands directly to `\cmd_vel` will need to have their outputs remapped to `\cmd_vel_estop`.

NOTE: This is pretty janky and quite old - but served as a simple example. If someone wants it updated, please let me know.

## INSTALLATION 
Requires ROS (tested on Indigo) and rqt
```
sudo apt-get install ros-%DISTRO%-rqt ros-%DISTRO%-rqt-common-plugins

cd ~/catkin_ws/src
git clone https://github.com/nrjl/rqt_estop.git
cd ..
catkin_make
```

Run using:
`rqt --standalone rqt_estop`

Or add to existing rqt widget
