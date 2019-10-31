# To set up the power_shutdown module:
The power_shutdown module is a module that allows the Raspberry Pi to gracefully shutdown when connected to an RPMIB (Raspberry Pi Multi Interface Board).

## Installation Instructions
Installing the power_shutdown module will take a little while as there are a fair amount of dependencies needed to compile and install the linux kernel module.

It is recommended you back up any important documents in the unlikely event your kernel is corrupted.

### Installation Script
There is a script located in the RaspberryPiCommon/Scripts named install-power-shutdown.sh.

Run this script with sudo. This will install all of the necessary dependencies, however the Pi needs to be rebooted in order for these changes
to take effect. Please note that upon running the script for the first time it will create a file named "part_1_complete.txt" please do not remove this file
the script will remove it upon the second run of the script. Additionally you may receive an error stating "", don't worry about this continue with the installation.

Upon reboot you need to re-run this script. This will now make and install the power_shutdown into the linux kernel.

## Test that power_shutdown functions properly
 0. Cut power to the Pi
 1. The Red power LED (LED1) on the RPiMIB stays illuminated after the RPiMIB looses power
 2. The Green status LED on the RPi next to the red power LED flickers for a few seconds after power is turned off
 3. Then about 8 seconds after the Green status LED on the RPi goes off the red power LED turn off
 4. Then about 30 seconds after removing power from the RPiMIB the Red power LED (LED1) on the RPiMIB goes off.
