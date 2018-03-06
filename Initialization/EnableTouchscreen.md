## Instructions to enable Kivy touchscreen:

1. Navigate to `~/kivy` and open `.kivy`'s `config.ini` with nano:
```
$ cd ~/kivy
$ nano ~/.kivy/config.ini
````
2. Enter `nano ~/.kivy/config.ini`
3. In the `[input]` section, remove the existing lines and put in:
```
mouse = mouse`
mtdev_%(name)s = probesys,provider=mtdev`
hid_%(name)s = probesys,priver=kidinput`
```
