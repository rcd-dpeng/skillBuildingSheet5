# Creating a Startup Script on a Raspberry Pi

When creating a UI using a Raspberry Pi and a Slush Engine, it is desirable for your UI script to run as soon as the Raspberry Pi loads the display. Note that there are **very many** ways of accomplishing this, so the steps listed below may differ from some online guides.

# Steps:

1. Create a shell script that changes directory into where your code is for your project. Do this in git bash by running the command `touch launcher.sh`
2. Edit the shell script so it navigates into your directory and runs your main python script, examle:

`cd /Documents/NewtonsCradle`

`python3 main.py`

3. Make the launcher script and your python main script executable by running `chmod u+x filename` in your projects source code directory ex. `chmod u+x main.py`. Don't forget to do this for your main python file and the launcher script.
4. Go into the terminal and run `crontab -e`
5. Select the editor you want to use in terminal to edit the crontab
6. Enter the line at the bottom `@reboot sh /path/to/your/launcher/script`
7. Reboot the pi and test if it works.
8. If it doesn't work check to see if your paths to your launcher script, and that your auncher script works.

Ensure that the password on the Raspberry Pi is disabled upon startup.
