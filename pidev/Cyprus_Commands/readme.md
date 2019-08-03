In order to initiate SPI communication with the Cyprus chip, call `open_spi()`.

Throughout the functions, the nomenclature of "port" and "channel" is used. The port refers to the sockets for a cable, or similar collections of pins. The channel refers to the individual communication interfaces inside each port.

If the Cyprus is not executing a command, it may be stuck in a listening state. Calling `no_command()` will ensure that the chip is in an idle state, ready to execute the next command.

Instructions on the use of each function are included below.

To control a servo using PWM, first use `setup_servo` to prepare the port. Once a port is set up, use `write_servo_position` each time you wish to change the servo's position.

Rather than writing to individual GPIO pins, each pin is considered as a binary digit of a number, which is written or read as a whole.

`write_i2c` is the only function required to send i2c data through the Cyprus. The other i2c functions are included for use cases where they may improve efficiency.

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
Write a 16 bit word to the given Cyprus PWM port. There are several functions that can be called which use default values for servos and motor controllers. Before setting custom values look at the **Related Functions** to control servos and motor controllers. For more information on PWM refer to https://en.wikipedia.org/wiki/Pulse-width_modulation.
* Parameters:
    - **port** (valid values 1 or 2):
        - 1 = RPiMIB port P4
        - 2 = RPiMIB port P5
    - **parameter** (valid values COMPARE_MODE, PERIOD, or COMPARE):
        - **PERIOD** - The clock period of the PWM. The **PERIOD** must be less than 1mHZ (1,000,000), the clock period of the Cyprus chip. The **PERIOD** is used in conjuntion with the **COMPARE** value to determine the duty cycle of the PWM. The default value of the **PERIOD** is 20,000 (20kHZ). This value only needs to be set once.
        - **COMPARE** - The **COMPARE** value is used in conjunction with the **PERIOD** to determine the duty cycle for the PWM. The **COMPARE** value MUST be less than the **PERIOD**.
        - **COMPARE_MODE** - The **PERIOD** counter comparisons that make up the PWM outputs. The default value is **LESS_THAN_OR_EQUAL**. This value only needs to be set once. **COMPARE_MODE** values include:
            - **LESS_THAN** – Compare output is true if period counter is less than the corresponding compare value.
            - **LESS_THAN_OR_EQUAL**– Compare output is true if period counter is less than or equal to the corresponding compare value.
            - **GREATER_THAN** – Compare output is true if period counter is greater than the corresponding compare value.
            - **GREATER_THAN_OR_EQUAL** – Compare output is true if period counter is greater than or equal to the corresponding compare value.
            - **EQUAL**– Compare output is true if period counter is equal to the corresponding compare value.
    - **value**: 16 bit PWM value
* Return: None

* Related methods:
    - setup_servo()
    - write_servo_position()
    - set_servo_speed()
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

# Create a PWM with a 50% duty cycle (PERIOD/COMPARE).
cyprus.open_spi()
cyprus.write_pwm(1, cyprus.COMPARE_MODE, cyprus.LESS_THAN_OR_EQUAL)
cyprus.write_pwm(1, cyprus.PERIOD, 20000)
cyprus.write_pwm(1, cyprus.COMPARE, 10000)
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

### setup_servo(port)
Sets the default values for the servo ports. This function needs to be called only once (in an initialization method) during the execution of a program. The default values include:
* **PERIOD** of 20,000 which equals a PWM clock of 20,000 hz
* **COMPARE_MODE** of **LESS_THAN_OR_EQUAL** indicating that the compare output is true if period counter is less than or equal to the corresponding compare value (set via the **write_servo_position()** function). To use other PWM values than the defaults, use the function **write_pwm()**.

* Parameters:
    - **port**: The port to which the servo is connected (valid values are 1 or 2):
        - 1 = RPiMIB port P4
        - 2 = RPiMIB port P5
* Return: None

* Related methods:
    - write_servo_position()
    - set_servo_speed()
    - write_pwm()
 ```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

def initialize():
    cyprus.open_spi()
    cyprus.setup_servo(1)
    cyprus.setup_servo(2)
```

### write_servo_position(port, position)
Sets the position of a servo on a given RPiMIB port. 
* Parameters:
    - **port**: The port to which the servo is connected (valid values are 1 or 2):
        - 1 = RPiMIB port P4
        - 2 = RPiMIB port P5
    - **position**: The position value is a float in the interval [0.0, 1.0] where 0.0 corresponds to one end of its range and 1.0 to the other. Note that the **position** value will be clamped to the interval [0.0, 1.0].
* Return: None

* Related methods:
    - setup_servo()
    - set_servo_speed()
    - write_pwm()
 ```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

# Initialize the servo and set the position to one extreme, the middle and the other extreme.
cyprus.setup_servo(1)
cyprus.write_servo_position(1, 0.0)
sleep(1)
cyprus.write_servo_position(1, 0.5)
sleep(1)
cyprus.write_servo_position(1, 1.0)
```
### set_servo_speed(port, speed)
Sets the speed of a servo on a given RPiMIB port. 
* Parameters:
    - **port**: The port to which the servo is connected (valid values are 1 or 2):
        - 1 = RPiMIB port P4
        - 2 = RPiMIB port P5
    - **speed**: The speed value is a float in the range [-1.0, 1.0] where -1.0 corresponds to the fastest speed in one diction and 1.0 to the fastest speed in the other. A speed of 0.0 with stop the servo. Note that the **speed** value will be clamped to the interval [-1.0, 1.0].
