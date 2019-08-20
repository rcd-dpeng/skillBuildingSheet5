# Begin Here - Overview

For an in depth look at code documentation please refer to the auto updated [docs.](https://dpengineering.github.io/RaspberryPiCommon/)

## SlushEngine, Raspberry Pi, Python, Kivy

These four components comprise what the DPEA calls a "Raspberry Pi Project." This colloquialism refers to both the hardware (SlushEngine and Raspberry Pi) and software (Python and Kivy) involved. Your project will contain one .py (Python) file and one .kv (Kivy) file.
Note: Not all projects may need all of the aforementioned items.

### SlushEngine
The SlushEngine is a hardware driver that works with the Raspberry Pi to move (stepper) motors with speed and simplicity. Your SlushEngine is physically connected to your project and its stepper motors.

Take time to review a more in-depth overview of the SlushEngine hardware [here.](https://github.com/dpengineering/RaspberryPiCommon/blob/master/docs/HardwareInfo.md) 

### Raspberry Pi
The Raspberry Pi is a (physical) computer small enough to fit on the SlushEngine. Because the Raspberry Pi is a computer, it can run IDEs, browsers, apps, etc. on your project's monitor.

Again, see https://github.com/dpengineering/RaspberryPiCommon/blob/master/HardwareInfo.md to visualize where the Raspberry Pi is positioned in respect to the SlushEngine.

### Python
Python is the language you will use to program your Raspberry Pi project. There are various SlushEngine Python functions that you will include in your program (.py file) to control hardware directly.

It is a good idea to familiarize yourself with Python syntax, etc. before embarking upon your programming endeavors. Here is a good [source](https://www.learnpython.org/) 

#### Pidev
There are python libraries made by the DPEA for use on projects in a python module named pidev. More information on python modules can be found [here](https://docs.python.org/3/tutorial/modules.html)

To install pidev on Linux open a terminal and change directories to where RaspberryPiCommon exists. Then run the command ```pip3 install -e .``` you will then be able to access all of pidev's functionality.
More info on pidev and it's functionality can be found [here.](https://dpengineering.github.io/RaspberryPiCommon/annotated.html)

### Kivy
Kivy is the Python library we use to create your Raspberry Pi project's user interface (UI). All Kivy code is found in the .kv file, and is used exclusively for programming UI.

Kivy syntax is different from python syntax; be sure to reference both the Kivy documentation [here](https://kivy.org/docs/) and some Pi/Kivy resources [here.](https://github.com/dpengineering/RaspberryPiCommon/tree/master/PiKivyProjects)
