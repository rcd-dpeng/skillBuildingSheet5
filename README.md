# Begin Here - Overview

## SlushEngine, Raspberry Pi, Python, Kivy

These four components comprise what the DPEA calls a "Raspberry Pi project." This colloquialism refers to both the hardware (SlushEngine and Raspberry Pi) and software (Python and Kivy) involved. Your project will contain one .py (Python) file and one .kv (Kivy) file.

### SlushEngine
The SlushEngine is a hardware driver that works with the Raspberry Pi to move (stepper) motors with speed and simplicity. Your SlushEngine is physically connected to your project and its stepper motors.

Take time to review a more in-depth overview of the SlushEngine hardware here: https://github.com/dpengineering/RaspberryPiCommon/blob/master/HardwareInfo.md 

### Raspberry Pi
The Raspberry Pi is a (physical) computer small enough to fit on the SlushEngine. Because the Raspbery Pi is a computer, it can run IDEs, browsers, apps, etc. on your project's monitor. You will be interacting with the Raspberry Pi via your monitor to work on your project.

Again, see https://github.com/dpengineering/RaspberryPiCommon/blob/master/HardwareInfo.md to visualize where the Raspberry Pi is positioned in respect to the SlushEngine.

To INSTALL Raspberry Pi, see https://github.com/dpengineering/RaspberryPiCommon/blob/master/OSInstallation.md

### Python
Python is the language you will use to program your Raspberry Pi project. There are various SlushEngine Python functions that you will include in your program (.py file) to control hardware directly.

It is a good idea to familiarize yourself with Python syntax, etc. before embarking upon your programming endeavors. Here is a good source: https://www.learnpython.org/

### Kivy
Kivy is the Python library we use to create your Raspberry Pi project's user interface (UI). Although all Kivy UI code is found in the .kv file, all Kivy-related import statements are included in the .py Python file. 

Kivy syntax is different from python syntax; be sure to reference both the Kivy documentation here: https://kivy.org/docs/ and some examples here: jdkhkjhdfkjhf.
