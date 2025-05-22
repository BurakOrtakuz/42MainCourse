from django.urls import path
from . import views

urlpatterns = [
    path('server_health/', views.server_health,name="server_health"),
	path('accessWithToken/',views.access_token_login,name='access_token'),
	path('login/', views.login, name='login'),
	path('register/', views.register, name='register'),
	path('logout/', views.logout, name='logout'),
 	path('intra_url', views.intra_url,name="intra_url"),
    path('intra_login/', views.intra_login,name="intra_login"),
 	path('create_2fa_code/', views.create_2fa_code,name="set_2fa"),
    path('verify_2fa_code/', views.verify_2fa_code,name="verify_2fa"),
    path('two_factor_permit/', views.two_factor_permit,name="two_factor_permit"),
    path('get_2fa/', views.get_2fa_state,name="get_2fa"),
]
