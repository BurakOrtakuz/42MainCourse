from django.http import JsonResponse
import requests
import json
from django.db import connection
from django.conf import settings
from rest_framework.decorators import api_view
from django.core.cache import cache
from .security import hash_password, generate_access_token,verify_access_token
from .security import  generate_refresh_token, refresh_access_token
from .security import REFRESH_TOKEN_EXPIRY,ACCESS_TOKEN_EXPIRY, MAX_ATTEMPTS, LOCKOUT_TIME
from .twofactorauth import create_two_factor_code, get_two_factor_code, send_mail, test_send_mail

@api_view(['POST'])
def access_token_login(request):
	"""Endpoint to verify and log in using an access token."""
	try:
		payload = verify_access_token(request)
		if isinstance(payload, int):
			return refresh_access_token(request)
		elif payload == 7:
			return JsonResponse({"error_level": 7})
    
		return JsonResponse({"error_level": 0, "username": payload.get("username")})
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": f"Unexpected error: {str(e)}"})

@api_view(['POST'])
def login(request):
	try:
		data = json.loads(request.body)
		username = data.get("USERNAME")
		password = data.get("PASSWORD")
		if not username or not password:
			return JsonResponse({"error_level": 2})

		cache_key = f"login_attempts_{username}"			
		attempts = cache.get(cache_key, 0)
		if attempts == 0:
			cache.set(cache_key, 0, LOCKOUT_TIME)
		if attempts >= MAX_ATTEMPTS:
			return JsonResponse({"error_level": 4})
		with connection.cursor() as cursor:
			cursor.execute(
				"SELECT \"Password\", \"TwoFactorAuth\" FROM \"User\" WHERE \"Username\" = %s",
				[username]
			)
			user = cursor.fetchone()

			if user:
				stored_hash = user[0]
				backend_hash = hash_password(password)
				if backend_hash == stored_hash:
					if user[1] == True:
						return JsonResponse({"error_level": 8})
					access_token = generate_access_token(username,False)
					refresh_token = generate_refresh_token(username)
					response = JsonResponse({"error_level": 0, "USERNAME": username})
					response.set_cookie(
						key="access_token",
						value=access_token,
						httponly=True,
						secure=True,
						samesite="Strict",
						max_age=ACCESS_TOKEN_EXPIRY
					)
					response.set_cookie(
						key="refresh_token",
						value=refresh_token,
						httponly=True,
						secure=True,
						samesite="Strict",
						max_age=REFRESH_TOKEN_EXPIRY
					)
					cursor.execute("UPDATE \"User\" SET \"Online\" = TRUE WHERE \"Username\" = %s", [username])
					cache.delete(cache_key)
					return response
				else:
					cache.incr(cache_key, 1)
					if attempts == 0:
						cache.expire(cache_key, 300)
					return JsonResponse({"error_level": 1})
			else:
				return JsonResponse({"error_level": 1})
	except json.JSONDecodeError:
		return JsonResponse({"error_level": 2})
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": str(e)})

@api_view(['POST'])
def logout(request):
	try:
		payload = verify_access_token(request)
		if isinstance(payload,int):
			return JsonResponse({"error_level": payload})
		username = payload.get("username")
		with connection.cursor() as cursor:
			cursor.execute("UPDATE \"User\" SET \"Online\" = FALSE WHERE \"Username\" = %s", [username])
		response = JsonResponse({"error_level": 0, "USERNAME": username})
		response.delete_cookie("access_token")
		response.delete_cookie("refresh_token")
		return response
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": str(e)})

@api_view(['POST'])
def register(request):
	try:
		data = json.loads(request.body)
		username = data.get("USERNAME")
		email = data.get("EMAIL")
		raw_password = data.get("PASSWORD")
		if not username or not email or not raw_password:
			return JsonResponse({"error_level": 2})
		password = hash_password(raw_password)
		with connection.cursor() as cursor:
			cursor.execute("SELECT \"Username\" FROM \"User\" WHERE \"Username\" = %s", [username])
			user = cursor.fetchall()
			if user:
				return JsonResponse({"error_level": 1})
			else:
				cursor.execute("INSERT INTO \"User\" (\"Username\", \"Password\", \"Email\") VALUES (%s, %s, %s)", [username, password,email])
				return JsonResponse({"error_level": 0})
	except json.JSONDecodeError:
		return JsonResponse({"error_level":2})
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": str(e)})

@api_view(['GET'])
def intra_url(request):
	INTRAURL = (
		f"{settings.INTRA_OAUTH_URL}"
		f"?client_id={settings.INTRA_UID}"
		f"&redirect_uri={settings.INTRA_REDIRECT_URL}"
		f"&response_type=code"
		f"&scope=public"
	)
	return JsonResponse({"URL": INTRAURL})

