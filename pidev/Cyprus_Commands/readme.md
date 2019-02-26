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
