## RaspberryPi OS Installation w/ Kivy Instructions:

1. Download KivyPi 0.9B from http://kivypie.mitako.eu/kivy-download.html (NOT version 1.0)
2. Flash .zip image to SD card using Etcher: https://etcher.io/ or another SD Card flash software
3. Login with default username and password (username: sysop password: posys)
4. Change root password - `sudo passwd root`
5. Restart Raspberry pi - `sudo reboot`
6. Login as root user. Change `sysop` user to `pi` - `sudo usermod -l pi -d /home/pi -m sysop`
7. Install lightdm - `sudo apt-get update` then `sudo apt-get install lightdm`
8. Launch raspi-config - `sudo raspi-config`
9. Disable overscan (Advanced Options)
10. Set boot option to Boot to desktop and autologin (usually option 4 in Boot Options)
11. Enable SPI, I2C & Serial in Advanced options
12. Select finish and reboot
13. Open bash session (Click > Applications > Shells > Bash)
14. Install Slush - `sudo wget https://raw.githubusercontent.com/Roboteurs/slushengine/master/install.pl -O - | perl`
15. Install smbus - `sudo apt-get update` then `sudo apt-get install python3-smbus`

