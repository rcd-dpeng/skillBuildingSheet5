#!/usr/bin/python3

import Stepper
import datetime # to print current date and time to testResults.txt
import re #regex

def runStepper(stepper):
    stepper.run(1, 2500)
    while stepper.readSwitch() == 0:
        continue
    
    checkIfSpinning(True)
        
    stepper.run(0, 2500)
    while stepper.readSwitch() == 0:
        continue
    
    checkIfSpinning(False)
    
    stepper.hardStop()
    stepper.free()
       
        
def checkIfSpinning(clockwise):
    if clockwise == True:
        clockWiseUserPrompt = input("Was the motor spinning clockwise? [y/n]\n")
        
        try:
            if clockWiseUserPrompt == "y" or clockWiseUserPrompt == "n":
                return
            else:
                raise ValueError("Not a valid response\n")
        except ValueError as error:
            print(error)
            clockWiseUserPrompt = input("Was the motor spinning clockwise? [y/n]\n")
        
    else:
        counterClockWiseUserPrompt = input("Was the motor spinning counter clockwise? [y/n]\n")
        
        try:
            if counterClockWiseUserPrompt == "y" or counterClockWiseUserPrompt == "n":
                return
            else:
                raise ValueError("Not a valid response\n")
        except ValueError as error:
            print(error)
            counterClockWiseUserPrompt = input("Was the motor spinning clockwise? [y/n]\n")
            
def checkUserInputPort(userInputPort):
    regex = r"[0123]"
    matches = re.finditer(regex, userInputPort)
    totalMatches = 0
    
    for matchNum, match in enumerate(matches):
        matchNum = matchNum + 1
        totalMatches = matchNum
       
        return matchNum
        
    if totalMatches < 1:
        return 0      

userInputPort = input("Which port is the stepper attached to?\n")

validUserInput = False

while not validUserInput:
    try:    
        if int(checkUserInputPort(userInputPort)) >= 1:
            int(userInputPort)
            validUserInput = True
            
        else :
            raise ValueError("Not a valid response")
    except ValueError as error:
        print(error)
        userInputPort = input("Which port is the stepper attached to?\n")


rightStepper = Stepper.Stepper(port = int(userInputPort))
runStepper(rightStepper)

input("press any key to exit")
