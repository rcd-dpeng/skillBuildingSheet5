from kivy.lang import Builder
from kivy.uix.screenmanager import Screen
from kivy.animation import Animation
from kivy.clock import Clock
import os.path

pause_screen_kv_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "", "PauseScreen.kv")
Builder.load_file(pause_screen_kv_path)

SCREEN_MANAGER = None
TRANSITION_SCREEN = None


class PauseScreen(Screen):
    """
    Class used to pause the UI
    """
    white_image_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "images", "white.png")

    @staticmethod
    def pause(screen_manager, pause_scene_name, transition_back_screen, text, seconds):
        """
        Pause the UI for a given amount of time
        :param screen_manager: The screen manager used for the UI
        :param pause_scene_name: The name of the PauseScreen when added as a widget
        :param transition_back_screen: The name of the screen to transition to when complete
        :param text: The text to display on screen while paused
        :param seconds: The number of seconds to pause the UI for
        :return: None
        """
        global SCREEN_MANAGER, TRANSITION_SCREEN

        SCREEN_MANAGER = screen_manager
        TRANSITION_SCREEN = transition_back_screen

        screen_manager.current = pause_scene_name
        screen_manager.get_screen('pauseScene').ids.pauseText = text
        load = Animation(size=(10, 10), duration=0) + \
                    Animation(size=(150, 10), duration=seconds)
        load.start(screen_manager.get_screen(pause_scene_name).ids.progress_bar)

        Clock.schedule_once(lambda dt: PauseScreen.transition_back(), seconds)

    @staticmethod
    def transition_back():
        """
        Transition the UI back from the PauseScreen
        :return: None
        """
        global SCREEN_MANAGER
        SCREEN_MANAGER.current = TRANSITION_SCREEN

