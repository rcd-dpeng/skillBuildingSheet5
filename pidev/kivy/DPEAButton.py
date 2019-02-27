from kivy.lang import Builder
from kivy.uix.button import Button
import os.path

dpea_button_kv_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "", "DPEAButton.kv")
Builder.load_file(dpea_button_kv_path)


class DPEAButton(Button):
    shadow_image_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "images", "shadow.png")

    def __init__(self):
        super.__init__()