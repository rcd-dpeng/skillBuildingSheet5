from kivy.lang import Builder
from kivy.uix.button import Button
from kivy.properties import ObjectProperty
import os.path

dpea_button_kv_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "", "DPEAButton.kv")
Builder.load_file(dpea_button_kv_path)


class DPEAButton(Button):
    """
    DPEAButton class
    """
    shadow_image_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "images", "shadow.png")
    shadow_path = ObjectProperty(shadow_image_path)

    def __init__(self, **kwargs):
        self.background_color = (0, 0, 0, 0)
        self.background_normal: ''
        self.size_hint: (None, None)
        super(DPEAButton, self).__init__(**kwargs)
