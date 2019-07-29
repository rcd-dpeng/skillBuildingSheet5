In order to initiate SPI communication with the Cyprus chip, call `open_spi()`.

Throughout the functions, the nomenclature of "port" and "channel" is used. The port refers to the sockets for a cable,
or similar collections of pins. The channel refers to the individual communication interfaces inside each port.

If the Cyprus is not executing a command, it may be stuck in a listening state. Calling `no_command()` will ensure that
the chip is in an idle state, ready to execute the next command.

Instructions on the use of each function are included as comments in each python file.

To control a servo using PWM, first use `setup_servo` to prepare the port. Once a port is set up, use 
`write_servo_position` each time you wish to change the servo's position.

Rather than writing to individual GPIO pins, each pin is considered as a binary digit of a number, which is written or
read as a whole.

`write_i2c` is the only function required to send i2c data through the Cyprus. The other i2c functions are included for
use cases where they may improve efficiency.

When sending multiple commands in sequence, calling `sleep(delay)` between them is advised.

# Cyprus API

### Opens SPI Communication 
    Open SPI communication with the Cyprus. Before any communication can be sent or read from the Cyprus chip `open_spi` must be called.
        return: None

`open_spi()`

### Closes SPI Communication 
    Close SPI communication with the Cyprus. `close_spi` should be called when exiting a program.
        return: None

`close_spi()`

### SPI Write Word
    Sends a 16 bit word to the Cyprus.
        word: 16 bit word
        return: None

`spi_write_word(word)`

### SPI Read Word
    Reads the SPI value from the Cyprus as a 16 bit word
        return: None

`spi_read_word()`


'''
Read SPI on a given port and channel

:param port: SPI port to read from
:param channel: SPI channel on port to read from
:return: returns the response received by the cyprus from the given port and channel
'''
def read_spi(port, channel)

'''
Writes the given value to the given spi port and channel of the cyprus
:param port: Port on the cyprus to write to
:param channel: Channel on the cyprus to write to
:param value: The value to write on the given spi port and channel
:return:
'''
def write_spi(port, channel, value)

'''
changes the given parameter, either COMPARE_MODE, PERIOD, or COMPARE,
of the given port to the given value. Compare modes: LESS_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN, GREATER_THAN_OR_EQUAL, EQUAL

:param port: PWM Port
:param parameter: PWM parameter to change
:param value: value to change the parameter to
:return: Reutrns string if the parameter isn't recognized, None otherwise
'''
def write_pwm(port, parameter, value)

'''
sets up the given pwm port to control a servo
:param port: PWM port to setup a servo on
:return: None
'''
def setup_servo(port)
	
'''
sets servo on given port to position given by a number in the interval [0, 1], where 0 corresponds to one end of its range and 1 to the ot
:param port: Port the servo motor is attached to
:param position: Position to write the servo to in the given interval [0,1]
:return: None
'''
def write_servo_position(port, position)
	
'''
sets servo on given port to speed given by a number in the interval [-1, 1], where -1 corresponds to maximum in one direction and 1 to the other
:param port: Port the servo motor is attached to
:param speed: Speed to set the servo to in the interval [1, 1]
:return:
'''
def set_servo_speed(port, speed)

'''
Read the GPIO
:return: returns a 4 bit number, each bit corresponds to a gpio pin
'''
def read_gpio()

'''
given a 4 bit number, writes the bits to the gpio pins
:param value: 4 bit number
:return: None
'''
def write_gpio(value)

'''
Read i2c at a given port and address
:param port: i2c port to read from
:param address: address on the i2c port
:return: value read from i2c at the given address
'''
def read_i2c(port, address)

'''
writes a single byte to the stored i2c data in the cyprus in advance of send i2c command
:type value: single byte
:param value: value to write to the stored i2c data in the cyprus
:return:
'''
def write_i2c_data_byte(value)
    
'''
writes a list of bytes to stored i2c data in the cyprus
:type values: list of bytes
:param values: list of bytes to write to the i2c stored data in the cyprus
:return: None
'''
def write_i2c_data_list(values)

'''
writes the stored i2c address in the cyprus in advance of send i2c command
:param address: i2c address to write
:return: None
'''
def write_i2c_address(address)

'''
signals the cyprus to send the prewritten data to the prewritten address through the given port
:param port: i2c port to write to
:return:
'''
def send_i2c(port)
    
'''
complete procedure to send given list of bytes to given address through given i2c port
:param port: i2c port
:param address: i2c address
:param values: values to write to the i2c port and address
:return: None
'''
def write_i2c(port, address, values)
    
'''
sets trigger on given channel to given value, cyprus activates corresponding gpio pin when encoder reads
within radius of trigger. Caller must set value to TRIGGER_OFF to disable trigger
:param channel: channel to set the trigger value
:param value: value to set the trigger on the given channel
:return:
'''
def set_encoder_trigger(channel, value)

'''
sets trigger on given channel to given value, cyprus activates corresponding gpio pin when encoder reads
within radius of trigger. The trigger only fires once, the trigger value is reset after it is hit.
:param channel: channel to set the trigger value
:param value: value to set the trigger on the given channel
:return:
'''
def set_encoder_trigger_auto_reset(channel, value)

'''
returns the value from the encoder at the given channel
:param port: port of the encoder
:param channel: channel the encoder is on
:return:
'''
def read_encoder(port, channel)

'''
sets the encoder trigger radius of the given channel to the given value
:param channel: channel of the encoder
:param value: value of the trigger radius
:return:
'''
def set_trigger_radius(channel, value)

'''
reads the firmware date from the cyprus
:return: list in the form of [day, month, year]
'''
def read_firmware_version()
	
'''
sends command to cyprus that tells it to do nothing
:return: None
'''
def no_command()
