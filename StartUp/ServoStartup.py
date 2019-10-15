#!/usr/bin/python3

# ////////////////////////////////////////////////////////////////
# //                     IMPORT STATEMENTS                      //
# ////////////////////////////////////////////////////////////////

import spidev
import os
from time import sleep
import RPi.GPIO as GPIO
from pidev.stepper import stepper
from Slush.Devices import L6470Registers
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus
spi = spidev.SpiDev()


# For this example we will use the RPiMIB to talk create the PWM signals to talk to Servo Motors motor controllers.
#
# The RPiMIB has two PWM outputs, which will be sufficient for this example. If we need more than 2 PWM outputs we
# typically use

