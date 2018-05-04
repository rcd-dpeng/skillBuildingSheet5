import spidev
from time import sleep
#preparing SPI
spi=spidev.SpiDev()
spi.open(0,0)

global Amp_VolumeControl = 0x24
sleep(0.1)
spiFrequency = 1000000


#Intialization
FG1 = 0x20
FG2 = 0x40
Amp1 = 0x4A
Amp2 = 0x4B
global addresses = [[FG1, Amp1], [FG2, Amp2]]
global freq_clock = 16000000
global freq_out1 = 440
global freq_out2 = 450
global Two28 = 268435456 #this value equal to the 2^28
global phase = 0


def setAmpAddresses(addresses):
        global Amp_I2C_Address = addresses
def setFGAddresses(addresses):
        global FG_Addresses = addresses
def setPhase(newPhase):
        global phase
        phase = newPhase
#this method is responsible for sending data through SPI bus
def send_data(input, port):
	tx_msb=input>>8
	tx_lsb=input & 0xFF
        
	spi.xfer([0x00, addresses[port][0], spiFrequency, 1)  # command to write the next data to Function Generator 1
	spi.xfer([tx_msb,tx_lsb], spiFrequency, 1)
	
	print(input)
                 

def setVolume(Amp_Address, volume):
        #INSET CALC HERE: VOLUME INPUT (#1-10) > REAL AMP VOLUME (HEX)
        spi.xfer([0x00, 0x80], spiFrequency, 1)  #command to write following data over I2C on connector 1
        spi.xfer([Amp_Address, volume], spiFrequency, 1)

def openData(port):
        send_data(0x2100, FG_Address)

def closeData(port):
        send_data(0x2000, FG_Address)

def playSound(port, freq, volume, duration):
        setVolume(addresses[port][1], volume)
        openData(port)
                 
        global freq_clock
        #calculation for the frequency: converts wanted frequency to a 28-bit number, then scales by clock frequency
        freq_word=int(round(float(freq * Two28) / freq_clock))
        #frequency word divide to two parts as MSB and LSB.
        # FFFC ->1111 1111 1111 1100 0000 0000
        MSB = (freq_word & 0xFFFC000)>>14
        # 3FFF ->0011 1111 1111 1111 
        LSB = (freq_word & 0x3FFF)
        #DB15 and DB14 are set to 0 and 1
        LSB |= 0x4000
        #DB15 and DB14 are set to 0 and 1
        MSB |= 0x4000
        #DB15, DB14,DB13 = 110 DB12 =x
        #respectively, which is the address for Phase Register 0.
        #The remaining 12 bits are the data bits and are all 0s in this case
        phase |= 0xC000
                 
        #sending LSB and MSB
        send_data(LSB, FG_Address)
        send_data(MSB, FG_Address)
        #sending phase
        send_data(phase, 1)
        send_data(phase, 2)

        closeData(FG_Address)
        sleep(duration)

                 
def mute(Amp_Address):
        self.setVolume(Amp_Address, 0x00)
spi.close()
