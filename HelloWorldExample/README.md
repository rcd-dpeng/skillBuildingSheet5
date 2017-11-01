# Kivy Hello World Example

This example code will run a basic kivy app with a button that will print "Hello!" to the console. There will also be another button that will quit the app.

1. Run newProject.py and name the project whatever you want.
2. A new folder will be created with 2 files, one called ```main.py``` and one called ```main.kv```

![](https://s1.postimg.org/6g7p0l1iy7/Capture.png)

3. Open up the main.py file in your text editor. The code should look like this:
```
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.graphics import *

Builder.load_file('main.kv')

sm = ScreenManager()
Window.clearcolor = (.95,.95,.95, 1) # Background Color of white

# ALL HARDWARE SETUP SHOULD APPEAR BETWEEN THESE LINES


# ^^^


class MainScreen(Screen):  # creates a scene called MainScene
    def buttonAction(self):
        pass

class MyApp(App):
    def build(self):
        return sm

sm.add_widget(MainScreen(name='main'))
MyApp().run()  # starts running app
```
> main.py

The first lines import all of the required libraries for Kivy to run. Next, the program references the .kv file that was also created. Then, a screen manager for the app is declared along with setting the background color to white. There is then a commented block of code where any inital stepper homing/IO control should take place. Ignore this part for now. Next, the main scene class is declared. Inside this class, there is a button action function that does nothing. Then, the App class is declared and finally the main screen is added to the screen manager and the app begins to run.

4. Open up your .kv file. It should look like this:
```
<MainScene>:    #start scene with a button and label
    name: 'main'
    FloatLayout:
        size_hint: None, None  #Needed to be able to define define height and width of widgets
        Button:
            size_hint: None,None
            text: 'text'
            font_size: 20
            size: 500, 75
            background_color: .1,.1,1,1
            center: root.center
            on_release: root.buttonAction()
 ```
 > main.kv

Here, the MainScreen is declared. You can see that there is already a button added inside that is set to be placed in the center of the screen with a size of 500x75. Finally, when the button is pressed (```on_release```), it will call the buttonAction() function inside the MainScene class from the .py file.
 
5. Lets change the text to say 'Hello world!' To do this, change ``` text: 'text'``` to ```text: "Hello World!"```. If you run the app (```python3 main.py``` from command prompt) now, it should look like this:

![](https://s1.postimg.org/2anutxz3tb/Capture1.png)

But the button doesnt do anything!

6. Lets make the console print 'Hello!' whenever you tap the button. Make this change in your .py file. The function that gets called when the button is tapped is called buttonAction() in the MainScreen Class. We know it is linked to the button from the .kv file because the property ```on_release:``` is set to ```root.buttonAction()``` Change ```buttonAction()``` in your .py file from:
```
def buttonAction(self):
        pass
```
to
```
def buttonAction(self):
        print("Hello!")
```
Now if you run the app, youll see that 'Hello!' is printed to the console every time you press the button.

7. Lets add another button to the screen that will let us quit. Do this in your .kv file by adding this below the current button:
```
        Button:
            size_hint: None,None
            text: 'Quit'
            font_size: 20
            size: 200, 75
            background_color: .1,.1,1,1
            center: root.center_x, root.center_y - 200
            on_release: root.tappedQuit()
```
> main.kv

This code will make a button of size 200, 75 which is placed in the center of the screen in the x direction and 200 units below the center in the y direction. The button will say 'Quit' and when it is tapped, the function tappedQuit() will be called. Lets implement tappedQuit() in our python file

8. Lets add another function to our MainScreen class that will be called when the new button is pressed. We called it tappedQuit() in our .kv file so that name must be matched in the .py file. Add another function so your MainScreen class looks like this:
```
class MainScene(Screen): 
    def tappedButton(self):
        print("Hello!!")
    def tappedQuit(self):
        quit()
```
> main.py

Now we have a new function tappedQuit() that calls quit() upon press. quit() is a universal Python function that simply exits the current process. If you try running the app now, it should look like this:

![](https://s1.postimg.org/1vt68jzp5b/Capture2.png)

And if you tap the quit button, the app should exit!

If you want to make more interesting and complex UIs there are a variety of examples availible here: https://kivy.org/docs/gettingstarted/intro.html
