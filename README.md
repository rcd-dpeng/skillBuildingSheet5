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
This block of code will define a new screen called ```MainScreen``` with the name ```'main'```. This name is what will be referenced whenever you want to transition to this scene. ```FloatLayout``` is the most basic layout type we will use. The layout type basically controls how objects are moved when the screen size changes. Since our screen sizes are relatively constant, we will prefer the FloatLaout because we can place objects in a X,Y coordinate system. Other layout types can be read about here: https://kivy.org/docs/gettingstarted/layouts.html

Most likely, this scene will contain buttons or other objects that will have something happen upon an event occuring (like tapping or dragging). In order to handle these events, there must be a place to declare the functions that handle them in your .py file. This is done by creating a new class like this in your .py file:

```
class MainScreen(Screen): 
    def something(self):
        pass
```
This block of code will create a new class with the name ```MainScreen```. Note that this name is the same as the name in the <> of the .kv file and NOT the ```name:``` property. In this example, there is one function called ```something``` which at this point does nothing. This function can be attatched to a button press or similar event as we will show later.
Finally, this scene must be added to the Screen Manager so that it can be shown and transitioned to. This is done as so:
```
sm.add_widget(MainScreen(name='main')) 
```
where ```sm``` is the screen manager variable you created earlier, ```MainScreen``` is the class type we just declared and ```'main'``` is the ```name:``` property you set in the .kv file.

### Widgets

Widgets are the building blocks with which you will build your UI. Widgets include Buttons, Sliders, Labels, and various other things which can be found here https://kivy.org/docs/api-kivy.uix.html under UX widgets. 

You will add widgets into your .kv file like so

```
Button:
    text: 'Im a Button'
    size_hint: None,None
    size:200,100
    x: root.width - self.width -500
    y: root.height *.45
    background_color: .1,.1,1,1
    on_release: root.something()
 ```
 This block of code declares a button and gives it all of its properties.
 
 ```text``` is the text displayed on the buton.
 ```size_hint: None,None``` allows us to assign an absolute size to our widget
 
 ```size``` is the size in pixels
 
 ```x``` is x position
 
 ```y``` is y position
 
 ```background_color``` is the color of the button in r,g,b,a
 
 ```on_release: root.something()``` is how we tie a function to the button. This function is declared in your .py file under the class for this screen. 
 
All of the properties you can asign to widgets can be found on this page https://kivy.org/docs/api-kivy.uix.widget.html

### Parent/Child Formatting

A very important part of Kivy is parent child relationships. These define what information widgets have acces to and what widgets can communicate with eachother. 

```
<MainScreen>:
    name: 'main'
    FloatLayout:
        size_hint: None, None 
        Button:
            size_hint: None,None
            text: 'Begin'
            font_size: 20
            size: self.parent.size
            background_color: .1,.1,1,1
            center: root.center
            on_release: root.something()
```            

In this example we have our screen ```main``` with a child ```floatlayout```. Next we have the ```Button``` which is a child of ```FloatLayout```. In the properties we can see a few new lines referencing ```parent``` and ```root```.

The line:

```
size: self.parent.size
```
sets the size of the button to the size of its parent. 

```center: root.center``` sets the center of the widget to the center of ```<MainScreen>``` and ```on_release: root.something()``` calls the ```something()``` function of ```MainScreen``` in the .py file

```
class MainScreen(Screen): 
    def something(self):
        pass
```

For the most part you will just be getting size or position from the parent  widget, or call function with root. But you can also use this to access data from your .py file like in this example.

```
<ExampleScreen>:
    name: 'touch' 
    FloatLayout:
        size_hint: None,None
        ExampleWidget:
            size_hint: None,None
            center_x: root.center_x - 30
            center_y: root.center_y
            Label:
                text: self.parent.tpos
                color: 0,0,0,1
                font_size: 50
                size_hint: None, None
                x: self.parent.width + self.parent.x + 300
                y: 600
```          
In this case the text of the label is being set to the variable ```tpos``` from the ```ExampleWidget``` Class.

This code also shows how you can create your own widgets and add them to other widgets (Not shown: the rule for ```<ExampleWidget>```)

Another important thing to notice is the ```self.``` infront of calls to parent. This is telling the code to reference the current widget. This is not needed with ```root``` because ```root``` always refers to the base widget of any rule. Rule reffering to anything included under ```<NAME>``` in the kv language.


### Examples

See the README.md in the example folder of this repository for further examples.
