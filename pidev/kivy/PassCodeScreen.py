"""
@file PassCodeScreen.py
File that contains the PassCodeScreen Class to interact with the PassCodeScreen.
There is no need to copy the .kv file into your project simply import this class and set the main screen name as well as transition back screen
"""

from kivy.lang import Builder
from kivy.uix.screenmanager import Screen
import os.path

PASSWORD = '7266'
USERPW = ''

passcode_screen_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "", "PassCodeScreen.kv")

Builder.load_file(passcode_screen_path)

ADMIN_EVENTS_SCREEN = None
TRANSITION_BACK_SCREEN = 'main'

"""
Class to display a passcode on screen to advance to admin screen
"""


class PassCodeScreen(Screen):
    """
    Class used to enter the PassCodeScreen to enter the admin screen
    """
    def add_num(self, num):
        """
        Add a number to the current password entry
        :param num: Number to add
        :return: None
        """
        global USERPW

        self.ids.pw.text += '* '
        USERPW += str(num)

    def remove_num(self):
        """
        Remove a number from the current password entry
        :return: None
        """
        global USERPW
        self.ids.pw.text = self.ids.pw.text[:len(self.ids.pw.text) - 2]
        USERPW = USERPW[:len(USERPW) - 1]

    def check_pass(self):
        """
        Check to see if the password was entered correctly
        :return: None
        """
        global USERPW
        if PASSWORD == USERPW:
            self.ids.pw.text = ' '
            USERPW = ''
            self.parent.current = ADMIN_EVENTS_SCREEN

    def reset_colors(self):
        """
        Reset all of the colors
        :return: None
        """
        self.ids.back.color = 0.019, 0.337, 1, 1
        self.ids.one.color = 0.019, 0.337, 1, 1
        self.ids.two.color = 0.019, 0.337, 1, 1
        self.ids.three.color = 0.019, 0.337, 1, 1
        self.ids.four.color = 0.019, 0.337, 1, 1
        self.ids.five.color = 0.019, 0.337, 1, 1
        self.ids.six.color = 0.019, 0.337, 1, 1
        self.ids.seven.color = 0.019, 0.337, 1, 1
        self.ids.eight.color = 0.019, 0.337, 1, 1
        self.ids.nine.color = 0.019, 0.337, 1, 1
        self.ids.zero.color = 0.019, 0.337, 1, 1
        self.ids.backspace.color = 0.019, 0.337, 1, 1
        self.ids.enter.color = 0.019, 0.337, 1, 1

    def back_button_down(self):
        """
        back button pressed event, changes the color of the button
        :return: None
        """
        self.ids.back.color = 0.01, 0.168, .5, 1

    def transition_back(self):
        """
        Transition back to given transition back scren
        :return: None
        """
        self.ids.pw.text = ""
        self.parent.current = TRANSITION_BACK_SCREEN

    def one_button_down(self):
        """
        One button down pressed
        :return: None
        """
        self.ids.one.color = 0.01, 0.168, .5, 1

    def two_button_down(self):
        """
        Two button down pressed
        :return: None
        """
        self.ids.two.color = 0.01, 0.168, .5, 1

    def three_button_down(self):
        """
        Three button down pressed event
        :return: None
        """
        self.ids.three.color = 0.01, 0.168, .5, 1

    def four_button_down(self):
        """
        Four button down pressed event
        :return: None
        """
        self.ids.four.color = 0.01, 0.168, .5, 1

    def five_button_down(self):
        """
        Five button down pressed event
        :return: None
        """
        self.ids.five.color = 0.01, 0.168, .5, 1

    def six_button_down(self):
        """
        Size button down pressed event
        :return: None
        """
        self.ids.six.color = 0.01, 0.168, .5, 1

    def seven_button_down(self):
        """
        Seven button down pressed event
        :return: None
        """
        self.ids.seven.color = 0.01, 0.168, .5, 1

    def eight_button_down(self):
        """
        Eight button down pressed event
        :return: None
        """
        self.ids.eight.color = 0.01, 0.168, .5, 1

    def nine_button_down(self):
        """
        Nine button down pressed event
        :return: None
        """
        self.ids.nine.color = 0.01, 0.168, .5, 1

    def zero_button_down(self):
        """
        Zero button down pressed event
        :return: None
        """
        self.ids.zero.color = 0.01, 0.168, .5, 1

    def backspace_button_down(self):
        """
        Backspace button down pressed event
        :return: None
        """
        self.ids.backspace.color = 0.01, 0.168, .5, 1

    def enter_button_down(self):
        """
        Enter button down pressed event
        :return: None
        """
        self.ids.enter.color = 0.01, 0.168, .5, 1

    @staticmethod
    def set_admin_events_screen(screen):
        """
        Set the name of the screen to transition to when the password is correct
        :param screen: Name of the screen to transition to
        :return: None
        """
        global ADMIN_EVENTS_SCREEN
        ADMIN_EVENTS_SCREEN= screen

    @staticmethod
    def set_transition_back_screen(screen):
        """
        Set the screen to transition back to when the "Back to Game" button is pressed
        :param screen: Name of the screen to transition back to
        :return: None
        """
        global TRANSITION_BACK_SCREEN
        TRANSITION_BACK_SCREEN = screen

    @staticmethod
    def set_password(pswd):
        """
        Change the default password
        :param pswd: New password
        :return: None
        """
        global PASSWORD
        PASSWORD = pswd

    @staticmethod
    def change_main_screen_name(name):
        """
        Change the name of the screen to add the hidden button to go to the admin screen

        NOTE: This only needs to be run ONCE, once it is called with the new name you can remove the call from your code
        :param name: Name of the main screen of the UI
        :return: None
        """
        if name == '':
            return

        with open(passcode_screen_path) as file:
            data = file.readlines()

        data[198] = '<' + name + '>\n'

        with open(passcode_screen_path, 'w') as file:
            file.writelines(data)

