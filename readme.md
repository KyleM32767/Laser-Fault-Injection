# Laser-Fault-Injection

This is the code for my Major Qualifying Project on using lasers to inject faults into Xilinx Kintex-7 FPGAs. In this repository is all the HDL and constraint files for programming the FPGA and an automated system that scans and attacks an area on the chip while drawing a map of fault-sensitive locations.



## Directories

Name               | Description
:-----------------:|:------------
`arduino_sketches` | Arduino sketches used to detect faults through the PMOD headers
`img`              | Images used in this readme
`constraints`      | Xilinx constraint files for the target FPGA
`searchandfault`   | Routines to automatically scan, laser, test and reprogram the FPGA to create a map of fault sensitive locations
`tcl_scripts`      | TCL scripts to automatically reprogram the FPGA in the event of a fault
`verilog_modules`  | HDL sources for the target FPGA

## Target FPGA configurations

For every target FPGA configuration, there is a corresponding verilog source, constraint file, and arduino sketch for testing.

Configuration                    | HDL Source            | Constraint File              | Arduino sketch  | FPGA input | FPGA output | Aux control pins
:--------------------------------|:----------------------|:-----------------------------|:----------------|:-----------|:------------|:------------------------------
Literally just a ring oscillator | `just_a_ring_osc.v`   | `just_a_ring_osc_constr.xdc` | N/A             | N/A        | `ja[0]`     | `sw[1]` to enable oscillator
XOR gate with ring oscillator    | `xor_gate_top.v`      | `xor_gate_constr.xdc`        | `xorTester.ino` | `ja[5:0]`  | `ja[6]`     | `jb[0]` to enable oscillator
XOR gate with a clock input      | `xor_gate_noRO_top.v` | `xor_gate__noROconstr.xdc`   | `xorTester.ino` | `ja[4:0]`  | `ja[6]`     | `ja[5]` to enable clock input

## Laser Setup

Before running a fault injection test, the laser must be ready to use.

1) Turn off the target board, close the door, and lock the door with the touch screen. Once the door is locked, turn the laser key. The white, green, and blue lights should be on, and there should be a check mark next to each item, as shown in Figure 1

<img src=img/touchscreen.jpg>

<sup>Figure 1. The touch screen showing the status of the door, XYZ stages, and laser</sup>

2) Using the buttons on the black control panel box, turn on the navigation camera by switching on the LED and moving motor 1 to the in position. Then open the laser by doing the same for motor two, as shown in Figure 2

<img src=img/controlpanelbox.jpg>

<sup>Figure 2. The control panel box, with the navigation camera active and the laser open</sup>

3) Open LUCIE to see the camera feed (if it is not showing, keep restarting LUCIE until it does). Once you have a feed, carefully lower the joystick by twisting the joystick until it is in focus, and find the target location.
	* To find the target location more easily, start with the 2.5x lens, then move up enough to safely change lenses, and repeat with the 20x and/or 50x.

4) **With the FPGA turned off,** open AlphaNov Control Software, and click "connect." After a few seconds, a control panel for the laser will open, as shown in Figure 3. Set a peak current of around 1000mA, a frequency of around 100kHz, and a pulse width of around 200ns. Set "laser activation" to on, and you should now see a laser spot in the camera feed, as shown in Figure 4. If you don't see it, try turning down the LED intensity using the control panel.

<img src=img/laser_control.png>

<sup>Figure 3. The laser control panel, with the relevant settings boxed in red</sup>

<img src=img/spot.png>

<sup>Figure 4. Camera feed showing a laser spot</sup>

5) In LUCIE, click the crosshair icon and adjust the crosshair position by typing coordinates in the text box. The crosshair should be directly over the laser spot, as shown in Figure 5.

<img src=img/aim.png>

<sup>Figure 5. Comparison of bad laser aiming (left) and good laser aiming (right)</sup>

6) Turn off the laser and close AlphaNov Control Software. This is because the automated search and fault won't be able to use the serial port for the laser.


## Running Automated Search And Fault

1) Set up the laser, turn on the FPGA, and program the FPGA.

2) plug each bit of the tester Arduino into the FPGA's PMOD headers and plug the tester board into USB 2 on the inside of the machine, as shown in Figure 6. For more details on which pins to use, refer to the Arduino sketch used in the tester. On the outside of the machine, plug the computer into the corresponding outside USB 2 plug.

<img src=img/test_arduino.jpg>

<sup>Figure 6. The tester Arduino plugged into the FPGA</sup>

3) Open Windows Powershell in the `searchandfault` directory, and run the tester by typing `python testandprogram.py`. It should say "no faults." If it says "error in result," try again.

4) Compile everything using `compile.bat`. This will create an executable in the `searchandfault` folder named `a.exe`. This is the executable that runs the search and fault
	* It's compiled using g++ because that's all I know how to use, and the only drawback is the very very long command to compile it, which is why the batch file exists.
	* The compiler will spit out one warning about deleting arrays and another about redefining macros. Do not worry about them - it's fiiiiiiiiiiiiiiiiine

5) You can run the search and fault test by with the following command
```
./a.exe | tee result/log.txt
```
* This will create a file called `log.txt` in the result folder which contains everything that is displayed in the command window. If you do not want this, you can instead run
```
./a.exe
```

6) You will be prompted to take an image using LUCIE and save it to `searchandfault/result/map.png`. This is the image on which the fault sensetivity map will be drawn. *Be sure to use the 20x lens, as the drawing of the map based on mapping pixels to coordinates, and it assumes 20x zoom.*

7) For maximum precision, switch to 50x lens. Using a properly aimed crosshair, aim the laser on a reference spot. Using MS Paint, identify the pixel coordinates of the location on the map image and type them in.
	* For this step, my go-to location is shown in Figure 7.
	* Once the y-coordinate is entered, the position of the XYZ stages will be taken, and the bounding box will be drawn

<img src=img/ref_spot.png>

<sup>Figure 7. A reference location that is easy to identify on an image</sup>

8) Wait and pray that nobody in the entire building moves for the next 45min or so.