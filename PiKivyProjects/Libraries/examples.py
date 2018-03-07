#  Written by Francis Pan as part of the standard kivy libraries for the DPEA
#  28 February 2018

from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen, NoTransition
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.image import Image
from kivy.uix.widget import Widget
from kivy.uix.behaviors import ButtonBehavior
from kivy.uix.floatlayout import FloatLayout
from kivy.graphics import *
from kivy.clock import Clock
from kivy.animation import Animation

import time
import ImageButton

sm = ScreenManager()

class MyApp(App):
    def build(self):
        return sm

Builder.load_file('examples.kv')
Builder.load_file('DPEAButton.kv')
Builder.load_file('PauseScene.kv')

Window.clearcolor = (0.95, 0.95, 0.95, 1)

def pause(text, sec):
    sm.current = 'pauseScene'
    sm.current_screen.ids.pauseText.text = text
    Clock.schedule_once(transitionBack, sec)
    load = Animation(size = (150, 15), duration = sec) + Animation(size = (15, 15), duration = 0)
    load.start(sm.current_screen.ids.progressBar)

def transitionBack(dt):
    sm.current = 'examples'

class MainScreen(Screen):
    def DPEAButtonDown(self):
        self.ids.DPEAButton.color = 0.01, 0.168, .5, 1

    def XButtonDown(self):
        self.ids.X.color = 0.5, 0, 0, 1

    def resetColors(self):
        self.ids.DPEAButton.color = 0.019, 0.337, 1, 1
        self.ids.X.color = 1, 0, 0, 1

    def DPEAButtonUp(self):
        pause('Scene Paused', 5)

class PauseScene(Screen):
    pass

sm.add_widget(MainScreen(name = 'examples'))
sm.add_widget(PauseScene(name = 'pauseScene'))

MyApp().run()
