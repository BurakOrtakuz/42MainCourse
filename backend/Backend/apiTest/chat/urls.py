# chat/urls.py
from django.urls import path

from . import views


urlpatterns = [
    path("", views.index, name="index"),
    path("global/",views.global_chat,name="test"),
    path("get_messages/",views.get_messages,name="get_messages"),
    #path("addtest/",views.addtestApi,name="addtest"),
    #path("<str:room_name>/", views.room, name="room"),
]