@api_view(['POST'])
def intra_login(REQ):
	DATA = REQ.data
	CODE = DATA.get('CODE')

	try:
		TOKENRESPONSE = requests.post(
			f"{settings.INTRA_TOKEN_URL}",
			data={
				'grant_type': 'authorization_code',
				'client_id': settings.INTRA_UID,
				'client_secret': settings.INTRA_SECRET_KEY,
				'code': CODE,
				'redirect_uri': settings.INTRA_REDIRECT_URL,
			})
	except Exception as e:
		return JsonResponse("error: token response not resived")
	TOKENDATA = TOKENRESPONSE.json()
	INTRA_ACCESS_TOKEN = TOKENDATA.get('access_token')
		
	if not INTRA_ACCESS_TOKEN:
		return JsonResponse({
			"error_level": 2, 
			"error_message": "No access token received"
		})

	USERRESPONSE = requests.get(
		f"{settings.INTRA_USER_URL}",
		headers={'Authorization': f'Bearer {INTRA_ACCESS_TOKEN}'}
	)
	USERDATA = USERRESPONSE.json()
	email = USERDATA.get('email')
	username = USERDATA.get('login')
	name = USERDATA.get('first_name')
	surname = USERDATA.get('last_name')
	image = USERDATA.get('image').get('link')
	REFRESH_TOKEN = generate_refresh_token(username)
	ACCESS_TOKEN = generate_access_token(username, True)
 
	try:
		with connection.cursor() as cursor:
			cursor.execute("SELECT \"Username\" FROM \"User\" WHERE \"Username\" = %s", [username])
			user = cursor.fetchall()
			if not user:
				cursor.execute(
					"""INSERT INTO \"User\" 
     				(\"Username\", \"Name\", \"Surname\",\"Email\",\"ProfilePhoto\", \"Online\") 
         			VALUES (%s, %s, %s, %s, %s, TRUE)""", 
					[username, name, surname, email, image]
				)
			response = JsonResponse({"error_level": 0, "USERNAME": username})
			response.set_cookie(
				key="access_token",
				value=ACCESS_TOKEN,
				httponly=True,
				secure=True,
				samesite="Strict",
				max_age=ACCESS_TOKEN_EXPIRY
			)
			response.set_cookie(
				key="refresh_token",
				value=REFRESH_TOKEN,
				httponly=True,
				secure=True,
				samesite="Strict",
			)
			return response
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": str(e)})


@api_view(['POST'])
def create_2fa_code(request):
	try:
		username = request.data.get("USERNAME")
		if not username:
			return JsonResponse({"error_level": 2})
		with connection.cursor() as cursor:
			code = """SELECT "Email" FROM "User" WHERE "Username" = %s"""
			cursor.execute(code, [username])
			user = cursor.fetchall()
			if not user:
				return JsonResponse({"error_level": 1})
			mail_send_code =send_mail(username, user[0][0])
		return mail_send_code
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": str(e)})

@api_view(['GET'])
def server_health(request):
	return JsonResponse({"_": 1})

@api_view(['POST'])
def verify_2fa_code(request):
	data = json.loads(request.body)
	username = data.get("USERNAME")
	with connection.cursor() as cursor:
		code = """SELECT "Email" FROM "User" WHERE "Username" = %s"""
		cursor.execute(code, [username])
		user = cursor.fetchall()
		if not user:
			return JsonResponse({"error_level": 1})
	user_two_factor_code = data.get("CODE")
	real_two_factor_code = get_two_factor_code(username)
	if user_two_factor_code == real_two_factor_code:
		access_token = generate_access_token(username,False)
		refresh_token = generate_refresh_token(username)
		response = JsonResponse({"error_level": 0, "USERNAME": username})
		response.set_cookie(
			key="access_token",
			value=access_token,
			httponly=True,
			secure=True,
			samesite="Strict",
			max_age=ACCESS_TOKEN_EXPIRY
		)
		response.set_cookie(
			key="refresh_token",
			value=refresh_token,
			httponly=True,
			secure=True,
			samesite="Strict",
			max_age=REFRESH_TOKEN_EXPIRY
		)
		return response
	else:
		return JsonResponse({"error_level": 9})

@api_view(['POST'])
def two_factor_permit(request):
	payload = verify_access_token(request)
	if isinstance(payload, int):
		return JsonResponse({"error_level": payload})
	username = payload.get("username")
	data = json.loads(request.body)
	state = bool(data.get("STATE"))
	try:
		with connection.cursor() as cursor:
			cursor.execute("UPDATE \"User\" SET \"TwoFactorAuth\" = %s WHERE \"Username\" = %s", [state,username])
			return JsonResponse({"error_level": 0})
	except Exception as e:
		return JsonResponse({"error_level": 3, "error_message": str(e)})

@api_view(['POST'])
def get_2fa_state(request):
	payload = verify_access_token(request)
	if isinstance(payload, int):
		return JsonResponse({"error_level": payload})
	username = payload.get("username")
	with connection.cursor() as cursor:
		cursor.execute("SELECT \"TwoFactorAuth\" FROM \"User\" WHERE \"Username\" = %s", [username])
		state = cursor.fetchone()
		return JsonResponse({"error_level": 0, "FA": state[0]})

