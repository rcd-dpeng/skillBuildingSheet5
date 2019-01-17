from kivy.lang import Builder
from kivy.uix.screenmanager import Screen
import pkg_resources

pidev_package = __name__
dpea_button_path = '/'.join(('', 'DPEAButton.kv'))
admin_screen_path = '/'.join(('', 'PassCodeScreen.kv'))

PASSWORD = '7266'
userPW = ''

Builder.load_file(pkg_resources.resource_filename(pidev_package, dpea_button_path))
Builder.load_file(pkg_resources.resource_filename(pidev_package, admin_screen_path))

ADMIN_EVENTS_SCREEN = None
TRANSITION_BACK_SCREEN = 'main'

"""
Class to display a passcode on screen to advance to admin screen
"""


class PassCodeScreen(Screen):
    def add_num(self, num):
        global userPW
        self.ids.pw.text += '* '
        userPW += str(num)

    def remove_num(self):
        global userPW
        self.ids.pw.text = self.ids.pw.text[:len(self.ids.pw.text) - 2]
        userPW = userPW[:len(userPW) - 1]

    def check_pass(self):
        global userPW
        if PASSWORD == userPW:
            self.ids.pw.text = ' '
            userPW = ''
            self.parent.current = ADMIN_EVENTS_SCREEN

    def reset_colors(self):
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
        self.ids.back.color = 0.01, 0.168, .5, 1

    def transition_back(self):
        self.parent.current = TRANSITION_BACK_SCREEN

    def one_button_down(self):
        self.ids.one.color = 0.01, 0.168, .5, 1

    def two_button_down(self):
        self.ids.two.color = 0.01, 0.168, .5, 1

    def three_button_down(self):
        self.ids.three.color = 0.01, 0.168, .5, 1

    def four_button_down(self):
        self.ids.four.color = 0.01, 0.168, .5, 1

    def five_button_down(self):
        self.ids.five.color = 0.01, 0.168, .5, 1

    def six_button_down(self):
        self.ids.six.color = 0.01, 0.168, .5, 1

    def seven_button_down(self):
        self.ids.seven.color = 0.01, 0.168, .5, 1

    def eight_button_down(self):
        self.ids.eight.color = 0.01, 0.168, .5, 1

    def nine_button_down(self):
        self.ids.nine.color = 0.01, 0.168, .5, 1

    def zero_button_down(self):
        self.ids.zero.color = 0.01, 0.168, .5, 1

    def backspace_button_down(self):
        self.ids.backspace.color = 0.01, 0.168, .5, 1

    def enter_button_down(self):
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

        with open(pkg_resources.resource_filename(pidev_package, admin_screen_path)) as file:
            data = file.readlines()

        data[198] = '<' + name + '>\n'

        with open(pkg_resources.resource_filename(pidev_package, admin_screen_path), 'w') as file:
            file.writelines(data)

