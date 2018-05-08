# To be used for the RPiMIB designed for the DPEA by Joe Kleeberg
# Compiled by Hannah Kleidermacher, Francis Pan, and Doug Whetter
# May 2018


#! usr/bin/env python3
import spidev
import os
from time import sleep
import RPi.GPIO as GPIO
from threading import Thread

SHUTDOWN_PORT = 21

GPIO.setmode(GPIO.BCM)
GPIO.setup(SHUTDOWN_PORT, GPIO.IN)    
GPIO.setup(22, GPIO.IN)

# set up SPI between the Raspberry Pi and the PiMIB board
spi = spidev.SpiDev()
spiFrequency = 1000000



#takes 0, 1, or 2
def readEncoder(encoder):
    global spi
    global spiFrequency
    
    spi.xfer([0x00, 0x10], spiFrequency, 1)                      # sending this command tells PiMIB to send back encoder data
    enc0_list_of_bytes = spi.xfer([0x00, 0x00], spiFrequency, 1)  # getting data for encoder A
    enc1_list_of_bytes = spi.xfer([0x00, 0x00], spiFrequency, 1)
    enc2_list_of_bytes = spi.xfer([0x00, 0x00], spiFrequency, 1)
    enc0 = 0x100*enc0_list_of_bytes[0] + enc0_list_of_bytes[1]  # convert the two bytes received into encoder value
    enc1 = 0x100*enc1_list_of_bytes[0] + enc1_list_of_bytes[1]
    enc2 = 0x100*enc2_list_of_bytes[0] + enc2_list_of_bytes[1]

    if encoder == 0:
        if (enc0 & 0xf000) :         # encoder has 12-bit value  PiMIB sends back xF000 if encoder not pulgged in
            print("Encoder A not plugged in")
        return enca
    
    if encoder == 1:
        if (enc1 & 0xf000) :
            print("Encoder B not plugged in")
        return encb
    
    if encoder == 2:
        if (enc2 & 0xf000) :
            print("Encoder C not plugged in")
        return encc

def openSpi():
    spi.open(0,0)

def closeSpi():
    spi.close()
    
def sendSPI(address, data1, data2):
    global spi
    global spiFrequency
    spi.xfer([0x00, address], spiFrequency, 1)  # command to write the next data to Function Generator 1
    spi.xfer([data1, data2], spiFrequency, 1)  #  data 0x1234 sent to function generator 1 using the SPI connector 1
        
def sendI2C(address, data):
    global spi
    global spiFrequency
    spi.xfer([0x00, 0x80], spiFrequency, 1)  #command to write following data over I2C on connector 1
    spi.xfer([address, data], spiFrequency, 1)  # I2C write to IC address 0x41 with data 0x17  0x41 = Amp1

def cleanup():
    global spi
    spi.close()
    GPIO.remove_event_detect(SHUTDOWN_PORT)
    GPIO.cleanup()

def shutdown():
    cleanup();
    print("Shutting down in 2 seconds")
    sleep(2)
#    os.system("sudo shutdown now -h")

def shutdownHandler():
    print("Shutdown Handler Started");
    GPIO.wait_for_edge(SHUTDOWN_PORT, GPIO.FALLING)
    shutdown()

def startShutdownHandlerThread():
    t = Thread(target=shutdownHandler)
    t.start()

