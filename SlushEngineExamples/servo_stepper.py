#This code has not been tested. It is a mystery as to what thee GPIO and pwm is and what the values are. There is also no pin numbered 8 that we have access to. TO be tested in the futue

import Slush
import RPi.GPIO as GPIO
import time

b = Slush.sBoard()

axis1 = Slush.Motor(0)
axis1.resetDev()
axis1.setCurrent(100, 100, 100, 100)
axis1.setMaxSpeed(100)
axis1.setMicroSteps(16)

GPIO.setmode(GPIO.BCM)
GPIO.setup(8, GPIO.OUT)
pwm = GPIO.PWM(8, 100)

while 1:
#	axis1.move(-1000)
	pwm.start(6)
	#print(pwm.read())
	time.sleep(3)
#	axis1.move(1000)
	pwm.start(16)
	time.sleep(3)
