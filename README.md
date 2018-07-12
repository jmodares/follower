Copyright © 2015 - 2018 Jalil Modares

This program was part of my Ph.D. Dissertation research in the Department of Electrical Engineering at the University at Buffalo. I worked in UB's Multimedia Communications and Systems Laboratory with my Ph.D. adviser, [Prof. Nicholas Mastronarde](http://www.eng.buffalo.edu/~nmastron).

If you use this program for your work/research, please cite:
[J. Modares, N. Mastronarde, K. Dantu, "UB-ANC Emulator: An Emulation Framework for Multi-agent Drone Networks"](https://doi.org/10.1109/SIMPAR.2016.7862404).

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

# Follower
## Mission description
In this mission, MAV `i + 1` follows 10 meters behind MAV `i`. This is accomplished by MAV `i` sending its GPS location to MAV `i + 1` every 100 ms using a 74 byte packet.

## Build
The Follower mission is the default mission in the [UB-ANC Emulator](https://github.com/jmodares/UB-ANC-Emulator). It is built automatically when you build the emulator.

If you need to build it independently of the UB-ANC Emulator, then adapt the build instructions for the [UB-ANC Agent](https://github.com/jmodares/UB-ANC-Agent).

## Run in the UB-ANC Emulator
Assuming that you have just built the UB-ANC Emulator, you can run the Follower mission with three agents as follows:
```
cd ~/ub-anc/emulator
./setup_objects.sh 3
./start_emulator.sh
```

This will launch the emulator using QGroundControl as the GUI. Note that you can not start the mission until you receive the following messages from the drones (which are accessible by clicking on the [Vehicle Messages](https://docs.qgroundcontrol.com/en/toolbar/toolbar.html) status icon in QGroundControl):
```
[XXX] Info: EKF2 IMU0 is using GPS
[XXX] Info: EKF2 IMU1 is using GPS
```

Once you observe those messages, select the vehicles one-by-one from the *vehicle menu* and change their modes from **Stabilize** to **Guided** using the *flight mode* menu. After all the vehicles are in Guided mode, select *Vehicle 1*. Click **Disarmed** to arm Vehicle 1. You will be prompted to confirm that you want to arm the vehicle. After confirming, *Vehicle 1*'s status will change to **Armed**. Now click the **Takeoff** button and confirm that you want the vehicle to takeoff. After confirming, *Vehicle 1* will takeoff. Click on the map to set a *Waypoint* for it to fly to (this will also require confirmation). The other agents should follow behind.

You can plan more sophisticated flight paths using the [Plan View](https://docs.qgroundcontrol.com/en/PlanView/PlanView.html).

**Exercise 1:** Using Plan View, create a flight plan with four  waypoints and have the drone land at the last waypoint. Load your plan on **Vehicle 1** and execute it.

**Exercise 2:** Relaunch the emulator to run a **10** drone Follower mission.
