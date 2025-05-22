import random
import string
from django.http import JsonResponse

room_names = {}

def generate_room_name(mod, length=10):
    letters = string.ascii_letters
    if mod == "multiple_player":
        for room_name, room_info in room_names.items():
            if room_info['mod'] == mod and room_info['players'] < 2:
                room_info['players'] += 1
                return room_name
        while True:
            room_name = ''.join(random.choice(letters) for i in range(length))
            if room_name not in room_names:
                room_names[room_name] = {'mod': mod, 'players': 1}
                return room_name
    else:
        while True:
            room_name = ''.join(random.choice(letters) for i in range(length))
            if room_name not in room_names:
                room_names[room_name] = {'mod': mod, 'players': 1}
                return room_name

def get_all_rooms():
    return room_names

def discrement(room_name):
    if room_name in room_names:
        room_names[room_name]['players'] -= 1

def delete_room(room_name):
    print(room_name)
    if room_name in room_names:
        del room_names[room_name]
        return True
    return False