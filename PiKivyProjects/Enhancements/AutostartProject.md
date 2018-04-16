# Creating a Startup Script on a Raspberry Pi

When creating a UI using a Raspberry Pi and a Slush Engine, it is desirable for your UI script to run as soon as the Raspberry Pi loads the display. Note that there are **very many** ways of accomplishing this, so the steps listed below may differ from some online guides. These steps were tested on Raspbian Stretch Lite with the RPD desktop environment installed.

# Steps:

1. Open the LXDE autostart file by typing `sudo vim ~/.config/lxsession/LXDE-pi/autostart` into a terminal.
* This file should have several lines already, each begining with `@`. If this file is empty, ensure you typed the path in correctly.
2. At the end of the autostart file, add a line that runs your UI script. This line constists of an `@` sybmol at the beginning, followed by `python3 [PATH TO YOUR SCRIPT]`. For example: `@python3 /home/pi/Documents/InfinityMirrorPie/main.py`.
* If you don't know how to edit files in vim, try [this](http://www.openvim.com/) or use `sudo nano` instead.
3. Save your file and reboot the Pi using `sudo reboot`. Theoretically, your script should run as soon as you log in and the display loads. If it works, continue to the next step. If you have issues, move to the troubleshooting section.
4. We now have to disable the password prompt for the Raspberry Pi's login. Start by opening a terminal and typing `sudo raspi-config`.
5. Using the arrows and enter key, navigate to **Boot Options>Desktop/CLI**.
6. Navigate down to option **B4** on the very bottom of the menu and hit enter.
7. Reboot the Pi. If all has gone to plan, the UI will automatically start.

# Troubleshooting

1. So your startup script didn't run. Bummer. First, view the crash logs by typing `sudo vim /home/pi/.xsession-errors`. This should show you any crashes that occured while the desktop environment was loading. 
2. If you see a line that says **python3 [YOUR SCRIPT]: No such file or directory** or something of that sort, ensure you typed the directory of your script correctly. I've also found that it doesn't work when you use the `~` symbol in your script path, so make sure to write out the full path.
* e.g. `@python3 /home/pi/Documents/InfinityMirrorPie/main.py` instead of `@python3 ~/Documents/InfinityMirrorPie/main.py`
3. Reboot the Pi and try again. If you see a different error related to your script, edit the path and script accordingly.
