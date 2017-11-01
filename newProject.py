import os, shutil

MAIN_FILE_TEMPLATE = """
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


class MainScene(Screen):  # creates a scene called MainScene
    def buttonAction(self):
        pass

class MyApp(App):
    def build(self):
        return sm

sm.add_widget(MainScene(name='main'))
MyApp().run()  # starts running app
"""

KV_FILE_TEMPLATE = """
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
"""


dirName = raw_input("Project Name: ")
os.makedirs(dirName)
os.chdir(dirName)

# Create html file
py = open('main.py', "w+")
py.write(MAIN_FILE_TEMPLATE)
py.close()

# Create sketch file
kv = open('main.kv', "w+")
kv.write(KV_FILE_TEMPLATE)
kv.close()
