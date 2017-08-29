# thruster-test-stand
Repository for the OSU UWRT Thruster Test Stand code.

## Objective ##
To characterize all 10 Blue Robotics Thrusters for thrust output, current, and voltage.

## Software Setup ##
1. Upload `ThrusterTestStand.ino` program to Arduino.
2. Run `python ThrusterTestStand.py` in the command line. This will save the data to a CSV file.
If `python ThrusterTestStand.py` does not work, the device serial port `'/dev/ttyACM1'` may need to be changed. Edit constants in the .ino file to change testing parameters.

## Hardware Setup ##
1. Check battery voltage
2. Check wiring diagram below on Arduino shield:
![alt text](https://github.com/lisadlima/thruster-test-stand/blob/master/ThrusterTestStand/ThrusterTestStandDiagram.png)
3. Connect battery to the ESC only when you are ready to run the thruster
