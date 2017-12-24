Copyright © 2015 - 2018 Jalil Modares

This program is part of my Ph.D. Dissertation research in the Department of Electrical Engineering at the University at Buffalo. I worked in UB's Multimedia Communications and Systems Laboratory with my Ph.D. adviser, [Prof. Nicholas Mastronarde](http://www.eng.buffalo.edu/~nmastron).

If you use this program for your work/research, please cite:
[J. Modares, N. Mastronarde, K. Dantu, "UB-ANC Emulator: An Emulation Framework for Multi-agent Drone Networks"](https://doi.org/10.1109/SIMPAR.2016.7862404).

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

# UB-ANC Emulator
An Emulation Framework for Multi-Agent Drone Networks

## Build
There are three main components used by UB-ANC Emulator:
* [UB-ANC Agent](https://github.com/jmodares/UB-ANC-Agent)
  * This is the mission that is going to be run on all agents (drones) in the network.

* [ns-3 Network Simulator](https://www.nsnam.org/docs/tutorial/html/getting-started.html#building-ns3)
  * ns-3 is used for network simulation between agents. After building the library, the path of the ns3 needs to be set in ns3.pri file in the engine folder.

* [ArduCopter Software in the Loop (SITL)](http://ardupilot.org/dev/docs/sitl-simulator-software-in-the-loop.html)
  * This is the actual software (firmware) that run on the real hardware controller.

Since UB-ANC-Emulator uses [QGroundControl](https://github.com/mavlink/qgroundcontrol) as its main library, it requires **Qt 5.7.1** or higher to be used.

```
git clone https://github.com/jmodares/UB-ANC-Emulator
mkdir build-emulator
cd build-emulator
qmake ../UB-ANC-Emulator
make -j4
cp -r ../UB-ANC-Emulator/scripts/* engine/release/
```

## Configuration
UB-ANC-Emulator uses **objects** folder to recognizes the IDs of the agents (drones). Every folder in the **objects** folder represents an emulated agent (drone). The naming format is **mav_xxx**, where xxx shows the ID, in the range **001 - 250**. In each **mav_xxx** folder there are three main files:
* **agent**
  * The mission executable

* **firmware**
  * The firmware executable running on real hardware

* **copter.parm**
  * The default parameters used in firmware

This can be done by running `build_objects.sh n`, where `n` is the number of agents in the network.
```
cd engine/release
./build_objects.sh 10
```

To build the objects folder, the script uses all three default files from **mav** folder. By default the agent executable is the [follower](https://github.com/jmodares/follower) mission.

## Run
To run the emulator, use `start_emulator.sh`. It first starts all firmwares, waits for emulator to connect to all firmwares, and then starts all coresponding agents so that they can connect to the emulator.
All command lines and logging options available for [ns3](https://www.nsnam.org/docs/tutorial/html/tweaking.html) and [QGroundControl](https://dev.qgroundcontrol.com/en/command_line_options.html) are also available. The script can be edited to utilize more available options.

Scripts `start_agent.sh i` and `stop_agent.sh i` are also useful to connect and disconnect the mission of agent (drone) `i`.
```
./stop_agent.sh 3
./start_agent.sh 3
```

It should be noted that port `10 * i + 5760` can be used to connect to agent (drone) `i`. 

## Docker
There is a public docker image with UB-ANC Emulator installed and can be used:
```
cd docker
./start.sh
start
```

