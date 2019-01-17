from kivy.lang import Builder
from kivy.uix.screenmanager import Screen
from kivy.animation import Animation
import pkg_resources
from threading import Thread

pidev_package = __name__
pause_screen_path = '/'.join(('', 'PauseScreen.kv'))

Builder.load_file(pkg_resources.resource_filename(pidev_package, pause_screen_path))


class PauseScreen(Screen):
    sm = None
    text = None
    seconds = None
    thread = None

    @staticmethod
    def pause(screen_manager, text, seconds):
        PauseScreen.sm = screen_manager
        PauseScreen.text = text
        PauseScreen.seconds = seconds
        thread = Thread(target=PauseScreen.start_pause())

        print(thread.is_alive())

    @staticmethod
    def start_pause():
        PauseScreen.sm.current = 'pauseScene'
        PauseScreen.sm.get_screen('pauseScene').ids.pauseText = PauseScreen.text
        load = Animation(size=(10, 10), duration=0) + \
               Animation(size=(150, 10), duration=PauseScreen.seconds)

        load.start(PauseScreen.sm.get_screen('pauseScene').ids.progress_bar)
        return

    @staticmethod
    def transition_back():
        print("here")
        #screen_manager.current = 'main'

