from kivy.lang import Builder
from kivy.uix.screenmanager import Screen
from kivy.animation import Animation
import pkg_resources
from time import time

pidev_package = __name__
pause_screen_path = '/'.join(('', 'PauseScreen.kv'))

Builder.load_file(pkg_resources.resource_filename(pidev_package, pause_screen_path))


def pause(text, seconds, screen_manager, pause_scene_name):
    screen_manager.transition.direction = 'left'
    screen_manager.current = pause_scene_name
    screen_manager.current_screen.ids.pauseText.text = text
    load = Animation(size=(10, 10), duration=0) + \
           Animation(size=(150, 10), duration=seconds)

    load.start(screen_manager.current_screen.ids.progressBar)
    load.on_complete(lambda : print("here"))


class PauseScreen(Screen):
    @staticmethod
    def pause(screen_manager, text, seconds):
        screen_manager.current = 'pauseScene'
        screen_manager.get_screen('pauseScene').ids.pauseText = text
        load = Animation(size=(10, 10), duration=0) + \
               Animation(size=(150, 10), duration=seconds)

        load.start(screen_manager.get_screen('pauseScene').ids.progress_bar)

        # end = time() + seconds
        # while time() < end:
        #     continue

        print("here")


    @staticmethod
    def transition_back():
        print("here")
        #screen_manager.current = 'main'

