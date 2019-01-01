# ////////////////////////////////////////////////////////////////
# //                     IMPORT STATEMENTS                      //
# ////////////////////////////////////////////////////////////////

import math
import sys
import spidev
import argparse
import time
from time import sleep
from datetime import datetime
import random

import RPi.GPIO as GPIO 
sys.path.insert(0, "/home/pi/GitHub/RaspberryPiCommon/pidev")
import stepper
import RPiMIB
import Slush

#from pidev import RPiMIB
#from pidev import slush_manager

#sys.path.insert(0, "/home/pi/Documents/RaspberryPiCommon/Libraries/Hardware/RPiMIB")
#sys.path.insert(0, "Libraries/Hardware/RPiMIB")
#import RPiMIB

MAX_SPEED = 50
CLOCKWISE = 0
COUNTERCLOCKWISE = 1

DIRECTIONS = ["CLOCKWISE", "COUNTERCLOCKWISE"]

parser = argparse.ArgumentParser()
parser.add_argument("-motor", type=int, help="Enter the motor to test", nargs='?', default = -1)
parser.add_argument("-motorCount", type=int, help="Enter the number of motors to test", nargs='?', default = 4)
parser.add_argument("-verbose", type=bool, help="Print verbose messages", nargs='?', default = False)
args = parser.parse_args()

if (args.motor != -1):
    args.motorCount = 0

def homeTest(motorNumber):
    printTitle("Home Test motor " + str(motorNumber))
    motor = stepper.stepper(port = motorNumber, speed = MAX_SPEED/2, micro_steps = 2)
    motor.resetDev()
        
    moveOffSwitch(motor, COUNTERCLOCKWISE)
    
    ### Move motor to random position
    random.seed(datetime.now())
    randPosition = random.randint(100, 1000)
    motor.go_to_position(randPosition)
    
    debug("Stepper HOMING in the Clockwise direction.")
    moveOffSwitch(motor, COUNTERCLOCKWISE)
    motor.home(COUNTERCLOCKWISE)

    port, channel = encoderInfo(motorNumber)
    homePosition = readEncoder(port, channel)
    debug("Home Position: " + hex(homePosition))
    
    debug("Stepper HOMING in the Counter Clockwise direction.")
    motor.run(CLOCKWISE, MAX_SPEED*4)
    sleep(1)
    motor.stop()
    motor.goHome()
    sleep(0.75)

    lastPosition = readEncoder(port, channel)
    debug("Last Position: " + hex(lastPosition))
    debug("Delta Position: " + hex(motorPositionDelta(homePosition, lastPosition)))
    assertTrue(assertEqualsWithDelta(homePosition, lastPosition, 0xf),
               "Home Test. Encoder value is not at the home position.")
    motor.stop()
    motor.free()

def speedTest(motorNumber):
    printTitle("Speed Test motor " + str(motorNumber))
    debug("Increase speed in 5 increaments")
    motor = stepper.stepper(port = motorNumber, speed = MAX_SPEED)
    motor.set_speed(3000)

    for speed in range(200, 1200, 200):
        debug("Speed = " + str(speed))
        motor.run(1, speed)
        sleep(1)
        assertTrue(testSwitch(motor), "speedTest motor " + str(motorNumber))
        motor.stop()
        motor.free()
        
def gpioInputTest():
    printTitle("GPIO Test A and B output")
    setGPIOValue(True)
    sleep(0.1)
    checkGPIOValue(True)
    setGPIOValue(False)
    sleep(0.1)
    checkGPIOValue(False)

def pwmTest(port, channel):
    printTitle("# Send PWM test 4 speeds (or positions) on Port " + str(port) + " and channel " + str(channel))
    RPiMIB.open_spi()
    for speed in range(500, 3000, 500):
        debug("Speed = " + str(speed))
        RPiMIB.write_pwm(port, "period", speed)
        sleep(2)
        debug(RPiMIB.read_spi(port, channel))
        RPiMIB.write_pwm(port, "period", 0)
        sleep(0.5)
    RPiMIB.close_spi()

