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

Configuration                    | Top-level HDL Source   | Constraint File              | Arduino sketch               | FPGA input             | FPGA output            | Aux control pins
:--------------------------------|:-----------------------|:-----------------------------|:-----------------------------|:-----------------------|:-----------------------|:------------------------------
Literally just a ring oscillator | `just_a_ring_osc.v`    | `just_a_ring_osc_constr.xdc` | N/A                          | N/A                    | `ja[0]`                | `sw[1]` to enable oscillator
XOR gate with ring oscillator    | `xor_gate_top.v`       | `xor_gate_constr.xdc`        | `xorTester.ino`              | `ja[5:0]`              | `ja[6]`                | `jb[0]` to enable oscillator
XOR gate with a clock input      | `xor_gate_noRO_top.v`  | `xor_gate_noRO_constr.xdc`   | `xorTester.ino`              | `ja[4:0]`              | `ja[6]`                | `ja[5]` to enable clock input
Where is this register?          | `whereisthisreg_top.v` | `whereisthisreg_constr.xdc`  | `whereisthisreg_control.ino` | N/A                    | N/A                    | `ja[7:0]` to enable repsective registers, `jb[2]` to enable ring oscillator
Just a few D flip-flops          | `d_flipflop.v`         | `just_a_dff_constr.xdc`      | `dffTester.ino`              | N/A                    | `ja[7:0]` = `led[7:0]` | `sw[7]` as manual D input, `btnd` as write enable
Simple password lock             | `password_top.v`       | `password_constr.xdc`        | `passwordInterface.ino`      | `ja[6:0]` for password | `ja[7]` indicates open | `jb[0]` as enter

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

4) **With the FPGA turned off,** open AlphaNov Control Software, and click "connect." After a few seconds, a control panel for the laser will open, as shown in Figure 3. Set a peak current of around 1000mA, a frequency of around 100kHz, and a pulse width of around 200ns. Set "laser activation" to on, and you should now see a laser spot in the camera feed, as shown in Figure 4. If you don't see it, try turning down the LED intensity using the control panel box.

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

2) Program the Arduino using the relevant tester sketch. Plug each bit of the tester Arduino into the FPGA's PMOD headers and plug the tester board into one of the USB ports on the inside of the machine, as shown in Figure 6. For more details on which pins to use, refer to the Arduino sketch. On the outside of the machine, plug the computer into the corresponding outside USB port.

<img src=img/test_arduino.jpg>

<sup>Figure 6. The tester Arduino plugged into the FPGA</sup>

3) Open the arduino's serial port in Realterm and verify the functionality of the tester. Every tester uses 9600 baud, and there are various commands which all correlate to a single ASCII character. For specific commands, refer to the tester sketch, but generally speaking the following convention is used:
	* `~` will reset
	* `a` will trigger a test
	* `r` will toggle the ring oscillator

4) Set the various parameters for the search defined in macros...
	* Laser pulse width, frequency, and peak current in `pewpewpew.c`
		* From my experience, the highest safe current for a Kintex-7 is 1A or 25%. **Using a higher current may permanently damage the chip if you don't know what you are doing!**
	* Step size in `xyz.h` (be sure to edit both PLUS_ONE and MINUS_ONE)
		* I advise don't going lower than 1um, because that is the width of the laser spot

5) Compile everything using `compile.bat`. This will create an executable in the `searchandfault` folder named `a.exe`. This is the executable that runs the search and fault
	* It's compiled using g++ because that's all I know how to use, and the only drawback is the very very long command to compile it, which is why the batch file exists.
	* The compiler will spit out one warning about deleting arrays and many others about redefining macros. Do not worry about them - it's fiiiiiiiiiiiiiiiiine.

6) You can run the search and fault test by with the following command
```
./a.exe | tee result/log.txt
```
* This will create a file called `log.txt` in the result folder which contains everything that is displayed in the command window. If you do not want this, you can instead run
```
./a.exe
```

7) You will be prompted to take an image using LUCIE and save it to `searchandfault/result/map.png`. This is the image on which the fault sensetivity map will be drawn. 
	* In the relevant python script for testing, be sure that you have the pixel to mm conversion factor for the lens you used for the map image! There are two lines setting `PIXEL_PER_MM`, one for 20X and one for 50X, so be sure to uncomment the right one.
	* The map image does not necessarily have to use the same lens that you use for laser faults, but it must have the same exact orientation as the chip during the test (i.e. don't touch the FPGA after you take the map image)

8) For maximum precision, switch to 50x lens. Using a properly aimed crosshair, aim the laser on a reference spot. Using MS Paint, identify the pixel coordinates of the location on the map image and type them in.
	* For this step, my go-to location is shown in Figure 7.
	* Once the y-coordinate is entered, the position of the XYZ stages will be taken, and the bounding box will be drawn

<img src=img/ref_spot.png>

<sup>Figure 7. A reference location that is easy to identify on an image</sup>

9) Wait and pray that nobody in the entire building moves for the next hour or so.

## Known Issues

* There is an offset between the squares marked on the fault map and the actual spots of the respective faults. In the absence of a better solution, the program takes a screenshot every time there is a fault. For this reason, make sure that the camera feed on LUCIE is visible the whole time.
* Over time, the laser goes out of focus due to who knows what. During an automated search and fault, supervise the camera and manually adjust the focus if needed. *This unfortunately means you have to be there in the lab the whole time,* so be sure to narrow down your search area.
	* For example, searching the entirety of a single logic cell on the Kintex-7 can take upwards of 6 hours! By narrowing the search down to a certain element within the cell, it can be reduced to 90 minutes
* The machine - particularly on the 50X zoom - is *extremely* sensitive to vibrations, and its spot on the second floor next to the elevator makes these vibrations plentiful! My workaround is doing the tests when the building is empty.