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

### open_spi()
Open SPI communication with the Cyprus chip. The must be called before attempting to communicate with the Cyprus chip.
* Parameters: None
* return: None
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus
cyprus.open_spi()
```

### close_spi()
Closes SPI communication with the Cyprus chip. `close_spi()` should be called when exiting a program.
* Parameters: None
* return: None
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

cyprus.open_spi()
<Do some SPI stuff>
cyprus.close_spi()
```

### spi_write_word(word)
Writes one word (16 bits) of data to the SPI channel.
* Parameters: word - a 16 bit word of data
* return: None
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

cyprus.open_spi()
cyprus.spi_write_word(0x0D00)
cyprus.close_spi()
```

### spi_read_word()
Reads one word (16 bits) of data from the SPI channel.
* Parameter: None
* return: one 16 bit word
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

cyprus.open_spi()
word = cyprus.spi_read_word()
cyprus.close_spi()
```
### write_pwm(port, parameter, value)
Write a 16 bit word to the given Cyprus PWM port.  

* Parameters:
    - **port** (valid values 1 or 2):
        - 1 = RPiMIB port P4
        - 2 = RPiMIB port P5
    - **parameter** (valid values COMPARE_MODE, PERIOD, or COMPARE):
        - COMPARE_MODE
        - PERIOD
        - COMPARE
    - **value**: 16 bit PWM value
* Return: None
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

cyprus.open_spi()
cyprus.write_pwm(2, cyprus.COMPARE, 1000)
cyprus.close_spi()
```
### read_gpio()
Read the GPIO from the RPiMIB board. Valid GPIO ports are P6, P7, P8 and P9.
* Parameters: None
* Return: 4 bits which represents ALL GPIO pins
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

cyprus.open_spi()
if (cyprus.read_gpio() & 0b0001):
    print("GPIO on port P6 is HIGH")
elif (cyprus.read_gpio() & 0b0010):
    print("GPIO on port P7 is HIGH")
elif (cyprus.read_gpio() & 0b0100):
    print("GPIO on port P8 is HIGH")
else (cyprus.read_gpio() & 0b1000):
    print("GPIO on port P9 is HIGH")
cyprus.close_spi()
```
 

