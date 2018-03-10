#!/usr/bin/python

# impot libraries
import RPi.GPIO as GPIO
import time

# declare hardware pins
ledPin = 18 
butPin = 17 

# set some GPIO stuff
GPIO.setmode(GPIO.BCM) 
GPIO.setup(ledPin, GPIO.OUT) 
GPIO.setup(butPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)  

# beginning state
GPIO.output(ledPin, GPIO.LOW)

print("Press CTRL+C to exit")
try:
    	while 1:
		fo = open("../ledStat", "r+"); 	# open the ledStat folder for reading/ writing from the beginning of the file
		stat = fo.read(1) 		# read the first character

        	if not GPIO.input(butPin): 	# read the input of the button
			fo.seek(0, 0)		# if the button is pressed set the cursor at the beginning	
			fo.write("0")		# of the file to set the character that is present at that 
			fo.seek(0, 0)		# moment to 0 (LED off)

		if stat == '1':			# if the file contains a '1' turn the LED on.
			GPIO.output(ledPin, GPIO.HIGH)
		else:				# if the file contains anything else turn the LED off.
			GPIO.output(ledPin, GPIO.LOW)
		
		fo.close()	# close the file

except KeyboardInterrupt: 	# when CTRL+C is pressed, exit cleanly
    	GPIO.cleanup() 
	fo.close() 
