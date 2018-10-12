Fixing the touch inversion while using VNC is relatively simple.

Attempt to run fixInversion.sh to fix the issue, if this does not work you can manually fix the issue.

## Manually Fixing
On the Raspberry Pi navigate to kivy/kivy/input/providers and open up hidinput.py, and scroll to line 420.

The line should read ``` invert_y = int(bool(drs('invert_y', 1))) ``` replace the line with ``` invert_y = int(bool(drs('invert_y', 0))) ```
Save the file.

## Rerun setup.py
Once the hidinput.pt has been edited navigate to kivy/ in the terminal(go back a few directories). There should be a setup.py in the main kivy directory.
When you are in the correct directory run the command ``` sudo python3 setup.py install ``` this will reinstall kivy. This tends to take a while.
