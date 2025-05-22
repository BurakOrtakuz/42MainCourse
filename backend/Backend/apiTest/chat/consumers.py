# chat/consumers.py
import json
from channels.generic.websocket import AsyncWebsocketConsumer
from UserManagement.security import verify_access_token_str
from .dbUtils import add_message

class ChatConsumer(AsyncWebsocketConsumer):
	async def connect(self):
		await self.channel_layer.group_add("global", self.channel_name)

		await self.accept()
	async def disconnect(self, close_code):
		# Leave room group
		await self.channel_layer.group_discard("global", self.channel_name)

	# Receive message from WebSocket
	async def receive(self, text_data):
		"""Handle messages received from WebSocket."""
		try:
			text_data_json = json.loads(text_data)
			action = text_data_json.get("ACTION")  # Join, Leave, or Message
			room_name = text_data_json.get("CHANNEL")
			message = text_data_json.get("MESSAGE")
			username = verify_access_token_str(self.scope['cookies'].get("access_token")).get("username")
			if action == "JOIN":
				await self.channel_layer.group_add(room_name, self.channel_name)
				await self.channel_layer.group_send(
					room_name,
					{"type": "online_status", "error_level":0,"username": username, "room_name": room_name, "JOIN": True},
				)
			elif action == "LEAVE":
				await self.channel_layer.group_discard(room_name, self.channel_name)
				await self.channel_layer.group_send(
					room_name,
					{"type": "online_status","error_level":0, "username": username, "room_name": room_name, "JOIN": False},
				)
			elif action == "MESSAGE":
				error_level = add_message(room_name, username, message)
				await self.channel_layer.group_send(
					room_name,
					{"type": "chat_message","error_level":error_level, "username": username, "room_name": room_name, "message": message},
				)
		except Exception as e:
			await self.send(text_data=json.dumps({"error_level": 3, "error_message": str(e)}))

	# Receive message from room group
	async def chat_message(self, event):
		message = event["message"]
		type = event["type"]
		room_name = event["room_name"]
		username = event["username"]
		error_level = event["error_level"]
		# Send message to WebSocket
		await self.send(text_data=json.dumps({"message": message,"error_level":error_level, "type": type, "room_name": room_name, "username": username}))