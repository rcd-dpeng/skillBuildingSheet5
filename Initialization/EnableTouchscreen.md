## Instructions to enable Kivy touchscreen:

1. Navigate to ~/kivy:
    `cd ~/kivy`
2. Enter `nano ~/.kivy/config.ini`
3. In the `[input]` section, remove the existing lines and put in:
    `mouse = mouse`
    `mtdev_%(name)s = probesys,provider=mtdev`
    `hid_%(name)s = probesys,priver=kidinput`

