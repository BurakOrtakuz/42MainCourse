import pyotp
from apiTest.settings import MAIL_SERVICE_HOST, MAIL_SERVICE_PORT, MAIL_SERVICE_HOST_USER, MAIL_SERVICE_HOST_PASSWORD
import smtplib
from email.mime.text import MIMEText
from django.http import JsonResponse
from django.db import connection

user_two_factor_code = {}

def create_two_factor_code(username):
	secret = pyotp.random_base32()
	totp = pyotp.TOTP(secret)
	code = totp.now()
	user_two_factor_code[username] =code
	return user_two_factor_code[username]

def send_mail(username, email):
	code = create_two_factor_code(username)
	if not code:
		return JsonResponse({"error_level": 1})
	subject = "Your Two-Factor Authentication Code"
	body = f"Hello {username},\n\nYour two-factor authentication code is: {code}\n\nThank you."
	msg = MIMEText(body)
	msg['Subject'] = subject
	msg['From'] = MAIL_SERVICE_HOST_USER
	msg['To'] = email
	try:
		with smtplib.SMTP(MAIL_SERVICE_HOST, MAIL_SERVICE_PORT) as server:
			server.starttls()
			server.login(MAIL_SERVICE_HOST_USER, MAIL_SERVICE_HOST_PASSWORD)
			server.sendmail(MAIL_SERVICE_HOST_USER, email, msg.as_string())
		return JsonResponse({"error_level":0})
	except Exception as e:
		try:
			with connection.cursor() as cursor:
				cursor.execute("UPDATE \"User\" SET \"TwoFactorAuth\" = false WHERE \"Username\" = %s", [username])
				return JsonResponse({"error_level":1,"error_message": str(e)})
		except Exception as e:
			return JsonResponse({"error_level":0,"error_message": str(e)})
def test_send_mail():
    return JsonResponse({"error_level":0,"data":MAIL_SERVICE_HOST_USER,"data2":MAIL_SERVICE_HOST_PASSWORD
                         ,"data3":MAIL_SERVICE_HOST,"data4":MAIL_SERVICE_PORT})
def get_two_factor_code(username):
	return user_two_factor_code.get(username)