def encoderTest(motorNumber):
    port, channel = encoderInfo(motorNumber)
    portChannel = motorEncoderMessage(motorNumber, port, channel)
    
    printTitle("Encoder Test " + portChannel)
    encoder1 = readEncoder(port, channel)
              
    motor = stepper.stepper(port = motorNumber, speed = MAX_SPEED)
    motor.relative_move(-1.0)

    if (encoder1 == 0xffff):
        assertTrue(False, "Encoder " + portChannel + " not connected.")
        return
    
    motor.hardStop()
    motor.free()

    encoder2 = readEncoder(port, channel)
    result = motorPositionDelta(encoder1, encoder2)

    debug("Encoder1: " + hex(encoder1) + " Encoder2: " + hex(encoder2) + " Difference: " + hex(result))
    
    # Adjust for the rolling over of the encoder
    result = motorPositionDelta(encoder1, encoder2)

    assertTrue(assertEqualsWithDelta(0xa0, result, 0xf),
               "Encoder Test " + portChannel + " Failed! Out of range (difference should be 0x9f)")

def encoderTriggerTest(motorNumber, value):
    port, channel = encoderInfo(motorNumber)   
    portChannel = motorEncoderMessage(motorNumber, port, channel)
    printTitle("Encoder Trigger Test with value: " + hex(value))
    
    motor = stepper.stepper(port = motorNumber, speed = 10)
    motor.relative_move(1)
    
    RPiMIB.open_spi()
    RPiMIB.set_encoder_trigger(port, channel, value)
    RPiMIB.close_spi()

    motor.relative_move(50)
    debug("Encoder value: " + hex(readEncoder(port, channel)))
    result = readEncoder(port, channel)
    
    assertTrue(assertEqualsWithDelta(value, result, 0xf),
               "Encoder Trigger Test " + portChannel + ". Out of range")

    RPiMIB.open_spi()
    RPiMIB.set_encoder_trigger(port, channel, 0xffff)
    RPiMIB.close_spi()
    
    motor.stop()
    motor.free()
    motor.resetDev()

def relativeMoveTest(motorNumber, value):
    printTitle("Relative Move Test motor " + str(motorNumber) + " with value = " + str(value))
    motor = stepper.stepper(port = motorNumber, speed = MAX_SPEED)
    debug("Relative move Counter Clockwise.")
    sleep(0.1)
    port, channel = encoderInfo(motorNumber)
    startPosition = readEncoder(port, channel)
    motor.relative_move(value)
    debug("Relative move Clockwise.")
    sleep(0.1)
    motor.relative_move(-value)
    
    endPosition = readEncoder(port, channel)
    delta = motorPositionDelta(startPosition, endPosition)
    
    debug("Start Position: " + hex(startPosition) +
          ", End Position: " + hex(endPosition) +
          ", Delta: " + hex(delta))

    assertTrue(assertEqualsWithDelta(startPosition, endPosition, 0xf),
               "Relative move Test for motor " + str(motorNumber) + ". Start and end position are not the same.")
    motor.stop()
    motor.resetDev()
    
#################################################
    
def pwmAndStepperTest(pwmPort, stepperPort):
    printTitle("PWM(port = " + str(pwmPort) + ") and Stepper(port = " + str(stepperPort) + ") test")
    motor = stepper.stepper(port = stepperPort, speed = MAX_SPEED)
    debug("Stepper Run Until Stop for 2 seconds. NOTE: PWM should not be running.")
    stepper.runUntilStop(1, 500)
    sleep(2)
    motor.stop()
    RPiMIB.openSPI()
    debug("PWM 4000 for 2 seconds")
    RPiMIB.sendPWM(pwmPort, 1000)
    sleep(2)
    debug("Stop PWM")
    RPiMIB.sendPWM(pwmPort, 0)
    RPiMIB.closeSPI()
    sleep(1)

