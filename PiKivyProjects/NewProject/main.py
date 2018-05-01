#   By Hannah Kleidermacher; to be used internally as a template for a new Pi/Kivy project.
#   February 2018


# ////////////////////////////////////////////////////////////////
# //                     IMPORT STATEMENTS                      //
# ////////////////////////////////////////////////////////////////

from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.button import Button
from kivy.uix.floatlayout import FloatLayout
from kivy.graphics import *
from dpea.utilities import MixPanel

PROJECT_TOKEN = "x"
bootEvent = MixPanel("My Project", PROJECT_TOKEN)
bootEvent.setEventName("Project Initialized")
bootEvent.sendEvent()

# ////////////////////////////////////////////////////////////////
# //            DECLARE APP CLASS AND SCREENMANAGER             //
# //                     LOAD KIVY FILE                         //
# ////////////////////////////////////////////////////////////////

sm = ScreenManager()

class MyApp(App):
    def build(self):
        return sm

Builder.load_file('main.kv')
Builder.load_file('DPEAButton.kv')
Window.clearcolor = (0.1, 0.1, 0.1, 1) # (DARKGREY)

# ////////////////////////////////////////////////////////////////
# //                    SLUSH/HARDWARE SETUP                    //
# ////////////////////////////////////////////////////////////////

# ////////////////////////////////////////////////////////////////
# //                      GLOBAL VARIABLES                      //
# //                         CONSTANTS                          //
# ////////////////////////////////////////////////////////////////

# ////////////////////////////////////////////////////////////////
# //                       MAIN FUNCTIONS                       //
# //             SHOULD INTERACT DIRECTLY WITH HARDWARE         //
# ////////////////////////////////////////////////////////////////

def quitAll():
    # free stepper motors, etc. before quit()
    quit() # quits program
#  more functions here

# ////////////////////////////////////////////////////////////////
# //        DEFINE MAINSCREEN CLASS THAT KIVY RECOGNIZES        //
# //                                                            //
# //   KIVY UI CAN INTERACT DIRECTLY W/ THE FUNCTIONS DEFINED   //
# //     CORRESPONDS TO BUTTON/SLIDER/WIDGET "on_release"       //
# //                                                            //
# //   SHOULD REFERENCE MAIN FUNCTIONS WITHIN THESE FUNCTIONS   //
# //      SHOULD NOT INTERACT DIRECTLY WITH THE HARDWARE        //
# ////////////////////////////////////////////////////////////////

class MainScreen(Screen):

    def exitProgram(self):
        quitAll()
    # more functions here

sm.add_widget(MainScreen(name = 'main'))

# ////////////////////////////////////////////////////////////////
# //                          MIXPANEL                          //
# ////////////////////////////////////////////////////////////////

def sendShapeEvent(eventName, prop):
    global PROJECT_TOKEN

    event = MixPanel("My Project", PROJECT_TOKEN)
    event.setEventName(eventName)
    event.addProperty("Property", prop)
    event.sendEvent()

# ////////////////////////////////////////////////////////////////
# //                          RUN APP                           //
# ////////////////////////////////////////////////////////////////

MyApp().run()
