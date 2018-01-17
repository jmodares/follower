Copyright © 2015 - 2018 Jalil Modares

This program was part of my Ph.D. Dissertation research in the Department of Electrical Engineering at the University at Buffalo. I worked in UB's Multimedia Communications and Systems Laboratory with my Ph.D. adviser, [Prof. Nicholas Mastronarde](http://www.eng.buffalo.edu/~nmastron).

If you use this program for your work/research, please cite:
[J. Modares, N. Mastronarde, K. Dantu, "UB-ANC Emulator: An Emulation Framework for Multi-agent Drone Networks"](https://doi.org/10.1109/SIMPAR.2016.7862404).

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

# follower
## The leader-follower mission using UB-ANC Agent template
The follower mission is an example that shows how to use UB-ANC Agent to develop new mission. In this mission, MAV `i + 1` follows 10 meters behind MAV `i`. This is accomplished by MAV `i` sending its GPS location to MAV `i + 1` every 100 ms using a 74 byte packet.
