# Ultrasonic-AR-parrot-Drone

### By Robert Horvers & Evert Poots
### Ordina Software Development JTech

![alt text](https://imgur.com/SVWl69D)

WARNING: WORK IN PROGRESS! This project was inspired by https://github.com/vdkd888/droneproject whereby the goal is to make the drone more autonomous by utilizing ultrasonic sensors and camera's. With these sensors and utilizing deep learning methodes the drone should be able to fly it's own path without human interference. At the same time the drone will map it's surrounding. The project Hack-A-Drone, https://github.com/roberthorvers/hack-a-drone, will be applied to this project whereby the autonomous drones shall fly as a swarm. 

- Arduino Code adapted from: http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
- Python Code Reworked from:https://gist.github.com/electronut/d5e5f68c610821e311b0

### Contents

- Systems
- Hardware
- Set Up
- Layout
- Installation

### System


### Hardware

- Parrot AR Drone 2.0: (https://www.parrot.com/fr/drones/parrot-ardrone-20-elite-edition)
- Arduino UNO 65139 Development-board ATMega328 (Or really any other Arduino board)
- Four HC-SR04 Ultrasonic Sensors: (https://www.sparkfun.com/products/13959)
- Logic Level Converter Bi-Directional
- USB drive

### Set Up


### Layout
![equation](http://www.sciweavers.org/tex2img.php?eq=1%2Bsin%28mc%5E2%29&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=)

### Installation

#### Downloads
Download the following
- The latest node.js and install (https://nodejs.org/en/).
- The latest AR-drone node (https://github.com/felixge/node-ar-drone).
- The latest node serial-port (https://github.com/EmergingTechnologyAdvisors/node-serialport).

#### Uploading files to the drone
For this part it is necessary to use a Linux OS. For this project we worked in Ubuntu 16.04.

1. Upload the AR-drone, node and serial-port on the USB driver.
2. Put the usb in on the drone. The usb port is located near the battery.
3. Power up the drone and connect to the drone wifi.
4. Open the terminal and enter the drone with; `telnet 192.168.1.1`.
5. Navigate to the video file; `cd /data/video` (The reason being is that this is where the drone sents it's output, or something. We arn't sure)'.
6. Copy the node the the video file; `cp usb0/node .` (it might be usb or usb1)
7. `chmod +x node`
8. `mkdir node_modules`
9. `cp -r usb/node-serialport/ node_modules/`
10. Copy the AR-drone paste the folder in `cd data/video` the same way you did node
11. Upload the Arduino script onto the Arduino.

### Start the drone

- Power up the drone
- Connect to the drone wifi
- Open the terminal and enter the drone; `telnet 192.168.1.1`.
- navigate to the video file; `cd /data/video`.
- Execute the node `./node` (example: `./node Hover.js`).
- Pray it won't sing Daisy Bell.
