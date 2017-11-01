from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.graphics import *

Builder.load_file('main.kv')

sm = ScreenManager()
Window.clearcolor = (.95,.95,.95, 1) # Background Color

class MainScene(Screen):  # creates a scene called MainScene
    def tappedButton(self):
        print("Hello!!")

class MyApp(App):
    def build(self):
        return sm

sm.add_widget(MainScene(name='main')) # adds TouchScenen and MainScene to screenmanager
MyApp().run()  # starts running app
