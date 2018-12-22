# ////////////////////////////////////////////////////////////////
# //                     IMPORT STATEMENTS                      //
# ////////////////////////////////////////////////////////////////

import math
import sys
import argparse
from time import sleep

#import RPi.GPIO as GPIO 
sys.path.insert(0, "/home/pi/Documents/RaspberryPiCommon/Libraries/Hardware")
import Stepper
import SlushEngine
sys.path.insert(0, "/home/pi/Documents/RaspberryPiCommon/Libraries/Hardware/RPiMIB")
import RPiMIB

MAX_SPEED = 10000

slushEngine = SlushEngine.SlushEngine()

parser = argparse.ArgumentParser()
parser.add_argument("--port", type=int, help="Enter the number of ports to test", nargs='?', default=-1)
parser.add_argument("--portCount", type=int, help="Enter the number of ports to test", nargs='?', default=1)
args = parser.parse_args()

def pwmTest(portNumber):
    print("######## Send PWM test 4 speeds (or positions) on Port " + str(portNumber))
    RPiMIB.openSPI()
    for speed in range(500, 3000, 500):
        print("# Speed = " + str(speed))
        RPiMIB.sendPWM(portNumber, speed)
        sleep(2)
        RPiMIB.sendPWM(portNumber, 0)
        sleep(0.5)
    RPiMIB.closeSPI()
    
def pwmAndStepperTest(pwmPort, stepperPort):
    print("###### PWM(port = " + str(pwmPort) + ") and Stepper(port = " + str(stepperPort) + ") test")
    stepper = Stepper.Stepper(port = stepperPort, speed = MAX_SPEED)
    print("Stepper Run Until Stop for 2 seconds. NOTE: PWM should not be running.")
    stepper.runUntilStop(1, 500)
    sleep(2)
    stepper.stop()
    RPiMIB.openSPI()
    print("# PWM 4000 for 2 seconds")
    RPiMIB.sendPWM(pwmPort, 1000)
    sleep(2)
    print("# Stop PWM")
    RPiMIB.sendPWM(pwmPort, 0)
    RPiMIB.closeSPI()
    sleep(1)

def homeTest(portNumber):
    stepper = Stepper.Stepper(port = portNumber, speed = MAX_SPEED)

    #### Homing Test
    print("######## Test Stepper on port " + str(portNumber))
    print("######## Stepper HOMING in the Clockwise direction.")
    print("Press switch to stop motor on port " + str(portNumber))
    stepper.home(0)
    sleep(0.25)
    stepper.reset()
    print("######## Stepper HOMING in the Counter Clockwise direction.")
    print("Press switch to stop motor on port " + str(portNumber))
    stepper.home(1)
    stepper.stop()

def relativeMoveTest(portNumber, value):
    print("######## Test Stepper on port " + str(portNumber) + " with value = " + str(value))
    stepper = Stepper.Stepper(port = portNumber, speed = MAX_SPEED)
    print("######## Relative move Counter Clockwise.")
    sleep(1)
    stepper.relativeMove(value)
    print("######## Relative move Clockwise.")
    sleep(1)
    stepper.relativeMove(-value)
    sleep(1)
    stepper.stop()

def speedTest(portNumber):
    print("######## Test Stepper on port " + str(portNumber))
    print("######## Increase speed in 5 increaments")
    stepper = Stepper.Stepper(port = portNumber, speed = MAX_SPEED)
    for speed in range(200, 1200, 200):
        print("# Speed = " + str(speed))
        stepper.runUntilStop(1, speed)
        sleep(2)
        stepper.stop()

def setGPIOValue(value):
    result = ["high", "low"]
    if (value == 0):
        result = ["low", "high"]

    for j in range(0, 2):
        label = ("A", "B")[j == 1]
        for i in range(0, 8):
            slushEngine.setGPIOState(j, i, value)
            if (slushEngine.getGPIOState(j, i) != 1):
                printError(label + str(i) + " should be " + result[0] + " but is " + result[1])
            sleep(0.25)

def gpioInputTest():
    print("######## Test A and B output GPIO")
    slushEngine = SlushEngine.SlushEngine()
    setGPIOValue(0)
    setGPIOValue(1)

def valueWithinRange(value1, value2, delta):
    if (value2 - value1 > -delta):
        if (value2 - value1 < delta):
            return True
    return False

def encoderTest():
    encoder1 = readEncoder(0)
    stepper = Stepper.Stepper(port = 0, speed = MAX_SPEED)
    stepper.relativeMove(-1.0)
#    stepper.relativeMove(-25.5)
    stepper.hardStop()
    stepper.free()
    encoder2 = readEncoder(0)
    print(hex(encoder2))
    print(encoder2-encoder1)
    if (valueWithinRange(encoder2, encoder1, 2) == False):
        printError("Encoder Test Failed!")


def readEncoder(index):
    RPiMIB.openSPI()
    encoderValue = RPiMIB.readEncoder(index)
    RPiMIB.closeSPI()
    return(encoderValue)


def encoderStopTest(portNumber, encoder, value):
    print("######## Encoder Stop Test with value: " + hex(value) + " ########")
    stepper = Stepper.Stepper(port = portNumber, speed = 10)
    stepper.reset()

    RPiMIB.openSPI()
    RPiMIB.setEncoderStopValue(encoder, value, 0x50)
    RPiMIB.closeSPI()
    stepper.home(1)
    RPiMIB.openSPI()
    RPiMIB.setEncoderStopValue(encoder, 0xffff, 0x00)
    RPiMIB.closeSPI()
    stepper.relativeMove(100)
    sleep(1)
    stepper.stop()
    stepper.reset()
    


def printError(message):
    print("####################################################### Error: " + message)

########################### Tests #########################################

#homeTest(0)

encoderStopTest(0, 1, 0xe0f)
#print(hex(readEncoder(0)));
#for i in range(0,5):
#    encoderTest()

#pwmAndStepperTest(4, 0)
#
#for port in range(4, 6, 1):
#    pwmTest(port)
#
#for portNumber in range (0, args.portCount):
#    homeTest(portNumber)
#    relativeMoveTest(portNumber, 500)
#    speedTest(portNumber)
#
#for i in range(0,10):
#    encoderTest()
#
#gpioInputTest()
#
#for pwmPort in range(4, 6, 1):
#    RPiMIB.openSPI()
#    RPiMIB.sendPWM(pwmPort, 0)
#    RPiMIB.closeSPI()

