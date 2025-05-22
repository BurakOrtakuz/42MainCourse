import os
import hashlib
import jwt
from datetime import datetime, timedelta, timezone
from django.http import JsonResponse
# Fetch the SALT environment variable
SALT = os.getenv("SALT")
SECRET_KEY = os.getenv("SECRET_KEY")

TOKEN_EXPIRY = 3600
MAX_ATTEMPTS = 100
LOCKOUT_TIME = 900  # seconds (15 minutes)
ACCESS_TOKEN_EXPIRY = 300  # 5 minutes in seconds
REFRESH_TOKEN_EXPIRY = 604800 # 7 days in seconds
# Raise an error if the SALT is not set
if not SALT or not SECRET_KEY:
    raise ValueError("SALT environment or SECRET_KEY environment variable is not set!")

def hash_password(password):
    """Hash the password with the shared salt using SHA-256."""
    salted_password = password + SALT
    return hashlib.sha256(salted_password.encode()).hexdigest()


def generate_access_token(username, intra_login):
    """Generate a JWT access token."""
    now = datetime.now(timezone.utc)
    payload = {
        "username": username,
        "type": "access",
        "intra_login": intra_login,
        "exp": (now + timedelta(seconds=ACCESS_TOKEN_EXPIRY)).timestamp(),
        "iat": now.timestamp()
    }
    return jwt.encode(payload, SECRET_KEY, algorithm="HS256")

def verify_access_token(request):
    """Verify the access token in cookies."""
    token = request.COOKIES.get("access_token")
    if not token:
        return 5
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=["HS256"])
        return payload
    except jwt.ExpiredSignatureError:
        return 6
    except jwt.InvalidTokenError:
        return 7
    
def generate_refresh_token(username):
    """Generate a JWT refresh token."""
    now = datetime.now(timezone.utc)
    payload = {
        "username": username,
        "type": "access",
        "exp": (now + timedelta(seconds=REFRESH_TOKEN_EXPIRY)).timestamp(),
        "iat": now.timestamp()
    }
    return jwt.encode(payload, SECRET_KEY, algorithm="HS256")

def verify_refresh_token(request):
    """Verify the refresh token in cookies."""
    token = request.COOKIES.get("refresh_token")
    if not token:
        return 5
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=["HS256"])
        return payload
    except jwt.ExpiredSignatureError:
        return 6
    except jwt.InvalidTokenError:
        return 7
def verify_access_token_str(token):
    """Verify the access token in cookies."""
    if not token:
        return 5
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=["HS256"])
        return payload
    except jwt.ExpiredSignatureError:
        return 6
    except jwt.InvalidTokenError:
        return 7
def refresh_access_token(request):
    """Refresh the access token."""
    refresh_token = verify_refresh_token(request)
    if isinstance(refresh_token, (int,float)):
        return JsonResponse({"error_level": refresh_token})
    username = refresh_token.get("username")
    intra_login = refresh_token.get("intra_login")
    access_token = generate_access_token(username, intra_login)
    response = JsonResponse({"error_level": 0, "USERNAME": username})
    response.set_cookie(
        key="access_token",
        value=access_token,
        httponly=True,
        secure=True,
        samesite="Strict",
        max_age=ACCESS_TOKEN_EXPIRY
    )
    return response

def add_access_token(response, request):
    """Refresh the access token."""
    refresh_token = verify_refresh_token(request)
    if isinstance(refresh_token, (int,float)):
        return refresh_token
    username = refresh_token.get("username")
    intra_login = refresh_token.get("intra_login")
    access_token = generate_access_token(username, intra_login)
    response.set_cookie(
        key="access_token",
        value=access_token,
        httponly=True,
        secure=True,
        samesite="Strict",
        max_age=ACCESS_TOKEN_EXPIRY
    )
    return response