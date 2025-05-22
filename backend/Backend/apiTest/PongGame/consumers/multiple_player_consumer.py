import json
from channels.generic.websocket import AsyncWebsocketConsumer
from UserManagement.security import verify_access_token_str
from asyncio import sleep, create_task
from django.db import connection
from ..utils import delete_room
from ..utils import get_all_rooms
from django.http import JsonResponse
from ..utils import discrement
import random



### GLOBAL DATA ###
room_states = {}
LIMIT_X = 8.3

### Set ball position and orientation after goal
def reset_room_state(numberOfUser, left, right, sdx, pln, prn, whowin):
    return {
        'ballX': 0.0,
        'ballZ': 0.0,
        'startDirectionX': -sdx,
        'ballSpeedX': -sdx * 0.05,
        'ballSpeedZ': random.uniform(-0.02, 0.02),
        'leftPaddleZ': 0.0,
        'rightPaddleZ': 0.0,
        'numberOfUser': numberOfUser,
        'scoreRight': right,
        'scoreLeft': left,
        'room_clear': 0,
        'playerLeftName': pln,
        'playerRightName': prn,
        'isFinished': False,
        'whoWin': whowin
    }

### Set ball position and orientation at the beginning of the game
def default_room_state():
    flag = random.choice([-1, 1])
    return {
        'ballX': 0.0,
        'ballZ': 0.0,
        'startDirectionX': flag,
        'ballSpeedX': flag * 0.05,
        'ballSpeedZ': 0,
        'leftPaddleZ' : 0.0,
        'rightPaddleZ': 0.0,
        'numberOfUser': 1,
        'scoreRight': 0,
        'scoreLeft': 0,
        'room_clear': 1,
        'playerLeftName': "",
        'playerRightName': "",
        'isFinished': False,
        'whoWin': 0
    }

