<div align="center">
  <h1>stepper-motor-controller</h1>
	<blockquote>
		<p><i>Controlling multiple stepper motors with A4988 stepper motor drivers.</i></p>
		<p><b>The inspiration for this piece of software arose from a personal project regarding my [Rubik's Cube solver](https://github.com/KacperBazan/RubiksCube). The code isn't particularly complex, but it is my first attempt at using the PlatformIO extension in Visual Studio Code to maintain my Arduino projects.</b></p>
		<img src=https://img.shields.io/badge/Build-Working-brightgreen> <img src=https://img.shields.io/badge/License-MIT-yellow>
		<img src=https://img.shields.io/badge/Progress-Incomplete-red>
	</blockquote>
</div>

- Feb/28/2021: Code only includes personal definitions of one motor.

## Images
![alt text](No pictures just yet)

## Credits
- **[DroneBot Workshop](https://www.youtube.com/channel/UCzml9bXoEM0itbcE96CB03w)** - Included incredibly detailed tutorials on the ESP32 board, stepper motor functionality, and setting up the Visual Studio Code coding environment. Great stepping stone for beginner Mechatronics.

- **[How To Mechatronics](https://www.youtube.com/channel/UCmkP178NasnhR3TWQyyP4Gw)** - Another YouTuber who gave beginner friendly descriptions of the A4988 driver chip.

The three main videos that assisted in my learning are the [Stepper Motor explanations](https://www.youtube.com/watch?v=0qwrnUeSpYQ&t=1261s), the [introduction to ESP32 boards](https://www.youtube.com/watch?v=xPlN_Tk3VLQ&t=855s), and the [introduction to the PlatformIO coding environment](https://www.youtube.com/watch?v=JmvMvIphMnY).

## Materials

To build a similar setup to experiment on stepper motors you will need the following materials:
| Item | Amount |
| ------------- | ------------- |
| Bipolar/ Unipolar Stepper Motor| 1 |
| A4988 Stepper Motor Driver | 1 per stepper motor |
| 47µF or Greater Capacitor | 1 per stepper motor |
| ESP32 Board (or any other microcontroller) | 1 |
| Micro-USB Cable (depends on microcontroller)| 1 |
| Push Buttons | 2 |
| LED Light | 1 |
| Breadboard | 2 (Depending on size)|
| 220 Ohm Resistor | 3 |
| 8-35V External Power Supply | 1 |

## Controls and Functions

| Input<sup>1</sup>  | Function |
| ------------- | ------------- |
| Button 1  | Toggles Enable Pins (Controls Voltage Sent to Motors) |
| Button 2  | Increments Move Counter  |
>
<sup>1</sup> To be changed in the future. Can be switched within code.

## Installation
1. If you want to download the entire repository, click on the green box and download the zip file. If you don't, skip to step 3.
2. Unzip the zip file.
3. Locate the `src` folder within the repository. 
4. Locate the `stepper-motor-controller.cpp` file.
5. Either copy and paste the contents of the file into your own program, or rename the file extension from `.cpp` to `.ino` to allow the Arduino IDE to directly open it (if downloaded).
6. If using **[PlatformIO](https://www.youtube.com/watch?v=JmvMvIphMnY)**, you may again copy and paste the contents into a seperate project, or open this folder directly.

## Licensing
*Copyright © 2020 Kacper Bazan* - Email: **bazankacper25@gmail.com**

*Distributed under the [MIT](https://github.com/FAR-Lab/RobotArmArduinoAnimation/blob/master/LICENSE) license*
