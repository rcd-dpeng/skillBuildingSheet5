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
