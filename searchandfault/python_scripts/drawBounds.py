'''
    drawBounds.py

    draws a box bound by the IRL coordinates given in command line arguments

    Author: Kyle Mitard
    Created 03 Feb 2023
'''

import cv2
from sys import argv

# file onto which the fault sensitivity map is drawn
MAP_IMAGE_FILE = "result/map.png"

# pixel to irl size conversion
# there is a minus sign because the left/up is positive IRL, but negative in image
PIXEL_PER_MM = -1/0.000752571202531646

# reference point for mapping laser position to image
with open('result/refpoint.txt', 'r') as f:
	REF_X_IMG = float(f.readline()) # image coordinates of a point
	REF_Y_IMG = float(f.readline())
	REF_X_IRL = float(f.readline()) # IRL coordinates corresponding to the same point
	REF_Y_IRL = float(f.readline())

# IRL coordinates of corners
irlX1 = float(argv[1])
irlY1 = float(argv[2])
irlX2 = float(argv[3])
irlY2 = float(argv[4])

# determine image location using reference point
imgX1 = int((irlX1 - REF_X_IRL) * PIXEL_PER_MM + REF_X_IMG)
imgY1 = int((irlY1 - REF_Y_IRL) * PIXEL_PER_MM + REF_Y_IMG)
imgX2 = int((irlX2 - REF_X_IRL) * PIXEL_PER_MM + REF_X_IMG)
imgY2 = int((irlY2 - REF_Y_IRL) * PIXEL_PER_MM + REF_Y_IMG)

map_img = cv2.imread(MAP_IMAGE_FILE)
cv2.rectangle(map_img, (imgX1,imgY1), (imgX2,imgY2), (0,0,0), 1)
cv2.imwrite(MAP_IMAGE_FILE, map_img)