#### Helpers
    
def setGPIOValue(value):
    slushEngine = Slush.sBoard()

    for i in range(0, 2): 
        label = ("A", "B")[i == 1]
        for j in range(0, 8):
            port = label + str(j)
            debug("Setting " + str(i) + ", " + str(j) + " to " + str(value))
            slushEngine.setIOState(i, j, value)
            sleep(0.05)

def checkGPIOValue(value):
    slushEngine = Slush.sBoard()

    for i in range(0, 2): 
        label = ("A", "B")[i == 1]
        for j in range(0, 8):
            port = label + str(j)
            state = slushEngine.getIOState(i, j)
            debug("Getting " + str(i) + ", " + str(j) + " with value of " + str(state))
            debug(port + " Expected: " + str(value) + ", Received : " + str(state))
            assertTrue(state == value,
                       port + " should be " + str(value) + " but is " + str(state))
            sleep(0.05)

def moveOffSwitch(motor, direction):
    if (motor.read_switch() == 1):
        debug("Moving off switch.")
        motor.run(direction, 100)
        sleep(0.4)
        motor.stop()
        
def readEncoder(port, index):
    RPiMIB.open_spi()
    sleep(0.1)
    encoderValue = RPiMIB.read_encoder(port, index)
    RPiMIB.close_spi()
    return(encoderValue)

def encoderInfo(motorNumber):
    if motorNumber == 0:
        port = 1
        channel = 0
    elif motorNumber == 1:
        port = 1
        channel = 1
    elif motorNumber == 2:
        port = 1
        channel = 2
    elif motorNumber == 3:
        port = 2
        channel = 0
        
    return port, channel

def motorPositionDelta(start, end):
    result = end - start
    
    if (result < 0):
        result = start - end
        
    #result = (0xfff - start) + end

    return result

def testSwitch(motor):
    switchSet = False
    for i in range(1, 20, 1):
        switchSet = switchSet|(motor.read_switch() == 1)
        sleep(0.01)
    return switchSet

def assertEqualsWithDelta(expected, result, delta):
    if (result >= expected - delta):
        if (result <= expected + delta):
            return True
    return False

def assertTrue(condition, message, errorOnly = True):
    if (condition == True):
        if (errorOnly != True): 
            printPassed(message)
    else:
        printFailed(message)

def motorEncoderMessage(motorNumber, port, channel):
    return "motor " + str(motorNumber) + ", port " + str(port) + ", channel " + str(channel)

def printTitle(message):
    print("\033[1;33;40m########### %50s ###########" % message)
    print("\033[0;37;40m")
    
def printFailed(message):
    print("\033[1;31;40m##### Failed: " + message)
    print("\033[0;37;40m")

def printPassed(message):
    print("\033[1;32;40m##### Passed: " + message)
    print("\033[0;37;40m")

def debug(message):
    if (args.verbose == True):
        print("# " + message)

def endTests():
    debug("Ending tests, freeing motors")
    for i in range(0, 4):
        motor = stepper.stepper(port = i, speed = 10)
        motor.stop()
        motor.free()
    
########################### Tests #########################################

#gpioInputTest()

for i in range(0, args.motorCount):
#    homeTest(i)
#    speedTest(i)
#    relativeMoveTest(i, 20)
    encoderTest(i)
#    encoderTriggerTest(i, 0x0F0)

if args.motor != -1:
#    homeTest(args.motor)
#    speedTest(args.motor)
#    relativeMoveTest(args.motor, 20)
    encoderTest(args.motor)
#    encoderTriggerTest(args.motor, 0x0F0)

#pwmAndStepperTest(4, 0)
#for pwmPort in range(4, 6, 1):
#    RPiMIB.openSPI()
#    RPiMIB.sendPWM(pwmPort, 0)
#    RPiMIB.closeSPI()

endTests()

