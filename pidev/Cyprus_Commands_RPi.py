import spidev
import os
from time import sleep

spi = spidev.SpiDev()
delay = .001
spi_frequency = 1000000
pwm_clock_frequency = 1000000

#break_into_list and form_word translate between lists of 2 bytes and 16 bit words

def break_into_list(word):
    return [word >> 8, word & 0x0FF]

def form_word(byte_list):
    return (byte_list[0] << 8) + byte_list[1]

def spi_write_word(word): #sends a 16 bit word to the cyprus
    spi.xfer(break_into_list(word), spi_frequency)

def spi_read_word(): #reads the spi value sent to the RPi as a 16 bit word
    return form_word(spi.xfer([0x00, 0x00], spi_frequency, 1))

def open_spi(): #opens spi communication
    spi.open(0,0)
    spi.mode = 0b00

def close_spi(): #closes spi communication
    spi.close()

def read_spi(port, channel): #returns the response recieved by the cyprus from the given port and channel
    command_data = 0x0300 | (port << 4) | channel
    spi_write_word(command_data)
    sleep(2*delay)
    return spi_read_word()

def write_spi(port, channel, value): #writes the given value to the given spi port and channel of the cyprus
    command_data = 0x0400 | (port << 4) | channel
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(value)

def write_pwm(port, parameter, value): #changes the given paremeter, either "compare mode", "period", or "compare",
    if (parameter == "compare mode"):  #of the given port to the given value. Compare modes: 0:<, 1:<=, 2:>, 3:>=, 4:=
        parameter_number = 0
        processed_value = value
    elif (parameter == "period"):
        parameter_number = 1
        processed_value = int(value * pwm_clock_frequency)
    elif (parameter == "compare"):
        parameter_number = 2
        processed_value = int(value * pwm_clock_frequency)
    else:
        return "parameter not recognized"
    command_data = 0x0500 | (port << 4) | parameter_number
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(processed_value)
	
def setup_servo(port): #sets up the given pwm port to control a servo
	write_pwm(port, "compare mode", 1)
	write_pwm(port, "period", .02)
	
def write_servo_position(port, position): #sets servo on given port to position given by a number in the interval
	if (position > 1): 		              # [0, 1], where 0 corresponds to one end of its range and 1 to the other
		position = 1
	elif (position < 0):
		position = 0
	compare = .001 * (1 + position)
	write_pwm(port, "compare", compare)

def read_gpio(): #returns a 4 bit number, each bit corresponds to a gpio pin
    spi_write_word(0x0100)
    sleep(delay)
    return spi_read_word()

def write_gpio(value): #given a 4 bit number, writes the bits to the gpio pins
    spi_write_word(0x0200)
    sleep(delay)
    spi_write_word(value & 0x0F)

def read_i2c(port, address): #returns the value read from i2c at the given address
    command_data = 0x0600 | port
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(address << 8)
    sleep(delay)
    return spi_read_word()

def write_i2c_data_byte(value): #writes a single byte to the stored i2c data in the cyprus in advance of send i2c command
    spi_write_word(0x0800)
    sleep(2*delay)
    spi_write_word(value)
    
def write_i2c_data_list(values): #writes a list of bytes to stored i2c data in the cyprus
    for i in range(len(values)):
        write_i2c_data_byte(values[i] & 0x00FF)
        sleep(2*delay)

def write_i2c_address(address): #writes the stored i2c address in the cyprus in advance of send i2c command
    spi_write_word(0x0900)
    sleep(delay)
    spi_write_word(address)

def send_i2c(port): #signals the cyprus to send the prewritten data to the prewritten adress through the given port
    command_data = 0x0700 | port
    spi_write_word(command_data)
    
def write_i2c(port, address, values): #complete procedure to send given list of bytes to given adress through given i2c port
    write_i2c_data_list(values)
    write_i2c_address(address)
    sleep(2*delay)
    send_i2c(port)
    
def set_encoder_trigger(channel, value): #sets trigger on given channel to given value, cyprus activates 
    command_data = 0x0a00 | channel      #corresponding gpio pin when encoder reads within radius of trigger
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(value)
    
def read_encoder(port, channel): #returns the value from the encoder at the given channel
    command_data = 0x0b00 | (port << 4) | channel
    spi_write_word(command_data)
    sleep(2*delay)
    return spi_read_word()
        
def no_command(): #sends command to cyprus that tells it to do nothing
    spi_write_word(0x000)
