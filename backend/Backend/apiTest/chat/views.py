from django.shortcuts import render
from .dbUtils import  get_Global_Chat, addTest
from django.http import JsonResponse
import json
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view

# Create your views here.

def index(request):
    return render(request, 'chat/index.html')

def room(request, room_name):
    return render(request, 'chat/room.html', {"room_name":room_name})

@api_view(['POST'])
def global_chat(request):
    
    # Fetch messages
    allMessages = get_Global_Chat(0)
    
    # Check if messages were found
    if not allMessages:  # Simplified way to check if the list is empty
        return JsonResponse({"error_level": 1})
    
    # Return the messages as JSON
    return JsonResponse({"messages": allMessages}, safe=False)

def addtestApi(request):
    try:
        # Check if 'message' is in query parameters
        message = request.GET.get("message")
        
        if not message:
            return JsonResponse({"error": "Message data not found"}, status=400)
        
        addTest(message)
        
        return JsonResponse({"response": "Message received successfully", "message": message})
    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

@api_view(['POST'])
def get_messages(request):
    return JsonResponse({"response": "Message received successfully", "message": "message"})
