# To set up the power_shutdown module:
# Make sure the RaspberryPiCommon repo is cloned in the packages or you will need to modify command below

#First, copy the power_shutdown folder into the proper modules folder with the command:
pi@widget07-pi.local:~ $ sudo cp -r /home/pi/packages/RaspberryPiCommon/pidev/ShutdownModule/power_shutdown /lib/modules/$(uname -r)/kernel/drivers

# Then, find the module's dependency, making it visible to modprobe by running the commands:
pi@widget07-pi.local:~ $ cd /lib/modules/$(uname -r)/kernel/drivers/power_shutdown
pi@widget07-pi.local:~/lib/modules/4.14.71-v7+/kernel/drivers/power_shutdown $ sudo depmod

# Then, add power_shutdown to the list of modules to be installed on boot by running the following commands:
pi@widget07-pi.local:~/lib/modules/4.14.71-v7+/kernel/drivers/power_shutdown $ cd
pi@widget07-pi.local:~ $ sudo su
pi@widget07-pi.local:~ $ echo power_shutdown >> /etc/modules-load.d/modules.conf

# Next, reboot the Raspberry Pi
pi@widget07-pi.local:~ $ sudo reboot

# Last test that the Raspberry Pi does a graceful shutdown when a RPiMIB is installed with a Lipo battery backup
# The RaspberryPi does a graceful shutdown if the following happens after the power is removed from the RPiMIB:
# 1. The Red power LED (LED1) on the RPiMIB stays illuminated after the RPiMIB looses power
# 2. The Green status LED on the RPi next to the red power LED flickers for a few seconds after power is turned off
# 3. Then about 8 seconds after the Green status LED on the RPi goes off the red power LED turn off
# 4. Then about 30 seconds after removing power from the RPiMIB the Red power LED (LED1) on the RPiMIB goes off.
