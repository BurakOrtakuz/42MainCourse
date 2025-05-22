import random
import string
from .utils import generate_room_name

tournament = {}
DEFAULT_PLAYER_COUNT = 7
def set_room(room_name):
    tournament[room_name] = {
        'players': [],
        'player_number': 0,
        'new_player': False,
        'game': None,
        'room1': None,
        'room2': None,
        'room3': None,
        'stage': 1
    }
    for _ in range(0, DEFAULT_PLAYER_COUNT):
        tournament[room_name]['players'].append(' ')


def generate_room_name_pro(length=9):
    letters = string.ascii_letters
    while True:
        room_name = ''.join(random.choice(letters) for i in range(length))
        if room_name not in tournament:
            set_room(room_name)
            return room_name
        
def join_room(room_name, username):
    if room_name in tournament:
        if tournament[room_name]['player_number'] >= DEFAULT_PLAYER_COUNT:
            return False
        for i in range(DEFAULT_PLAYER_COUNT):
            if tournament[room_name]['players'][i] == ' ':
                tournament[room_name]['players'][i] = username
                break
        tournament[room_name]['player_number'] += 1
        tournament[room_name]['new_player'] = True
        return True

def leave_room(room_name, username):
    if room_name in tournament:
        if username in tournament[room_name]['players']:
            tournament[room_name]['player_number'] -= 1
            for i in range(DEFAULT_PLAYER_COUNT):
                if tournament[room_name]['players'][i] == username:
                    tournament[room_name]['players'][i] = ' '
                    break
            tournament[room_name]['new_player'] = True
            if tournament[room_name]['player_number'] == 0:
                del tournament[room_name]
            return True
    return False

def check_available():
    for room in tournament:
        if tournament[room]['player_number'] <= 4:
            return room
    return None

def add_player(username):
    room_name = check_available()
    if room_name is None:
        room_name = generate_room_name_pro()
    join_room(room_name, username)
    return room_name

def get_players(room_name):
    if room_name in tournament:
        return tournament[room_name]['players']
    return None
def get_stage(room_name):
    if room_name in tournament:
        return tournament[room_name]['stage']
def get_new_player(room_name):
    if room_name in tournament:
        if 'new_player' in tournament[room_name]:
            tournament[room_name]['new_player'] = False
            return tournament[room_name]['new_player']
    return None

def get_player_size(room_name):
    if room_name in tournament:
        return int(tournament[room_name]['player_number'])
    return -1

def start_tournament_pro(room_name, username):
    if room_name in tournament:
        if tournament[room_name]['stage'] == 1:
            if username == tournament[room_name]['players'][0]:
                return generate_room_name('multiple_player')
            elif username == tournament[room_name]['players'][1]:
                return generate_room_name('multiple_player')
            elif username == tournament[room_name]['players'][2]:
                return generate_room_name('multiple_player')
            elif username == tournament[room_name]['players'][3]:
                return generate_room_name('multiple_player')
            else:
                return "False"
        elif tournament[room_name]['stage'] == 2 or tournament[room_name]['stage'] == 3:
                return generate_room_name('multiple_player')
        else:
            return "False"
    return "False"



def add_winner(room_name, winner):
    if room_name in tournament:
        if tournament[room_name]['stage'] < 3:
            if tournament[room_name]['players'][0] == winner:
                tournament[room_name]['players'][4] = winner
            elif tournament[room_name]['players'][1] == winner:
                tournament[room_name]['players'][4] = winner
            elif tournament[room_name]['players'][2] == winner:
                tournament[room_name]['players'][5] = winner
            elif tournament[room_name]['players'][3] == winner:
                tournament[room_name]['players'][5] = winner
        elif tournament[room_name]['stage'] == 3:
            tournament[room_name]['players'][6] = winner
    tournament[room_name]['stage'] += 1
    return False

def check_tournament_finished(room_name):
    if room_name in tournament:
        if tournament[room_name]['stage'] == 4:
            return True
    return False