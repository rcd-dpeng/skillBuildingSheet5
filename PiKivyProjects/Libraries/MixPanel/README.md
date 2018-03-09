# dpeaMixPanel

# Python module to send analytic Events/Properties to MixPanel

# Example

from dpea.utilities import MixPanel

INFINITY_MIRROR_TOKEN = "yourMixPanelProjectToken"

#
# Sends a "Color Selected" event with a color property of 'blue'
#
colorEvent = MixPanel("Infinity Mirror", INFINITY_MIRROR_TOKEN)

colorEvent.setEventName("Color Selected");

colorEvent.addProperty("color", "blue");

colorEvent.sendEvent()

#
# Sends a "Demo Mode" event with a 'duration' property of 232 seconds
#
demoEvent = MixPanel("Infinity Mirror", INFINITY_MIRROR_TOKEN)

demoEvent.setEventName("Demo Mode");

demoEvent.addProperty("duration", 232);

demoEvent.sendEvent()

