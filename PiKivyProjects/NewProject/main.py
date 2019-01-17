from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from pidev import MixPanel
from pidev.kivy import PassCodeScreen
from pidev.kivy import PauseScreen
from time import sleep

PROJECT_TOKEN = "x"
MIXPANEL = MixPanel("Project Name", PROJECT_TOKEN)

SCREEN_MANAGER = ScreenManager()


class ProjectNameGUI(App):
    def build(self):
        return SCREEN_MANAGER


Window.clearcolor = (1, 1, 1, 1)  # White


class MainScreen(Screen):

    @staticmethod
    def exit_program():
        quit()

    def pressed(self):
        PauseScreen.pause(SCREEN_MANAGER, 'test', 10)


Builder.load_file('main.kv')
SCREEN_MANAGER.add_widget(MainScreen(name='main'))
SCREEN_MANAGER.add_widget(PassCodeScreen(name='admin'))
SCREEN_MANAGER.add_widget(PauseScreen(name='pauseScene'))
"""
MixPanel
"""


def send_event(event_name):
    """
    Send an event to MixPanel without properties
    :param event_name: Name of the event
    :return: None
    """
    global MIXPANEL

    event = MixPanel("My Project", PROJECT_TOKEN)
    event.set_event_name(event_name)
    event.send_event()


if __name__ == "__main__":
    send_event("Project Initialized")
    ProjectNameGUI().run()
