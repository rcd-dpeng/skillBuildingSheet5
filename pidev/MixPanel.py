import requests
import base64
import json
from threading import Thread


class MixPanel(object):
    MIXPANEL_URL = "http://api.mixpanel.com/track/?data="
    properties = {}

    def __init__(self, project_name, token):
        self.properties.clear()
        self.add_property("token", token)
        self.add_property("distinct_id", project_name)
        self.event_name = None

    def set_event_name(self, event_name):
        self.event_name = event_name

    def add_property(self, key, value):
        self.properties[key] = value

    def http_post_request(self, url):
        requests.post(url)
    
    def send_event(self):
        event = {}
        event['event'] = self.event_name
        event['properties'] = self.properties

        data = json.dumps(event)
        url = self.MIXPANEL_URL + base64.b64encode(data.encode("utf-8")).decode("utf-8")
        request = Thread(target=self.http_post_request, args=(url,))
        request.start()

