'''
	testandprogram.py

	automatically runs the XOR gate test and reprograms the FPGA in the event of a fault

	Author: Kyle Mitard
	Created 22 Jan 2023
'''

import serial
import os
import time
import sys
import cv2
from PIL import ImageGrab

# SSH hosts
PI_HOST     = 'pi@fe80::ae16:eb8a:4dee:14df'
VIVADO_HOST = 'dev@130.215.23.103'

# file onto which the fault sensitivity map is drawn
MAP_IMAGE_FILE = "result/map.png"

# pixel to irl size conversion
# there is a minus sign because the left/up is positive IRL, but negative in image
PIXEL_PER_MM = -1/0.000752571202531646

# width of fault spot
SPOT_SIZE = 4

# fault spot colors
COLOR_0_FAULT     = (255, 0,   0) # red
COLOR_1_FAULT     = (0,   255, 0) # green
COLOR_BOTH_FAULTS = (255, 255, 0) # yellow 

# fault spot opacity
OPACITY = 0.3

# reference point for mapping motor position to image
with open('result/refpoint.txt', 'r') as f:
	REF_X_IMG = float(f.readline()) # image coordinates of a point
	REF_Y_IMG = float(f.readline())
	REF_X_IRL = float(f.readline()) # IRL coordinates corresponding to the same point
	REF_Y_IRL = float(f.readline())

# IRL coordinates of current spot
irlX = float(sys.argv[2])
irlY = float(sys.argv[3])

# open port for gate tester
tester = serial.Serial(port=sys.argv[1], baudrate=115200, timeout=3)
time.sleep(2)

# start test and get result
tester.write(b'c')
result = tester.readline()
print(result)


# search result for faults
nFaults = [0, 0]
for i in range(0, len(result) - 2):

	# record a fault if found
	if result[i] == ord('0'):
		nFaults[0] += 1
	elif result[i] == ord('1'):
		nFaults[1] += 1

	# there are no other possible characters for faults
	elif result[i] != ord('~'):
		print('error in result')
		exit()


# if there's a fault, reprogram FPGA and log location
if nFaults[0] == 0 and nFaults[1] == 0:
	print('no faults')
else:

	# report the faults
	if (nFaults[0] == 0):
		color = COLOR_1_FAULT
		print(nFaults[1], 'one-to-zero FAULTS! reprogramming FPGA...')
	elif (nFaults[1] == 0):
		print(nFaults[0], 'zero-to-one FAULTS! reprogramming FPGA...')
		color = COLOR_0_FAULT
	else:
		print(nFaults[0], 'zero-to-one FAULTS and', nFaults[1], 'one-to-zero FAULTS! reprogramming FPGA...')
		color = COLOR_BOTH_FAULTS


	# take a screenshot of lucie
	ss_region = (0, 0, 1920, 1080)
	ss_img = ImageGrab.grab(ss_region)
	ss_img.save("result/xorFault" + time.strftime("%Y%m%d%H%M%S", time.gmtime()) + ".png")


	# determine image location using reference point
	imgX = int((irlX - REF_X_IRL) * PIXEL_PER_MM + REF_X_IMG)
	imgY = int((irlY - REF_Y_IRL) * PIXEL_PER_MM + REF_Y_IMG)


	# edit the map image with a spot of the fault
	map_img = cv2.imread(MAP_IMAGE_FILE)
	overlay = map_img.copy()
	cv2.rectangle(overlay, (imgX-SPOT_SIZE//2,imgY-SPOT_SIZE//2), (imgX+SPOT_SIZE//2,imgY+SPOT_SIZE//2), color, -1)
	n = cv2.addWeighted(overlay, OPACITY, map_img, 1-OPACITY, 0)
	cv2.imwrite(MAP_IMAGE_FILE, n)


	# do a double nested ssh to run vivado without connecting to the internet
	# full path to vivado is needed due to path issues over ssh
	os.system('ssh ' + PI_HOST + ' ssh ' + VIVADO_HOST + ' /tools/Xilinx/Vivado/2022.2/bin/vivado -mode batch -source /home/dev/kyle/Laser-Fault-Injection/tcl_scripts/autoprogram.tcl')
	print('done. verifying...')


	# rerun test to see if it was reprogrammed successfully
	tester.write(b'b')
	result = tester.readline()
	if result.find(ord('F')) == -1:
		print('reprogram success.')
	else:
		print('reprogramming failed... perhaps the LUT is dead?')


# close serial port
tester.close()
