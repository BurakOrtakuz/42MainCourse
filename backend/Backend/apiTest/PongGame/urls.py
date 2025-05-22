from django.urls import path
from . import views

urlpatterns = [
    path("one_player/", views.one_player, name="one_player"),
    path("two_player/", views.two_player, name="two_player"),
    path("multiple_player/", views.multiple_player, name="multiple_player"),
    path("add_player_tournament/", views.add_player_tournament, name="add_player_tournament"),
    path("wait_update/", views.wait_update, name="wait_update"),
    path("exit_from_tournament/", views.exit_from_tournament, name="exit_from_tournament"),
    path("start_tournament/", views.start_tournament, name="start_tournament"),
    path("check_tournament/", views.check_tournament, name="check_tournament"),
]
