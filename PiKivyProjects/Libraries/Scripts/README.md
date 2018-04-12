# Raspberry Pi Scripts

The scripts in the directory support the continuous running and maintainence of a project which has been deployed to the field.  This document describes how to install and run each script.  NOTE: These scripts are designed to help keep applications running and maintained without human interaction. You should fully understand what they do before installing.

launcher.sh : This script will launch the main UI of your project. This script first checks to see if the application is already running, if so, it does nothing.  Otherwise, it will launch the application.  If the application is running in the field.  This script should be executed in a cron job (see instructions below) to periodically check to see if the application is still running.  If the application has crashed, it will auto restart it.

updater.sh : This script allows for a project to be updated remotely. The script checks if changes were made to a specific GitHub branch of the project (this branch SHOULD NOT be the master branch). If the script detects changes, they are pull and installed in the project directory. This script should be run either when the Raspberry Pi boots or when the application is run (assume the application launched infrequently)

## launcher.sh

### Defaults

The launcher assumes that your project is installed in the **/home/pi/Documents** directory and the process name is **main.py**.

If you want to override the default values, you can set the following environment variables:

export DPEA_REPO_ROOT="/home/pi/git"
export DPEA_PROCESS="main.py -- --fan --begin"

NOTE: Use full paths, do not user ~/git

To execute the launcher.sh in a command shell:

. launch.sh <Project Directory Name>


## updater.sh



