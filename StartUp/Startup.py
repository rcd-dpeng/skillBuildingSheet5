#!/usr/bin/python3

# ////////////////////////////////////////////////////////////////
# //                     IMPORT STATEMENTS                      //
# ////////////////////////////////////////////////////////////////

import spidev
import os
from time import sleep
import RPi.GPIO as GPIO
from pidev.stepper import stepper
spi = spidev.SpiDev()

# Init a 200 steps per revolution stepper on Port 0
s0 = stepper(port=0, micro_steps=32, hold_current=20, run_current=20, accel_current=20, deaccel_current=20,
             steps_per_unit=200, speed=8)

# Init a 1036 steps per revolution stepper on Port 1 - this is for a stepper with a 5.18:1 planetary transmission
# https://www.omc-stepperonline.com/economy-planetary-gearbox/nema-17-stepper-motor-bipolar-l48mm-w-gear-raio-51-planetary-gearbox-17hs19-1684s-pg5.html?mfp=161-motor-nema-size%5BNema%2017%5D
s1 = stepper(port=1, micro_steps=32, hold_current=20, run_current=20, accel_current=20, deaccel_current=20,
             steps_per_unit=1038, speed=8)

# Init a 200 steps per revolution stepper on Port 2 with a lead screw that moves 8mm per revolution
# (200 steps/1 rev)* (1 rev/8 mm) which simplifies to 25 steps/mm giving us 25 for our steps_per_unit value
# https://www.pololu.com/product/2268
s2 = stepper(port=2, micro_steps=32, hold_current=20, run_current=20, accel_current=20, deaccel_current=20,
             steps_per_unit=25, speed=8)

# get current position and print it to the screen
s0.get_position_in_units()
# this tells us that the startup position is currently setup as the "home" position

# move stepper connected to port 0, 5 rotations clockwise
s0.start_relative_move(5)

# get current position and print it to the screen
s0.get_position_in_units()
# note the current position is 5 units - in this case 5 revolutions away from home

# move stepper connected to port 0, 5 rotations counter-clockwise
s0.start_relative_move(-5)

# get current position and print it to the screen
s0.get_position_in_units()
# note we are now back at "home"

# move stepper connected to port 0, 10 rotations counter-clockwise
s0.relative_move(-10)

# get current position and print it to the screen
s0.get_position_in_units()
# note we -10 rotations from "home"
# There is another way to get back to home regardless of where we are

# Tell the motor to go home and it will go home.
s0.goHome()

# we can also set the home position
# move stepper connected to port 0, 5 rotations counter-clockwise
s0.start_relative_move(-5)
s0.get_position_in_units()
s0.set_as_home()
s0.get_position_in_units()
# notice we have set the current position as home

# Notice how it is hard to turn the stepper shaft right now?
# This is because by default the SlushEngine leaves the stepper motor stalled or ON so it could hold something
# mechanical in this position. This is good but it consumes a lot of power, and the motor can get quite hot.
# so it is best to turn off or free the motor when we dont need it to be held in its current position.
s0.free
# Frees the motor - we can also free all the motors with one command with
s0.free_all()

# we can run a stepper until it detects a input like a switch or sensor to set the home position
# here the arguments are direction 0 or 1 and steps per second - note steps here does not account for microsteps
# so if we are using 32 micro steps and a standard 200 steps per revolution stepper to get 1 rev / sec
# 32 microsteps * 200 steps / revolution * 1 revolution / second = 6400 steps / second
s0.go_until_press(0, 6400)
# this function will reset the home position to the location that the switch was activated.


# we can stop the stepper at any point in its motion by issuing the following command
s0.softStop()
# softStop() allows the motor to correctly de-accelerate
s0.hard_stop()
# hard_stop() stops immediately, does not allow the motor to de-accelerate first.
# or similarly
s0.stop()
# which is the same as hard_stop

# sometimes, for example on a system that has continuous rotary motion - it is best to home in a specific direction.
# for example if you are running around a circular track, it may be quickest to get back to the starting point or home
# either by continuing on in the same direction, or by turing around sand going back.
s0.goToDir(0, 100)
# parameter direction 0 makes the value returned in get_position get smaller for example 100 -> 80
# while parameter direction 1 makes the value returned in get_position get larger for example -100 -> -80

s1.relative_move(1)
s2.relative_move()


# to deallocate the RPi resources that are attached to this we need to run the following commands so that the next time we want to connect a stepper to one of the ports they are free.
spi.close()
GPIO.cleanup()
# the next command will reboot the system
os.system("sudo reboot")
# alternatively we can shutdown the system with
os.system("sudo shutdown now")
