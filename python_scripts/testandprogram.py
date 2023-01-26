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

# open port for gate tester
tester = serial.Serial(port=sys.argv[2], baudrate=115200, timeout=3)
time.sleep(2)

# start test and get result
tester.write(b'b')
result = tester.readline()
print(result)

# report on any faults
nFaults = 0
for i in range(0, len(result) - 2):

	# report a fault if found
	if result[i] == ord('F'):
		nFaults += 1
		print('fault at input', bin(i)[2:])
	
	# there are no other possible characters for faults
	elif result[i] != ord('~'):
		print('error in result')
		exit()

# reprogram FPGA if needed
if nFaults == 0:
	print('no faults')
else:
	print(nFaults, 'FAULTS! reprogramming FPGA...')
	os.system('putty -load "vernam lab" -pw ' + sys.argv[1] + ' -m C:\\Users\\KyleM\\Documents\\MQP\\vivadoscript.txt -t') # something tells me storing the password in plaintext on github is a bad idea
	print('done. verifying...')

	# rerun test to see if it was reprogrammed successfully
	tester.write(b'b')
	result = tester.readline()
	if result.find(ord('F')) == -1:
		print('reprogram success.')
	else:
		print('reprogramming failed... perhaps the LUT is dead?')

tester.close()
