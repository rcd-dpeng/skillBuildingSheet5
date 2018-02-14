import os, shutil

MAIN_FILE_TEMPLATE = """
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


# ////////////////////////////////////////////////////////////////
# //            DECLARE APP CLASS AND SCREENMANAGER             //
# //                     LOAD KIVY FILE                         //
# ////////////////////////////////////////////////////////////////


sm = ScreenManager()

class MyApp(App):
    def build(self):
        return sm

Builder.load_file('kivy.kv')
Window.clearcolor = (0.1, 0.1, 0.1, 1) # (WHITE)


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
# //                          RUN APP                           //
# ////////////////////////////////////////////////////////////////


MyApp().run()

"""

KV_FILE_TEMPLATE = """
<MainScreen>:
    name: 'main'
    FloatLayout:
        size_hint: None, None

		# QUIT BUTTON
        Button:
            text: 'X'
            font_size: 23
            size_hint: None,None
            size: root.width * 0.015,root.width * 0.015
            x: root.width * 0.965
            y: root.height * 0.945
            background_color: 0.7, 0.7, 0.7, 1
            on_release: root.exitProgram()

		# IMAGE
        Screen:
            Image:
                source: 'DPEA Logo Transparent.png'
                keep_ratio: False
                allow_stretch: True
                opacity: 1
                size_hint: 2.7, 2.7
                x: root.width * 0.753
                y: root.height*0.283
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
