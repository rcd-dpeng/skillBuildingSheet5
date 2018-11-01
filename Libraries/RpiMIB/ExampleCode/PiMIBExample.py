#! usr/bin/env python3
import spidev
import os
from time import sleep
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(40, GPIO.IN)    
GPIO.setup(15, GPIO.IN)

# set up SPI between the Raspberry Pi and the PiMIB board
spi = spidev.SpiDev()
spi.open(0,0)


Amp1_I2C_Address = 0x49
Amp1_VolumeControl = 0x20    #   2-bit command type, 6-bits for volume control
Amp2_I2C_Address = 0x4A
Amp2_VolumeControl = 0x45      #   2-bit command type, 6-bits for volume control
sleep(0.1)
spiFrequency = 1000000

spi.xfer([0x00, 0x10], spiFrequency, 1)                      # sending this command tells PiMIB to send back encoder data
enca_list_of_bytes = spi.xfer([0x00, 0x00], spiFrequency, 1)  # getting data for encoder A
encb_list_of_bytes = spi.xfer([0x00, 0x00], spiFrequency, 1)
encc_list_of_bytes = spi.xfer([0x00, 0x00], spiFrequency, 1)
enca = 256*enca_list_of_bytes[0] + enca_list_of_bytes[1]  # convert the two bytes received into encoder value
encb = 256*encb_list_of_bytes[0] + encb_list_of_bytes[1]
encc = 256*encc_list_of_bytes[0] + encc_list_of_bytes[1]
    
if (enca == 0xf000) :         # encoder has 12-bit value  PiMIB sends back xF000 if encoder not pulgged in
    print("Encoder A not plugged in")
else :
    print("Encoder A reads  " + hex(enca))
      
if (encb == 0xf000) :
    print("Encoder B not plugged in")
else :
    print("Encoder B reads  " + hex(encb))
      
if (encc == 0xf000) :
    print("Encoder C not plugged in")
else :
    print("Encoder C reads  " + hex(encc))
                
spi.xfer([0x00, 0x20], spiFrequency, 1)  # command to write the next data to Function Generator 1
spi.xfer([0x12, 0x34], spiFrequency, 1)  #  data 0x1234 sent to function generator 1 using the SPI connector 1
    
spi.xfer([0x00, 0x40], spiFrequency, 1)   # command to write the next data to Function Generator 2
spi.xfer([0x67, 0x89], spiFrequency, 1)   #  data 0x6789 sent to function generator 2 using the SPI connector 1
    
spi.xfer([0x00, 0x80], spiFrequency, 1)  #command to write following data over I2C on connector 1
spi.xfer([Amp1_I2C_Address, Amp1_VolumeControl], spiFrequency, 1)  # I2C write to IC address 0x41 with data 0x17  0x41 = Amp1
    
spi.xfer([0x00, 0x80], spiFrequency, 1)  #command to write following data over I2C on connector 1
spi.xfer([Amp2_I2C_Address, Amp2_VolumeControl], spiFrequency, 1)  # I2C write to IC address 0x42 with data 0x05  0x42 = Amp2
 
while 1:   
    if not GPIO.input(40) :
        break



spi.close()
GPIO.cleanup()
print("good bye")
sleep(2)
os.system("sudo shutdown now -h")
