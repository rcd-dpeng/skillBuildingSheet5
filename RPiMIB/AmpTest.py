import spidev
import os
from time import sleep
import RPi.GPIO as GPIO
	
# set up SPI between the Raspberry Pi and the PiMIB board
spi = spidev.SpiDev()
spi.open(0,0)

Amp2_I2C_Address = 0x4A
Amp2_VolumeControl = 0x24      #   2-bit command type, 6-bits for volume control
sleep(0.1)
spiFrequency = 1000000

spi.xfer([0x00, 0x80], spiFrequency, 1)  #command to write following data over I2C on connector 1
spi.xfer([0x4A, 0x24], spiFrequency, 1)  # I2C write to IC address 0x42 with data 0x05  0x42 = Amp2

spi.xfer([0x00, 0x80], spiFrequency, 1)  #command to write following data over I2C on connector 1
spi.xfer([0x4B, 0x24], spiFrequency, 1)  # I2C write to IC address 0x42 with data 0x05  0x42 = Amp2


spi.xfer([0x00, 0x40], spiFrequency, 1)  # command to write the next data to Function Generator 1
spi.xfer([0x4E, 0x20], spiFrequency, 1)  #  data 0x1234 sent to function generator 1 using the SPI connector 1
sleep(5)
spi.xfer([0x00, 0x40], spiFrequency, 1)  # command to write the next data to Function Generator 1
spi.xfer([0x59, 0xD8], spiFrequency, 1)  #  data 0x1234 sent to function generator 1 using the SPI connector 1
sleep(5)
spi.xfer([0x00, 0x40], spiFrequency, 1)  # command to write the next data to Function Generator 1
spi.xfer([0x40, 0x00], spiFrequency, 1)  #  data 0x1234 sent to function generator 1 using the SPI connector 1
sleep(5)

spi.close()
