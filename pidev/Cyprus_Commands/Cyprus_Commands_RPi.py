"""
@file Cyprus_Commands_RPi.py
File containing the commands to interface with the cyprus
"""
import spidev
import os
from time import sleep

spi = spidev.SpiDev()
delay = .001
spi_frequency = 1000000
pwm_clock_frequency = 1000000

servo_position_minimum = .001
servo_position_range = .001

servo_speed_minimum_positive = .001555
servo_speed_minimum_negative = .001445
servo_speed_range = .00007

COMPARE_MODE = 0
PERIOD = 1
COMPARE = 2

EQUAL = 0
LESS_THAN = 1
LESS_THAN_OR_EQUAL = 2
GREATER_THAN = 3
GREATER_THAN_OR_EQUAL = 4

TRIGGER_OFF = 0x8000

TRIGGER_MODE = 1 
GPIO_MODE = 0

#break_into_list and form_word translate between lists of 2 bytes and 16 bit words

def break_into_list(word):
    return [word >> 8, word & 0x0FF]

def form_word(byte_list):
    return (byte_list[0] << 8) + byte_list[1]

def spi_write_word(word):
    """
    Sends a 16 bit word to the cyprus
    :param word: 16 bit word
    :return: None
    """
    spi.xfer(break_into_list(word), spi_frequency)

def spi_read_word():
    """
    reads the spi value sent to the RPi as a 16 bit word
    :return:
    """
    return form_word(spi.xfer([0x00, 0x00], spi_frequency, 1))

def open_spi():
    """
    Open SPI communication with the Cyprus
    :return: None
    """
    spi.open(0,0)
    spi.mode = 0b00

def close_spi(): #closes spi communication
    """
    Close SPI communication with the Cyprus
    :return: None
    """
    spi.close()

def read_spi(port, channel):
    """
    Read SPI on a given port and channel

    :param port: SPI port to read from
    :param channel: SPI channel on port to read from
    :return: returns the response received by the cyprus from the given port and channel
    """
    command_data = 0x0300 | (port << 4) | channel
    spi_write_word(command_data)
    sleep(2*delay)
    return spi_read_word()

def write_spi(port, channel, value):
    """
    Writes the given value to the given spi port and channel of the cyprus
    :param port: Port on the cyprus to write to
    :param channel: Channel on the cyprus to write to
    :param value: The value to write on the given spi port and channel
    :return:
    """
    command_data = 0x0400 | (port << 4) | channel
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(value)

def write_pwm(port, parameter, value):
    """
    changes the given parameter, either COMPARE_MODE, PERIOD, or COMPARE,
    of the given port to the given value. Compare modes: LESS_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN, GREATER_THAN_OR_EQUAL, EQUAL

    :param port: PWM Port
    :param parameter: PWM parameter to change
    :param value: value to change the parameter to
    :return: Reutrns string if the parameter isn't recognized, None otherwise
    """

    if (parameter == COMPARE_MODE):
        processed_value = value
    elif (parameter == PERIOD):
        processed_value = int(value * pwm_clock_frequency)
    elif (parameter == COMPARE):
        processed_value = int(value * pwm_clock_frequency)
    else:
        return "parameter not recognized"
    command_data = 0x0500 | (port << 4) | parameter
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(processed_value)
	
def setup_servo(port):
    """
    sets up the given pwm port to control a servo
    :param port: PWM port to setup a servo on
    :return: None
    """
    write_pwm(port, COMPARE, LESS_THAN_OR_EQUAL)
    sleep(delay)
    write_pwm(port, PERIOD, .02)
	
def write_servo_position(port, position):
    """
    sets servo on given port to position given by a number in the interval [0, 1], where 0 corresponds to one end of its range and 1 to the ot
    :param port: Port the servo motor is attached to
    :param position: Position to write the servo to in the given interval [0,1]
    :return: None
    """
    if (position > 1):
        # her
        position = 1
    elif (position < 0):
        position = 0
    compare = servo_position_minimum + (position * servo_position_range) 
    write_pwm(port, COMPARE, compare)
	
def set_servo_speed(port, speed):
    """
    sets servo on given port to speed given by a number in the interval [-1, 1], where -1 corresponds to maximum in one direction and 1 to the other
    :param port: Port the servo motor is attached to
    :param speed: Speed to set the servo to in the interval [1, 1]
    :return:
    """

    if (speed < -1):
        speed = -1
    elif (speed > 1):
        speed = 1
    if (speed < 0):
        compare = servo_speed_minimum_negative + (speed * servo_speed_range)
    elif(speed > 0):
        compare = servo_speed_minimum_positive + (speed * servo_speed_range)
    elif(speed == 0):
        compare = (servo_speed_minmimum_positive + servo_speed_minmimum_negative) / 2
    write_pwm(port, COMPARE, compare)