class MultiplePlayerConsumer(AsyncWebsocketConsumer):

    ### Let the ball for 0.4 second to continue after a goal
    async def ending_animation(self,room_name):
        time = 0
        while time < 0.4:
            if (room_states[room_name]['numberOfUser'] == 0):
                break
            room_states[room_name]['ballX'] += room_states[room_name]['ballSpeedX']
            room_states[room_name]['ballZ'] += room_states[room_name]['ballSpeedZ']

            game_state = room_states[self.room_group_name]
            await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'game_state_update',
                'game_state': game_state
            }
        )
            await sleep(0.005)
            time += 0.005

    ### Update ball position taking care of collision
    async def update_ball_position(self,room_name):
        while True:
            if (room_states[room_name]['numberOfUser'] == 0):
                room_states[room_name]['room_clear'] += 1
                break
            room_states[room_name]['ballX'] += room_states[room_name]['ballSpeedX']
            room_states[room_name]['ballZ'] += room_states[room_name]['ballSpeedZ']

            if room_states[room_name]['ballX'] > LIMIT_X or room_states[room_name]['ballX'] < -LIMIT_X:
                if room_states[room_name]['ballX'] > LIMIT_X:
                    PaddleZ = 'rightPaddleZ'
                else :
                    PaddleZ = 'leftPaddleZ'
                if(room_states[room_name]['ballSpeedX'] < 0.2 and room_states[room_name]['ballSpeedX'] > -0.2):
                    if room_states[room_name]['ballSpeedX'] > 0:
                        room_states[room_name]['ballSpeedX'] += 0.01
                    elif room_states[room_name]['ballSpeedX'] < 0:
                        room_states[room_name]['ballSpeedX'] -= 0.01
                if room_states[room_name]['ballZ'] > (room_states[room_name][PaddleZ] - 1.5) and room_states[room_name]['ballZ'] < (room_states[room_name][PaddleZ] + 1.5):
                    room_states[room_name]['ballSpeedX'] = -room_states[room_name]['ballSpeedX']
                    paddle_center = room_states[room_name][PaddleZ]
                    delta_z = room_states[room_name]['ballZ'] - paddle_center
                    if delta_z > 0.75 and room_states[room_name]['ballSpeedZ'] < 0.10:
                        room_states[room_name]['ballSpeedZ'] += 0.02
                    elif delta_z < -0.75 and room_states[room_name]['ballSpeedZ'] > -0.10:
                        room_states[room_name]['ballSpeedZ'] -= 0.02
                else:
                    await self.ending_animation(room_name)
                    scoreLeft = room_states[room_name]['scoreLeft'] + (PaddleZ == 'rightPaddleZ')
                    scoreRight = room_states[room_name]['scoreRight'] + (PaddleZ == 'leftPaddleZ')
                    if (scoreLeft == 3):
                        room_states[room_name]['whoWin'] = room_states[room_name]['playerLeftName']
                    elif (scoreRight == 3):
                        room_states[room_name]['whoWin'] = room_states[room_name]['playerRightName']
                    room_states[room_name] = reset_room_state(room_states[room_name]['numberOfUser'], scoreLeft, scoreRight, room_states[room_name]['startDirectionX'], room_states[room_name]['playerLeftName'], room_states[room_name]['playerRightName'], room_states[room_name]['whoWin'])
                
            if room_states[room_name]['ballZ'] > 3.5 or room_states[room_name]['ballZ'] < -3.5:
                room_states[room_name]['ballSpeedZ'] = room_states[room_name]['ballSpeedZ'] * -1

            game_state = room_states[self.room_group_name]
            await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'game_state_update',
                'game_state': game_state
            }
        )
            await sleep(0.005)

    ### Sending init or on going game state to user and add 1 to total connected user number in the room
    async def connect(self):
        cookies = self.scope["cookies"]
        payload = verify_access_token_str(cookies.get('access_token'))
        if isinstance(payload, int):
            return
        username = payload.get('username')
        self.room_name = self.scope['url_route']['kwargs']['room_name']
        self.room_group_name = f'{self.room_name}'
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        if self.room_group_name not in room_states:
            room_states[self.room_group_name] = default_room_state()
            room_states[self.room_group_name]['playerRightName'] = username
        elif room_states[self.room_group_name]['playerRightName'] == username:
            discrement(self.room_group_name)
            await self.accept()
            room_states[self.room_group_name]['isFinished'] = True
            self.send(json.dumps(room_states[self.room_group_name]))
            return
        else:
            room_states[self.room_group_name]['numberOfUser'] += 1
            room_states[self.room_group_name]['room_clear'] = 0
            room_states[self.room_group_name]['playerLeftName'] = username
            create_task(self.update_ball_position(self.room_group_name))
        await self.accept()

    ### remove 1 to total connected user number in the room, if no player left, delete and discard room
    async def disconnect(self, close_code):
        if self.room_group_name in room_states:
            room_states[self.room_group_name]['isFinished'] = True
            room_states[self.room_group_name]['whoWin'] = " "
            room_states[self.room_group_name]['numberOfUser'] = 0
            while room_states[self.room_group_name]['room_clear'] < 1:
                await sleep(0.001)
            del room_states[self.room_group_name]
            await self.channel_layer.group_discard(
                    self.room_group_name,
                    self.channel_name
                )
            delete_room(self.room_group_name)

            
    ### Update Paddle position depending of received key
    async def receive(self, text_data):
        cookies = self.scope["cookies"]
        payload = verify_access_token_str(cookies.get('access_token'))
        if isinstance(payload, int):
            return
        username = payload.get('username')
        received_data = json.loads(text_data)
        movement = next(iter(received_data))
        z = 'leftPaddleZ'
        if (username == room_states[self.room_group_name]['playerLeftName']):
            z = 'leftPaddleZ'
        elif (username == room_states[self.room_group_name]['playerRightName']):
            z = 'rightPaddleZ'
        # if z == 'nonPaddleZ':
        #     return
        movement_value = received_data[movement]
        if (movement_value and room_states[self.room_group_name][z] < 3):
            room_states[self.room_group_name][z] = round(room_states[self.room_group_name][z] + 0.2, 2)
        elif (not movement_value and room_states[self.room_group_name][z] > -3):
            room_states[self.room_group_name][z] = round(room_states[self.room_group_name][z] - 0.2, 2)
        game_state = room_states[self.room_group_name]
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'game_state_update',
                'game_state': game_state
            }
        )

    async def game_state_update(self, event):
        game_state = event['game_state']
        await self.send(text_data=json.dumps(game_state))
