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
        """
        Specifies the background_color, background_normal, and size_hint for all instances
        :param kwargs: Arguments passed to the Button Instance
        """
        self.background_color = (0, 0, 0, 0)
        self.background_normal = ''
        self.size_hint = (None, None)
        self.original_colors = [0, 0, 0, 0]
        super(DPEAButton, self).__init__(**kwargs)

    def on_press(self):
        """
        Overrides the Button default on_press to darken the color of the button.
        :return: None
        """
        super(DPEAButton, self).on_press()
        self.original_colors = self.color
        self.color = [i * 0.7 for i in self.original_colors]

    def on_release(self):
        """
        Overrides the Button default on_release to revert the buttons color back to its original color
        :return: None
        """
        super(DPEAButton, self).on_release()
        self.color = self.original_colors
