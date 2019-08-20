# Kivy UI Libraries for the DPEA
This document assumes that you have the most recent version of pidev (python module found [here](https://github.com/dpengineering/RaspberryPiCommon)) installed.
Documentation for pidev can be found [here.](https://dpengineering.github.io/RaspberryPiCommon/)

These are the libraries to be used for all Mechatronics projects that require the use of Python with Kivy. Please refer to this doc as well as the comments in the code files themselves for help on how to use these libraries/Kivy in general

Before using these libraries, make sure you have these imports in your python file:
```python
from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
```

## DPEAButton

A button that's a colored, rounded rectangle with a drop shadow. Text has a bolded white body and a black outline.

### Required Setup
To use you must import it from pidev:
```python
from pidev.kivy import DPEAButton
```

### Appearance Customization

You can specify the ```text```, ```color```, ```size```, ```center_x```, and ```center_y```. Here's an example of what your kivy code should look like now:
```
DPEAButton:
    background_color: 0, 0, 0, 0
    background_normal: ''
    size_hint: None, None
    text: 'Hello World!'
    size: 40, 40
    center_x: root.width * 0.97
    center_y: root.height * 0.955
    color: 1, 0, 0, 1
```

The parameters for ```color``` are red, green, blue, alpha (think of alpha as opacity), so in this case, a bright red.

### Touch Event Handling

For the DPEAButton, in order to add the color change animations and handle touches, you need to specify ```id```, ```on_press```, ```on_touch_up```, and ```on_release```. The ```id``` is especially important as it can be used later to change any characteristic of the button.
Here's an example of what your kivy code should look like now:
```
DPEAButton:
    id: ExampleButton
    size_hint: None, None
    text: 'Hello World!'
    size: 40, 40
    center_x: root.width * 0.97
    center_y: root.height * 0.955
    color: 1, 0, 0, 1
    on_press: root.ExampleButtonDown()
    on_touch_up: root.resetColors()
    on_release: root.exampleAction()
```

## Image Button

An Image with button-like behavior since kivy unfortunately does not have a default ```ImageButton``` class.

### Required Setup

At the top of your file with your import statements, add ```from pidev.kivy import ImageButton```. To use the ```ImageButton```, simply initialize it in your kivy file like so:
```
ImageButton:
    source: "path_to_image"
    center_x: root.width * 0.5
    center_y: root.height * 0.5
```

### Touch Event Handling

Binding an ```on_release``` method to the ```ImageButton``` should be enough, but feel free to use ```on_press``` and ```on_touch_up``` as well. Also note that ```id``` can also be used to change you button's characteristics.

## Pause Scene
There are instances when we want to have a pause screen while the project is performing an action.

### Pause Scene Setup
First import the pause screen:
```python
from pidev.kivy import PauseScreen
```

### Usage

To use the pause scene, simply call the pause method like so:
```
pause('Scene Paused', 5, 'examples')
```

The parameters in order are: ```text``` which is the text you wish the pause scene to display, ```sec``` which is the time you want the pause to be in seconds, and ```originalScene``` which is the string name you assigned to the scene you wish to switch back to.

## Admin Screen

An admin screen that requires a password to be entered to continue

### Required Setup

At the top of your file with your import statements, add ```import AdminScreen```.

Add the admin screen to the screen manager after you add your main scenes:
```
sm.add_widget(MainScreen(name = 'examples'))
# your other screens here
sm.add_widget(AdminScreen.AdminScreen(name = 'admin'))
```

Set the action that the admin screen will execute if the password is entered correctly by editing the ```AdminScreen.py``` file. Find the ```checkPass``` method that should look like the following:
```
def checkPass(self):
      global password
      global userPW
      if (password == userPW):
          print('correct')
          self.ids.pw.text = ' '
          userPW = ''
          self.parent.current = 'examples'
```

On the line that says ```self.parent.current = 'examples'```, modify it to run the action that you want it to

You also need to set the scene that the "Back to Game" button will transition to by editing the ```AdminScreen.kv``` file. Below is the code for the very first button in the file that you will be editing:
```
DPEAButton:
      background_color: 0, 0, 0, 0
      background_normal: ''
      size_hint: None, None
      text: 'Back to Game'
      id: back
      center_x: root.center_x
      center_y: root.center_y + 260
      color: 0.019, 0.337, 1, 1
      size: 280, 80
      on_press: root.backButtonDown()
      on_release: root.manager.current = 'examples'
      on_touch_up: root.resetColors()
```

On the line that says ```on_release: root.manager.current = 'examples'``` change ```'examples'``` to the name of the scene that you want the back button to go back to

### Password

The default password is ```7266```. To change this password, open the ```AdminScreen.py``` file and edit the line that says ```password = '7266'``` near the top of the file.

Passwords can be any length but must only contain numbers.

### Adding A hiddne Button

To keep all hidden button placement consistent, add this code to the .kv file in each ```<EXAMPLEScreen>``` that you want to lead to the admin screen.
```
Button:
            id: admin
            size_hint: None,None
            font_size: 20
            size: 10, 10
            background_color: 0, 0, 0, 0
            background_normal: ''
            center: root.width - 5, 5
            on_release: root.manager.current = 'main'
```
This creates a small transparent button in the bottom right of the screen.
