from kivy.lang import Builder
from kivy.uix.screenmanager import Screen


PASSWORD = '7266'
userPW = ''

Builder.load_file('DPEAButton.kv')
Builder.load_file('AdminScreen.kv')


class AdminScreen(Screen):

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
            self.parent.current = 'examples'

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
