# SlushEngine

## Hardware Overview

This is the SlushEngine: Model X LT. 

![](https://i.imgur.com/2v12RMR.png?1)

It is a stepper Motor controller with the ability to control 4 steppers, and has an additional 16 General Purpose input/output (GPIO) pins (3.3v)
### Power
Here is where power is attached to the SlushEngine. It can be between 8v-35v.

![](https://i.imgur.com/odr3LFQ.png?1)

### Steppers
These four ports (Motor 0-3)are where you attach the stepper motors to the board. When attaching motors make sure the wires are in the corrrect port (A+,A-,B+,B-). You can find out which wire is which on your steppers datasheer. 

![](https://i.imgur.com/VerCrTt.png?1)

### Limit Switches
There are also four ports where you can attach limit switches (SW0-SW3) to home the steppers (0-3) which can be found here:

![](https://i.imgur.com/g51PaSy.png?1)

### GPIO
The sixteen GPIO pins can be found here, along with ground and 3.3v pins. They are in two rows labeled PA0-PA7, PB0-PB7, and a third row for the 3.3v and ground pins.

![](https://i.imgur.com/TVrEYj9.png?1)

### UEXT
There is also a UEXT connector where we can attach i2c, spi, or serial devices. Documentation for this connector can be found [here](https://www.olimex.com/Products/Modules/UEXT/resources/UEXT_rev_B.pdf) 

![](https://i.imgur.com/0ws4Ydz.png?1)

### Raspberry Pi
And finally here is where you attach the Raspberry Pi:

![](https://i.imgur.com/xuiFksD.png?1)

## Software Overview

Now on to controlling things!

Before starting make sure you have installed the Slush python library on the Raspberry pi.

The following sections will be about software not found in the examples, or not made clear in the examples.

### Getting a motor running

Start by opening the python shell and entering ```import Slush```. This gives you access to the Slush library. Next enter ```b = Slush.sBoard()``` this initializes the board and names it b. Next enter ```m = Slush.Motor(0)``` this initialises the motor in port zero with the name m. Finally enter ```m.move(1000)``` this will make the motor move 1000 steps. If that worked Congrats! otherwise go to the troubleshooting section.

### Basic Motor Functions


```m.setCurrent(hold,run,acc,decc)```: sets the amount of current going to the stepper. It takes 4 unitless inputs between 0-200. It controls Current when its holding, running, accelerrating, and deccelerating. For our purposes just use m.setCurrent(20,20,20,20).

```m.setMicroSteps()```: Sets the microstepping for the stepper. can be between 1 and 128. NOTE this does not affect the the size of a step in any other function. SO moving 100 steps and full microstepping is the same at moving 200 at half microstepping.

```m.isBusy()```: returns true is the motor is performing a move and false when it is not performing a move.

```m.run(direction, speed)```: moves the motor indefinently in direction (0 or 1) at speed (in steps).

```m.free()```: disables the stepper motor.

```m.softStop()```: stops the motor with decceleration.

```m.hardStop()```: immediatly stops the motor.

```m.setAsHome()```: sets the current position as 0.

```m.goHome()```: moves to the home position.'

```m.goUntilPress(act, dir, speed)```: homes in dir at speed in steps until the switch on port act is pressed.

```b.getIOState(row, pin)```: gets the state of pin in row A or B (0 or 1) of number 0-7. 1 for high, 0 for low.

The rest of the commands can be found here: https://github.com/Roboteurs/slushengine/blob/master/Slush/Motor.py#L55

### Homing Steppers using Proximity Sensors

You can not use the default homing function if you need to home to a proximity sensor. You also need to do some different wiring.

The signal and ground pins can be plugged into the GPIO pins on the board. The sensors we use are rated for 5v to 30v so it will need to be attached to an appropriate power source.
When reading the data from the GPIO pin remember that the sensors are pullup so they will show low when sensed. So 1 = not sensed and 0 = sensed.

```
m.run(0,50)
while(b.getIOState(0,0) == 1):
    continue
m.hardStop()
m.setAsHome()
```

This code moves the motor slowly towards the sensor until it gets sensed. Once it is sensed it stops and sets the current position as home.

If you need to home multiple steppers at the same time (tied to the same axis or not). you will need to add a few more lines.

```
m0.run(0,50)
m1.run(0,50)
m2.run(0,50)
while(b.getIOState(0,0) == 1 or  b.getIOState(0,1) == 1 or b.getIOState(0,2) == 1 ):
    if(b.getIOState(0,0) == 0):
        m0.hardStop()
    if(b.getIOState(0,1) == 0):
        m1.hardStop()
    if(b.getIOState(0,2) == 0):
        m2.hardStop()
m0.hardStop()
m1.hardStop()
m2.hardStop()
m0.setAsHome()
m1.setAsHome()
m2.setAsHome()
```
This will start homing all of the motors and then stop each motor as it when it is sensed. When they are all sensed it sets their current position as home and continues with the rest of your program.
