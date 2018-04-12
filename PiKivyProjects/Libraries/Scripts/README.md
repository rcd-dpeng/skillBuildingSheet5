# Raspberry Pi Scripts

This document describes how to use the scripts which help support project which need to be run remotely.  The scripts include:

launcher.sh : This script will launch the main UI of your project. This script first checks to see if the application is already running, if so, it does nothing.  Otherwise, it will launch the application.  If the application is running in the field.  This script should be executed in a cron job (see instructions below) to periodically check to see if the application is still running.  If the application has crashed, it will auto restart it.

updater.sh : This script allows for a project to be updated remotely. The script checks if changes were made to a specific GitHub branch of the project (this branch SHOULD NOT be the master branch). If the script detects changes, they are pull and installed in the project directory. This script should be run either when the Raspberry Pi boots or when the application is run (assume the application launched infrequently)

## launcher.sh


## updater.sh



