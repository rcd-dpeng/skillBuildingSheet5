## RaspberryPi OS Installation w/ Kivy Instructions:

1. Download KivyPi 0.9B from http://kivypie.mitako.eu/kivy-download.html (NOT version 1.0)
2. Flash .zip image to SD card using Etcher: https://etcher.io/ or another SD Card flash software. Make sure your SD card is at least 8gb.
3. Login with default username and password (username: sysop password: posys)
4. Make sure an ethernet cable is plugged in or follow steps to connect to wifi.
5. Change root password - `sudo passwd root`
6. Restart Raspberry pi - `sudo reboot`
7. Login as root user. Change `sysop` user to `pi` - `sudo usermod -l pi -d /home/pi -m sysop`
8. Install lightdm - `sudo apt-get update` then `sudo apt-get install lightdm`
9. Launch raspi-config - `sudo raspi-config`
10. Disable overscan (Advanced Options)
11. Set boot option to Boot to desktop and autologin (usually option 4 in Boot Options)
12. Enable SPI, I2C & Serial in Advanced options
13. Select finish and reboot
14. Open bash session (Click > Applications > Shells > Bash)
15. Install Slush - `sudo wget https://raw.githubusercontent.com/Roboteurs/slushengine/master/install.pl -O - | perl`
16. Install smbus - `sudo apt-get update` then `sudo apt-get install python3-smbus`

Optional - Install Ninja IDE text editor

17. Run `sudo apt-get install software-properties-common`
18. Run `sudo apt-get install python3-software-properties`
19. Run `sudo apt-add-repository ppa:ninja-ide-developers/ninja-ide-stable` - Will probably crash but its ok
20. Run `sudo apt-get update` then `sudo apt-get install ninja-ide`
21. Launch IDE by running `ninja-ide` from any bash session
