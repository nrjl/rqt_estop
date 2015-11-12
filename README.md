# rqt_estop

Basic emergency stop button GUI for ROS.

Currently expects cmd_vel twists to be sent to /cmd_vel_estop 
(remap existing if necessary) and then forwards messages to 
/cmd_vel if e-stop is not activated. When activated, it will
send a zero twist then stop forwarding messages from 
/cmd_vel_estop.

--- INSTALLATION ---
Requires ROS (tested on Indigo) and rqt
sudo apt-get install ros-%DISTRO%-rqt ros-%DISTRO%-rqt-common-plugins


cd ~/catkin_ws/src
git clone git@github.com:nrjl/rqt_estop.git
cd ..
catkin_make

Run using:
rqt --standalone rqt_estop

Or add to existing rqt widget
