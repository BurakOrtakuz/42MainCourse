from django.urls import re_path

from .consumers.one_player_consumer import OnePlayerConsumer
from .consumers.two_player_consumer import TwoPlayerConsumer
from .consumers.multiple_player_consumer import MultiplePlayerConsumer

websocket_urlpatterns = [ 
    re_path(r"ws/pong/one_player/(?P<room_name>\w+)/$", OnePlayerConsumer.as_asgi()),
    re_path(r"ws/pong/two_player/(?P<room_name>\w+)/$", TwoPlayerConsumer.as_asgi()),
    re_path(r"ws/pong/multiple_player/(?P<room_name>\w+)/$", MultiplePlayerConsumer.as_asgi()),
]