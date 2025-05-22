from django.shortcuts import render
from django.http import JsonResponse
from rest_framework.decorators import api_view
from UserManagement.security import verify_access_token, add_access_token
from .utils import generate_room_name
from django.db import connection
from .tournamete import add_player,get_players,get_player_size,leave_room,start_tournament_pro
from .tournamete import check_tournament_finished
from .tournamete import add_winner, get_stage
import json

@api_view(['POST'])
def one_player(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    room_name = generate_room_name("one_player")
    if not room_name:
        return JsonResponse({"error_level": 1})
    
    response_data.update({"error_level": 0, "room_name": room_name})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def two_player(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    room_name = generate_room_name("two_player")
    response_data.update({"error_level": 0, "room_name": room_name})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def multiple_player(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    room_name = generate_room_name("multiple_player")
    response_data.update({"error_level": 0, "room_name": room_name})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def add_player_tournament(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    username = payload.get("username")
    room_name = add_player(username)
    response_data.update({"error_level": 0, "room_name": room_name, "players": get_players(room_name)})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def wait_update(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    username = payload.get("username")
    data = json.loads(request.body)
    room_name = data.get("ROOM_NAME")
    players = get_players(room_name)
    error_level = 1
    player_size = get_player_size(room_name)
    stage = get_stage(room_name)
    if player_size == 4 and (stage == 1 or stage == 3):
        error_level = 0
    response_data.update({"error_level": error_level,"current_player":username, "room_name": room_name,"players": players})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def exit_from_tournament(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    data = json.loads(request.body)
    room_name = data.get("ROOM_NAME")
    username = payload.get("username")
    value = leave_room(room_name,username)
    response_data.update({"error_level": 0, "value": value})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def start_tournament(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    data = json.loads(request.body)
    room_name = data.get("ROOM_NAME")
    username = payload.get("username")
    tournamete_room = start_tournament_pro(room_name,username)
    response_data.update({"error_level": 0, "room_name":tournamete_room})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def game_over(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    data = json.loads(request.body)
    room_name = data.get("ROOM_NAME")
    username = payload.get("username")
    response_data.update({"error_level": 0, "room_name": room_name})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response

@api_view(['POST'])
def check_tournament(request):
    payload = verify_access_token(request)
    response_data = {}
    response = JsonResponse(response_data)
    if isinstance(payload, int):
        control = add_access_token(response, request)
        if isinstance(control, int):
            return JsonResponse({"error_level": control})
    data = json.loads(request.body)
    username = payload.get("username")
    room_name = data.get("ROOM_NAME")
    winner = data.get("WINNER")
    add_winner(room_name, winner)
    check_available = check_tournament_finished(room_name)
    response_data.update({"error_level": 0,"who_am_i":username, "check_available": check_available})
    response = JsonResponse(response_data)
    add_access_token(response, request)
    return response