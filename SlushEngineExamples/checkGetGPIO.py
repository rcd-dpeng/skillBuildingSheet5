"""
Title: Input Output

Description: This program will read the inputs on the SlushEngine expansion IO. During this program you
may apply 3.3V or ground to any of the pins to observe there change. This program can be modified to 
include motor controls based on the inputs and outputs. 

"""
#import the required module
import Slush
import time

#initalizes the board and all its functions
SlushEngine = Slush.sBoard()

while(1):
    #reads pin A[0-7] and B[0-7] and prints the value
    for j in range(0, 2):
        label = ("A", "B")[j == 1]
        for i in range(0, 8):
            print("Pin " + label + str(i) + ": " + str(SlushEngine.getIOState(j, i)))
            time.sleep(0.5)
