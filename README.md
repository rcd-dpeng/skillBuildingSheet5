# Creating a UI With Kivy on the Raspberry Pi

This document assumes that you have a Raspberry Pi running the KivyPi OS as installed here: https://github.com/dpengineering/InfinityMirrorPie/blob/master/README.md

Note that all of the previous arcade Python programming was done in Python 2.7.x. All python code referenced below will be in Python 3.5 or above.

## Kivy Overview
Kivy is a UI library that makes it easy to create UIs that are written in 100% Python. It is organized in a heirarchal parent/child system similar to the current Javascript based UI libraries used on the Arcade. All programs written in Kivy will have 2 basic files. ```main.py``` and ```main.kv```. ```main.py``` is where all of the actual Python programming is done. The ```.kv``` file is where all layout information will be stored. This includes information like the location and size of widgets (Buttons, Images, Labels, etc...), what they do and where they are in the heirarchy. 

### App Class

The highest object on the widget heirarchy will be the App. This object requires little to no customization for our purposes. It will be declared in your .py file like this:
```
class MyApp(App):
    def build(self):
        return sm
```

The final line in your ```main.py``` file will then be ```MyApp.run()``` to begin your application. 'MyApp' can be renamed to whatever you want.

### Screen Manager

The next object embedded inside the App will be the Screen Manager. This is an object that manages every screen for your app (duh...). It behaves similarly to a Stage from JavaScript, meaning that it handles all of the transitions and scene navigation for your App. It is declared like this:
```
sm = ScreenManager()
```
You can then add screens (or 'scenes') to this screen manager which can then be referenced and transitioned to. You attatch a screen to a Screen Manager like this:
```
sm.add_widget(MainScene(name='main'))
```
where ```MainScene``` is replaced with the scene class name and ```'main'``` is replaced with the name of the scene. 

### Screens

Screens are where most of your programming will be done. While your app is running, the UI will be occupied by one screen at a time. This screen will have buttons, labels, and other types of objects that the user will be able to interact with. To create a custom screen, you will need to edit both the .py file and the .kv file. To start, open the .kv file and add this:
```
<MainScreen>:   
    name: 'main'
    FloatLayout:
        size_hint: None, None  
```
This block of code will define a new screen calle ```MainScreen``` with the name ```'main'```. This name is what will be referenced whenever you want to transition to this scene. 
Most likely, this scene will contain buttons or other objects that will have something happen upon an event occuring (like tapping or dragging). In order to handle these events, there must be a place to declare the functions that handle them in your .py file. This is done by creating a new class like this:

```
class MainScreen(Screen): 
    def something(self):
        pass
```
This block of code will create a new class with the name ```MainScreen```. Note that this name is the same as the name in the <> of the .kv file and NOT the ```name:``` property. In this example, there is one function called ```something``` which at this point does nothing. This function can be attatched to a button press or similar event as we will show later.

### Widgets
