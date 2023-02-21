'''
	getFlippedRegs.py

	automatically checks the DFF tester for any flipped registers, then resets it

	Author: Kyle Mitard
	Created 20 Feb 2023
'''

import serial
import os
import time
import sys
import cv2
from PIL import ImageGrab


# ======================================================================================================
# CONSTANTS
# ======================================================================================================

# file onto which the fault sensitivity map is drawn
MAP_IMAGE_FILE = "result/map.png"

# pixel to irl size conversion - uncomment the one for whatever lens was used for the map imahe
# there is a minus sign because the left/up is positive IRL, but negative in image
# PIXEL_PER_MM = -1/0.000752571202531646 # 20X
PIXEL_PER_MM = -3326.315789473684      # 50X

# width of fault spot
SPOT_SIZE = 4

# fault spot opacity
OPACITY = 0.3

# fault spot colors - one for each register
COLOR_REG0 = (0,   0,   0  ) # black
COLOR_REG1 = (0,   0,   255) # red 
COLOR_REG2 = (0,   255, 0  ) # green
COLOR_REG3 = (0,   255, 255) # yellow
COLOR_REG4 = (255, 0,   0  ) # blue
COLOR_REG5 = (255, 0,   255) # purple
COLOR_REG6 = (255, 255, 0  ) # teal
COLOR_REG7 = (255, 255, 255) # white
colors = [COLOR_REG0, COLOR_REG1, COLOR_REG2, COLOR_REG3, COLOR_REG4, COLOR_REG5, COLOR_REG6, COLOR_REG7]

# ======================================================================================================
# MAIN PROCESSING
# ======================================================================================================

# reference point for mapping motor position to image
with open('result/refpoint.txt', 'r') as f:
	REF_X_IMG = float(f.readline()) # image coordinates of a point
	REF_Y_IMG = float(f.readline())
	REF_X_IRL = float(f.readline()) # IRL coordinates corresponding to the same point
	REF_Y_IRL = float(f.readline())

# IRL coordinates of current spot from command-line args
irlX = float(sys.argv[2])
irlY = float(sys.argv[3])

# open port for gate tester
tester = serial.Serial(port=sys.argv[1], baudrate=9600, timeout=3)
time.sleep(2)

# start test and get result
tester.write(b'a')
result = tester.readline()
print(result)


# search result for faults
fault = -1
for i in range(0, len(result) - 2):

	# record a fault if found
	if result[i] == ord('1'):
		fault = i

	# there are no other possible characters for faults
	elif result[i] != ord('0'):
		print('error in result')
		exit()


# if there's a fault, log location
if fault == -1:
	print('no faults')
else:

	# report the faults
	print("flipped register " + str(fault) + "!")

	# take a screenshot of lucie
	ss_region = (0, 0, 1920, 1080)
	ss_img = ImageGrab.grab(ss_region)
	ss_img.save("result/flippedReg" + str(fault) + time.strftime("%Y%m%d%H%M%S", time.gmtime()) + ".png")

	# determine image location using reference point
	imgX = int((irlX - REF_X_IRL) * PIXEL_PER_MM + REF_X_IMG)
	imgY = int((irlY - REF_Y_IRL) * PIXEL_PER_MM + REF_Y_IMG)

	# edit the map image with a spot of the fault
	map_img = cv2.imread(MAP_IMAGE_FILE)
	overlay = map_img.copy()
	cv2.rectangle(overlay, (imgX-SPOT_SIZE//2,imgY-SPOT_SIZE//2), (imgX+SPOT_SIZE//2,imgY+SPOT_SIZE//2), colors[fault], -1)
	n = cv2.addWeighted(overlay, OPACITY, map_img, 1-OPACITY, 0)
	cv2.imwrite(MAP_IMAGE_FILE, n)

	# reset and verify that it was reset
	tester.write(b'~')
	result = tester.readline()
	if result == b'reset\r\n':
		print('reset success.')
	else:
		print("reset failed...")
		os.system("pause")


# close serial port
tester.close()