* Return: None

* Related methods:
    - setup_servo()
    - write_servo_position()
    - write_pwm()
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus

# Initialize the servo and loop through the servo speed values so the servo start fast in one direction, slows to a stop and then increases it speed in the oposite direction. Then, stop the servo.
cyprus.setup_servo(1)
for i in range(-10, 10, 1):
    cyprus.write_servo_position(1, i/10.0)
    sleep(0.5)
cyprus.write_servo_position(1, 0.0)
```
### set_encoder_trigger(encoderIndex, value)
Sets the trigger value of the given encoder. When the trigger value is reached, the corresponding GPIO pin will be get **True** on the RPiMIB. Each encoder can have a value between 0x000 and 0xFFF. If the encoder value is set to **TRIGGER_OFF **, the triggers will be disabled. The RPiMIB supports up to four encoders.
* Parameters:
    - **encoderIndex** - the encoder for which the trigger is being set. Valid values are in the range 1 to 4. When the RPiMIB determines the encoder value is reached, the following mapping indicates which GPIO pins on the RPiMIB board will be set **HIGH**:
        - 1 = RPiMIB port P6
        - 2 = RPiMIB port P7
        - 3 = RPiMIB port P8
        - 4 = RPiMIB port P9
    - **value**: The trigger value. Valid values are in the range 0x000 to 0xFFF.
* Return: None

* Related methods:
    - read_encoder()
    - set_trigger_radius()
    - set_encoder_trigger_auto_reset()
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus
from pidev import stepper

motor = stepper(port = 0, speed = 100, micro_steps = 2)

# Set the encoder value to be 0x500.
cyprus.set_encoder_trigger(0, 0x500)

# Move the motor (with limit switch input connected to P6).
# The motor should stop at the encoder value 0x500 (+/- 0x5).
motor.relative_move(50)

# The encoder value should be between 0x4FB and 0x505.
encoderValue = cyprus.readEncoder(0)
```

### read_encoder(encoderIndex)
Reads the current value of the encoder.
* Parameters:
    - **encoderIndex**: The encoder for which the trigger value is being read. Valid values are in the range 1 to 4. The following is a mapping of encoders to RPiMIB output GPIO ports.
        - 1 = RPiMIB port P6
        - 2 = RPiMIB port P7
        - 3 = RPiMIB port P8
        - 4 = RPiMIB port P9
* Return: 
    - **value**: The trigger value. Valid values are between 0x000 and 0xFFF.

* Related methods:
    - set_encoder_trigger()
    - set_trigger_radius()
    - set_encoder_trigger_auto_reset()
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus
from pidev import stepper

motor = stepper(port = 0, speed = 100, micro_steps = 2)

# Set the encoder value to be 0x500.
cyprus.set_encoder_trigger(0, 0x500)

# Move the motor (with limit switch input connected to P6).
# The motor should stop at the encoder value 0x500 (+/- 0x5).
motor.relative_move(50)

# The encoder value should be between 0x4FB and 0x505.
encoderValue = cyprus.readEncoder(0)
```

### set_trigger_radius(encoderIndex, value)
Sets the encoder trigger radius of the specified encoder. The trigger radius determines the range in which the trigger for the encoder will be fired. For an example, a **trigger radius** of 0x10 will cause the trigger to fire within 0x10 units on either side of the trigger value set by **set_encoder_trigger()**. The **trigger radius** should be set depending on the speed of the motor.  Faster motor speeds require a larger **trigger radius**. The default **trigger radius** is 0x5.
* Parameters:
    - **encoderIndex**: The encoder for which the **trigger radius** value is being set. Valid values are in the range 1 to 4. The following is a mapping of encoders to RPiMIB output GPIO ports.
        - 1 = RPiMIB port P6
        - 2 = RPiMIB port P7
        - 3 = RPiMIB port P8
        - 4 = RPiMIB port P9
* Return: 
    - **value**: The **trigger radius** value. Valid values are between 0x000 and 0xFFF.

* Related methods:
    - set_encoder_trigger()
    - read_encoder()
    - set_encoder_trigger_auto_reset()
```
from pidev.Cyprus_Commands import Cyprus_Commands_RPi as cyprus
from pidev import stepper

motor = stepper(port = 0, speed = 100, micro_steps = 2)

# Set the encoder value to be 0x500.
cyprus.set_encoder_trigger(0, 0x500)

# Set the encoder trigger radius to fire between the values 0x4EB and 0x515.
cyprus.set_trigger_radius(0, 0x15)

# Move the motor (with limit switch input connected to P6).
# The motor should stop at the encoder value 0x500.
motor.relative_move(50)

# The encoder value should be between 0x4FB and 0x505.
encoderValue = cyprus.readEncoder(0)
```


