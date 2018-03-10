#!/usr/bin/python

import RPi.GPIO as GPIO
import time

ledPin = 18 
butPin = 17 

GPIO.setmode(GPIO.BCM) 
GPIO.setup(ledPin, GPIO.OUT) 
GPIO.setup(butPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)  

GPIO.output(ledPin, GPIO.LOW)

print("Press CTRL+C to exit")
try:
    	while 1:
		fo = open("../ledStat", "r+");
		stat = fo.read(1)

        	if not GPIO.input(butPin): 
			fo.seek(0, 0)
			fo.write("0")
			fo.seek(0, 0)

		if stat == '1':
			GPIO.output(ledPin, GPIO.HIGH)
		else:
			GPIO.output(ledPin, GPIO.LOW)
		
		fo.close()

except KeyboardInterrupt: 
    	GPIO.cleanup() 
	fo.close() 
