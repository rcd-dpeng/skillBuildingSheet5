# Connect Raspberry Pi To Wi-Fi

These steps assume that you are running the newest Raspberry Pi firmware. This can be updated using `sudo rpi-update`. **NOTE THAT THIS COMMAND HAS BEEN KNOWN TO BRICK THE PI. MAKE SURE YOUR CODE IS BACKED UP!!**

1. Make sure the pi is in range of a wifi network. Note that your pi must be a model 3.
2. Edit the interface configuration file - `sudo vim /etc/network/interfaces`
3. Under the wlan0 configuration, set the `wpa-ssid` and `wpa-psk` to your network name and password surrounded by quotes.
4. Save the configuration file and launch `sudo raspi-config`
5. Set `Wait for network at boot` to yes.
6. Run `sudo reboot` if the configuration program doenst prompt you to do so.
7. Test the connection using `ping www.google.com`
