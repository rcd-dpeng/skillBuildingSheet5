# Kivy UI Libraries for the DPEA

These are the libraries to be used for all Mechatronics projects that require the use of Python with Kivy. Please refer to this doc as well as the comments in the code files themselves for help on how to use these libraries/Kivy in general

## DPEAButton

A button that's a colored rounded rectangle with a drop shadow. Text is bold white with a black outline.

### Required setup

Build the DPEAButton.kv into your main python file (the one you run to launch the UI) by using ```Builder.load_file('DPEAButton.kv')```

In your kivy file, add these four required lines of code to declare a DPEADButton:
```
DPEAButton:
      background_color: 0, 0, 0, 0
      background_normal: ''
      size_hint: None, None
```
These three lines allow you to specify the button's size explicitly and makes the background for the button transparent

### Appearance Customization

You can specify the ```text```, ```color```, ```size```, and ```position```. Here's an example of what your code should look like now:
```
DPEAButton:
      background_color: 0, 0, 0, 0
      background_normal: ''
      size_hint: None, None
      text: 'Hello World!'
      size: 40, 40
      center_x: root.width * 0.97
      center_y: root.height * 0.955
      color: 1, 0, 0, 1
```

### Touch event handling