def read_gpio():
    """
    Read the GPIO
    :return: returns a 4 bit number, each bit corresponds to a gpio pin
    """
    spi_write_word(0x0100)
    sleep(delay)
    return spi_read_word()

def write_gpio(value):
    """
    given a 4 bit number, writes the bits to the gpio pins
    :param value: 4 bit number
    :return: None
    """
    spi_write_word(0x0200)
    sleep(delay)
    spi_write_word(value & 0x0F)

def read_i2c(port, address):
    """
    Read i2c at a given port and address
    :param port: i2c port to read from
    :param address: address on the i2c port
    :return: value read from i2c at the given address
    """
    command_data = 0x0600 | port
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(address << 8)
    sleep(delay)
    return spi_read_word()

def write_i2c_data_byte(value):
    """
    writes a single byte to the stored i2c data in the cyprus in advance of send i2c command
    :type value: single byte
    :param value: value to write to the stored i2c data in the cyprus
    :return:
    """
    spi_write_word(0x0800)
    sleep(2*delay)
    spi_write_word(value)
    
def write_i2c_data_list(values):
    """
    writes a list of bytes to stored i2c data in the cyprus
    :type values: list of bytes
    :param values: list of bytes to write to the i2c stored data in the cyprus
    :return: None
    """
    for i in range(len(values)):
        write_i2c_data_byte(values[i] & 0x00FF)
        sleep(2*delay)

def write_i2c_address(address):
    """
    writes the stored i2c address in the cyprus in advance of send i2c command
    :param address: i2c address to write
    :return: None
    """
    spi_write_word(0x0900)
    sleep(delay)
    spi_write_word(address)

def send_i2c(port):
    """
    signals the cyprus to send the prewritten data to the prewritten address through the given port
    :param port: i2c port to write to
    :return:
    """
    command_data = 0x0700 | port
    spi_write_word(command_data)
    
def write_i2c(port, address, values):
    """
    complete procedure to send given list of bytes to given address through given i2c port
    :param port: i2c port
    :param address: i2c address
    :param values: values to write to the i2c port and address
    :return: None
    """
    write_i2c_data_list(values)
    write_i2c_address(address)
    sleep(2*delay)
    send_i2c(port)
    
def set_encoder_trigger(channel, value):
    """
    sets trigger on given channel to given value, cyprus activates corresponding gpio pin when encoder reads
    within radius of trigger set value to TRIGGER_OFF to disable trigger
    :param channel: channel to set the trigger value
    :param value: value to set the trigger on the given channel
    :return:
    """
    command_data = 0x0a00 | channel
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(value)
    
def read_encoder(port, channel):
    """
    returns the value from the encoder at the given channel
    :param port: port of the encoder
    :param channel: channel the encoder is on
    :return:
    """
    command_data = 0x0b00 | (port << 4) | channel
    spi_write_word(command_data)
    sleep(5*delay)
    return spi_read_word()

def set_trigger_radius(channel, value):
    """
    sets the encoder trigger radius of the given channel to the given value
    :param channel: channel of the encoder
    :param value: value of the trigger radius
    :return:
    """
    command_data = 0x0c00 | channel
    spi_write_word(command_data)
    sleep(delay)
    spi_write_word(value)

def set_pinmode(mode):
    """
    sets the pins to either encoder trigger mode or gpio mode, using constants TRIGGER_MODE and GPIO_MODE
    :param mode: mode to set the pins to
    :return: None
    """
    spi_write_word(0x0d00)
    sleep(delay)
    spi_write_word(mode)
	
def write_firmware_date(day, month, year):
    """
    writes a date to identify the cyprus firmware
    :param day: Firmware day
    :param month: Firmware month
    :param year: Firmware year
    :return: None
    """
    spi_write_word(0x0e00)
    sleep(delay)
    spi_write_word(day)
    spi_write_word(0x0e01)
    sleep(delay)
    spi_write_word(month)
    spi_write_word(0x0e02)
    sleep(delay)
    spi_write_word(year)

def read_firmware_date():
    """
    reads the firmware date from the cyprus
    :return: list in the form of [day, month, year]
    """
    spi_write_word(0x0f0000)
    sleep(delay)
    day = spi_read_word()
    spi_write_word(0x0f0001)
    sleep(delay)
    month = spi_read_word()
    spi_write_word(0x0f0002)
    sleep(delay)
    year = spi_read_word()
    return [day, month, year]
	
def no_command():
    """
    sends command to cyprus that tells it to do nothing
    :return: None
    """
    spi_write_word(0x000)
