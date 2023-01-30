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

PI_HOST     = 'pi@fe80::ae16:eb8a:4dee:14df'
VIVADO_HOST = 'dev@130.215.23.103' # maybe best to leave this hidden from github

# open port for gate tester
tester = serial.Serial(port=sys.argv[1], baudrate=115200, timeout=3)
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
	print(nFaults, 'FAULTS! reprogramming FPGA...') # full path to vivado is needed due to path issues over ssh
	os.system('ssh ' + PI_HOST + ' ssh ' + VIVADO_HOST + ' /tools/Xilinx/Vivado/2022.2/bin/vivado -mode batch -source /home/dev/kyle/Laser-Fault-Injection/tcl_scripts/autoprogram.tcl')
	print('done. verifying...')

	# rerun test to see if it was reprogrammed successfully
	tester.write(b'b')
	result = tester.readline()
	if result.find(ord('F')) == -1:
		print('reprogram success.')
	else:
		print('reprogramming failed... perhaps the LUT is dead?')

tester.close()
