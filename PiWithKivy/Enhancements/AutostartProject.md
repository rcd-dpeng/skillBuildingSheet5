# Setting a program to autostart upon boot

**DO NOT SET THIS UNLESS THERE IS A BUTTON TO QUIT OUT OF THE APP WITHIN YOUR UI**

1. Use raspi-config to autoboot w/login to console (usually under 'Boot Options' or similar)
2. Open your .bashrc file in a text editor. This file is located in your home directory.
3. Assuming that you project folder is in your root directory, add a line to the end of this .bashrc file to ```cd``` into this folder. Probably will look like this: ```cd ~/MyProject```
4. Below that line, add the command to start the project. Probably ```python3 main.py```
5. Save this .bashrc file and reboot the pi.

Something to keep in mind: These steps tell the computer to execute the tasks once a bash session is launched. We use this method because a bash session is launched automatically upon boot and this is the easiest way to run tasks upon startup. Note, however, that even if you quit the program and go to launch another bash session, the program will autostart again. To avoid this, use anothe preinstalled shell like sh instead of bash when doing development work.
