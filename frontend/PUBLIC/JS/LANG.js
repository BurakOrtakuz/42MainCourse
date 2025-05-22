/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LANG.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 ??:??:?? by hdeniz            #+#    #+#             */
/*   Updated: 2024/11/01 ??:??:?? by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

var LANG = "EN"; /* PAGE LANGUAGE - DEFAULT (EN) */


switch ((navigator.language || navigator.userLanguage).substring(0, 2))
{
	case ("tr"):
	{
		LANG = "TR";
	}
	break ;
	case ("fr"):
	{
		LANG = "FR";
	}
	break ;
}

const __LANG__ =
{
	EN:
	{
		ERROR:
		{
			SERVER_500:
			{
				MESSAGE: "Internal server error! (500)",
				TITLE: "Server connection error"
			}
		},
		BUTTON:
		{
			OK: "OK",
			CANCEL: "Cancel"
		},
		START:
		{
			BUTTON_TEXT: "Start",
			MENU:
			{
				LOGOFF: "Log off...",
				SETTINGS: "Settings"
			}
		},
		BSOD:
		{
			MESSAGE: "An error has occurred. To continue:\n\n" +
				"Press Enter to retry connecting to server, or\n\n" +
				"Press CTRL+SHIFT+R to reset the caches and " +
				"re-open the website.\n" +
				"We are really sorry for this error.\n\n" +
				"Error: ",	
			PAUSE_CONTINUE: "Press any key to continue "
		},
		LOGIN:
		{
			TITLE: "Login Screen",
			HEADER: "Please login",
			SPAN_USERNAME: "Username/Email:",
			SPAN_PASSWORD: "Password:",
			PLACEHOLDER_USERNAME: "Your Username or Email",
			PLACEHOLDER_PASSWORD: "Your Password",
			REGISTER_BUTTON: "Register",
			LOGIN_WITH_42_BUTTON: "Login with 42",
			ERROR:
			{
				_1: // USERNAME OR PASSWORD IS INCORRECT
				{
					TITLE: "Login Failed",
					MESSAGE: "Username or Password is Incorrect!"
				},
				_2: // INPUT FORMAT ERROR
				{
					TITLE: "Login Try Error",
					MESSAGE: "The Syntax or Format you're trying on inputs are prohibited!"
				},
				_3: // SOMETHING WENT WRONG
				{
					TITLE: "Error",
					MESSAGE: "Something went wrong. Please try again later:\n"
				},
				_4: // MAX TRY NUMBER REACHED
				{
					TITLE: "Try limit reached!",
					MESSAGE: "You tried too many attempts. Please try again later."
				},
				INPUTS_NULL: // SOMETHING WENT WRONG
				{
					TITLE: "Login Error",
					MESSAGE: "Make sure fill all the areas inside login form!"
				},
				UNDEXPECTED_START: // SOMETHING WENT WRONG
				{
					TITLE: "Website start error",
					MESSAGE: "Undexpected error resulted while trying to connect to server!"
				},
				INTRA:
				{
					TITLE: "42 Intra Login",
					MESSAGE: "Failed to login with Intra"
				},
				FORCE_START_ERROR:
				{
					TITLE: "ERROR",
					MESSAGE: "You're tried to open the desktop by force!\n Your request has been blocked: "
				}
			}
		},
		REGISTER:
		{
			TITLE: "Register Screen",
			HEADER: "Please enter your informations to register",
			SPAN_USERNAME: "Username",
			SPAN_EMAIL: "Email",
			SPAN_PASSWORD: "Password:",
			SPAN_PASSWORD_AGAIN: "Password Again:",
			PLACEHOLDER_USERNAME: "Your Username",
			PLACEHOLDER_EMAIL: "Your Email",
			PLACEHOLDER_PASSWORD: "Your Password",
			PLACEHOLDER_PASSWORD_AGAIN: "Your Password Again",
			REGISTER_BUTTON: "Register",
			ERROR:
			{
				_1: // USERNAME OR PASSWORD IS ALREADY EXIST
				{
					TITLE: "Register Failed",
					MESSAGE: "A User with this Username is already exist!"
				},
				_2: // INPUT FORMAT ERROR
				{
					TITLE: "Register Try Error",
					MESSAGE: "The Syntax or Format you're trying on inputs are prohibited!"
				},
				_3: // SOMETHING WENT WRONG
				{
					TITLE: "Error",
					MESSAGE: "Something went wrong. Please try again later:\n"
				},
				PASSWORD_NOT_SAME: // SOMETHING WENT WRONG
				{
					TITLE: "Register Error",
					MESSAGE: "Passwords are not same!"
				},
				INPUTS_NULL: // SOMETHING WENT WRONG
				{
					TITLE: "Register Error",
					MESSAGE: "Make sure fill all the areas inside this form!"
				}
			},
			SUCCESS:
			{
				TITLE: "Register",
				MESSAGE: "You're successfully registered!!! :-D\n Now please login to continue."
			}
		},
		MSN:
		{
			GLOBAL_CHAT_BUTTON: "Global Chat",
			MESSAGE_PLACEHOLDER: "You're chatting with ",
			MESSAGE_PLACEHOLDER_AT: "You're chatting at ",
			SEND_BUTTON: "Send",
			ERROR:
			{
				WEBSOCKET:
				{
					MESSAGE: "MSN failed to connect server while getting messages.",
					TITLE: "MSN Connection Error"
				}
			}
		},
		PONG:
		{
			TITLE: "The Pong Game",
			WON: " won!",
			MAIN_MENU:
			{
				VS_BOT: "Play with BOT",
				TWO_PLAYERS: "Play with yourself",
				VS_ONLINE: "Play on online",
				VS_TOURNAMENT: "Play in tournament mode",
				EXIT: "Exit",
				NEXT: "Next"
			},
			ERROR:
			{
				ROOM_CREATE:
				{
					TITLE: "Pong Room Error",
					MESSAGE: "Failed to create the room. Please try again. ("
				},
				CONNECTION:
				{
					TITLE: "Pong Error",
					MESSAGE: "Pong failed to connect to server: ("
				},
				ALREADY_IN:
				{
					TITLE: "Pong Tournament Mode",
					MESSAGE: "You're already in a tournament!"
				},
				_5:
				{
					TITLE: "Server Error",
					MESSAGE: "Failed to communicate with server while using access token: ("
				},
				JOIN:
				{
					TITLE: "Tournament Error",
					MESSAGE: "Failed to join tournament! ("
				}
			},
			SOCKET_CLOSED_BY_SERVER: "Socket closed by server",
			PLAYING_WITH: "Playing with ",
			PLAYING_WITH_YOURSELF: "Playing with yourself",
			IN_TOURNAMENT: "You're in a tournament",
			BOT_WON: "You lose to a bot. Loser!",
			YOU_WON: "You won! Lucky!",
			LEFT_PLAYER_WON: "Left player won!",
			RIGHT_PLAYER_WON: "Right player won!",
			MULTIPLAYER_WHO_WON: " is won!",
			PLAYER_EXIT: "Player is exit during the game."
		},
		__2FA__:
		{
			TITLE: "2FA",
			HEADER: "You will gona recieve a code from your email.",
			SPAN: "Please enter your security code",
			PLACEHOLDER_USERNAME: "Security Code",
			ERROR:
			{
				UNKNOWN:
				{
					MESSAGE: "Unknown error. Please try again - (",
					TITLE: "Something went wrong"
				},
				CODE_CREATE_FAIL:
				{
					MESSAGE: "Failed to create your 2FA code.",
					TITLE: "Server Error"
				},
				WRONG_CODE:
				{
					MESSAGE: "You're entered wrong 2FA code. Please try again!",
					TITLE: "Error"
				},
				NOT_ENOUGH_CHARACTER:
				{
					MESSAGE: "You need to give 6 numbers for this from.",
					TITLE: "Error - Not enough characters"
				}
			}
		},
		SETTINGS:
		{
			TITLE: "Settings",
			CHECK__2FA: "Enable 2FA on this profile",
			LEFT_PLAYER_COLOR: "Left Player Color",
			RIGHT_PLAYER_COLOR: "Right Player Color",
			BALL_COLOR: "Ball Color",
			TABLE_COLOR: "Table Color"
		}
	},
	TR:
	{
		ERROR:
		{
			SERVER_500:
			{
				MESSAGE: "Sunucu Hatası! (500)",
				TITLE: "Sunucu bağlantı hatası"
			}
		},
		BUTTON:
		{
			OK: "Tamam",
			CANCEL: "İptal"
		},
		START:
		{
			BUTTON_TEXT: "Başlat",
			MENU:
			{
				LOGOFF: "Çıkış yap...",
				SETTINGS: "Ayarlar"
			}
		},
		BSOD:
		{
			MESSAGE: "Bir hata oluştu. Devam etmek için:\n\n" +
				"Sunucuya bağlanmayı yeniden denemek için Enter tuşuna basın, or\n\n" +
				"Önbellekleri sıfırlamak için CTRL+SHIFT+R tuşlarına basın ve " +
				"web sitesini yeniden açın.\n" +
				"Bu hata için gerçekten üzgünüz.\n\n" +
				"Hata: ",	
			PAUSE_CONTINUE: "Devam etmek için herhangi bir tuşa basın "
		},
		LOGIN:
		{
			TITLE: "Giriş Ekranı",
			HEADER: "Lütfen giriş yapın",
			SPAN_USERNAME: "Kullanıcı Adı/Email:",
			SPAN_PASSWORD: "Şifre:",
			PLACEHOLDER_USERNAME: "Kullanıcı Adınız veya Email",
			PLACEHOLDER_PASSWORD: "Şifreniz",
			REGISTER_BUTTON: "Kayıt ol",
			LOGIN_WITH_42_BUTTON: "42 ile giriş yap",
			ERROR:
			{
				_1: // USERNAME OR PASSWORD IS INCORRECT
				{
					TITLE: "Giriş Başarısız",
					MESSAGE: "Kullanıcı Adı veya Şifre Yanlış!"
				},
				_2: // INPUT FORMAT ERROR
				{
					TITLE: "Giriş Deneme Hatası",
					MESSAGE: "Giriş yapmaya çalıştığınız girişlerin Sözdizimi veya Formatı yasaklanmıştır!"
				},
				_3: // SOMETHING WENT WRONG
				{
					TITLE: "Hata",
					MESSAGE: "Bir şeyler yanlış gitti. Lütfen daha sonra tekrar deneyin:\n"
				},
				_4: // MAX TRY NUMBER REACHED
				{
					TITLE: "Deneme sınırına ulaşıldı!",
					MESSAGE: "Çok fazla deneme yaptınız. Lütfen daha sonra tekrar deneyin."
				},
				INPUTS_NULL: // SOMETHING WENT WRONG
				{
					TITLE: "Giriş Hatası",
					MESSAGE: "Giriş formundaki tüm alanları doldurduğunuzdan emin olun!"
				},
				UNDEXPECTED_START: // SOMETHING WENT WRONG
				{
					TITLE: "Web sitesi başlatma hatası",
					MESSAGE: "Sunucuya bağlanmaya çalışırken beklenmeyen hata oluştu!"
				},
				INTRA:
				{
					TITLE: "42 Intra Giriş",
					MESSAGE: "Intra ile giriş yapma başarısız oldu"
				},
				FORCE_START_ERROR:
				{
					TITLE: "HATA",
					MESSAGE: "Masaüstünü zorla açmaya çalışıyorsunuz!\n İsteğiniz engellendi: "
				}
			}
		},
		REGISTER:
		{
			TITLE: "Kayıt Ekranı",
			HEADER: "Kayıt olmak için bilgilerinizi girin",
			SPAN_USERNAME: "Kullanıcı Adı",
			SPAN_EMAIL: "Email",
			SPAN_PASSWORD: "Şifre:",
			SPAN_PASSWORD_AGAIN: "Şifre Tekrarı:",
			PLACEHOLDER_USERNAME: "Kullanıcı Adınız",
			PLACEHOLDER_EMAIL: "Emailiniz",
			PLACEHOLDER_PASSWORD: "Şifreniz",
			PLACEHOLDER_PASSWORD_AGAIN: "Şifrenizi Tekrar Girin",
			REGISTER_BUTTON: "Kayıt ol",
			ERROR:
			{
				_1: // USERNAME OR PASSWORD IS ALREADY EXIST
				{
					TITLE: "Kayıt Başarısız",
					MESSAGE: "Bu Kullanıcı Adıyla bir Kullanıcı zaten var!"
				},
				_2: // INPUT FORMAT ERROR
				{
					TITLE: "Kayıt Deneme Hatası",
					MESSAGE: "Giriş yapmaya çalıştığınız girişlerin Sözdizimi veya Formatı yasaklanmıştır!"
				},
				_3: // SOMETHING WENT WRONG
				{
					TITLE: "Hata",
					MESSAGE: "Bir şeyler yanlış gitti. Lütfen daha sonra tekrar deneyin:\n"
				},
				PASSWORD_NOT_SAME: // SOMETHING WENT WRONG
				{
					TITLE: "Kayıt Hatası",
					MESSAGE: "Şifreler aynı değil!"
				},
				INPUTS_NULL: // SOMETHING WENT WRONG
				{
					TITLE: "Kayıt Hatası",
					MESSAGE: "Bu formdaki tüm alanları doldurduğunuzdan emin olun!"
				}
			},
			SUCCESS:
			{
				TITLE: "Kayıt",
				MESSAGE: "Başarıyla kayıt oldunuz!!! :-D\n Şimdi devam etmek için lütfen giriş yapın."
			}
		},
		MSN:
		{
			GLOBAL_CHAT_BUTTON: "Global Sohbet",
			MESSAGE_PLACEHOLDER: "Şu kişiyle sohbet ediyorsunuz: ",
			MESSAGE_PLACEHOLDER_AT: "Şu odada sohbet ediyorsunuz: ",
			SEND_BUTTON: "Gönder",
			ERROR:
			{
				WEBSOCKET:
				{
					MESSAGE: "MSN mesajları alırken sunucuya bağlanamadı.",
					TITLE: "MSN Bağlantı Hatası"
				}
			}
		},
		PONG:
		{
			TITLE: "Pong Oyunu",
			WON: " kazandı!",
			MAIN_MENU:
			{
				VS_BOT: "BOT ile oyna",
				TWO_PLAYERS: "Kendinle oyna",
				VS_ONLINE: "Online oyna",
				VS_TOURNAMENT: "Turnuva modunda oyna",
				EXIT: "Çıkış",
				NEXT: "Sonraki Maç"
			},
			ERROR:
			{
				ROOM_CREATE:
				{
					TITLE: "Pong Oda Hatası",
					MESSAGE: "Oda oluşturulamadı. Lütfen tekrar deneyin. ("
				},
				CONNECTION:
				{
					TITLE: "Pong Hatası",
					MESSAGE: "Pong sunucuya bağlanamadı: ("
				},
				ALREADY_IN:
				{
					TITLE: "Pong Turnuva Modu",
					MESSAGE: "Zaten bir turnuvadasınız!"
				},
				_5:
				{
					TITLE: "Sunucu Hatası",
					MESSAGE: "Erişim jetonu kullanırken sunucuyla iletişim kurulamadı: ("
				},
				JOIN:
				{
					TITLE: "Turnuva Hatası",
					MESSAGE: "Turnuvaya katılmak başarısız oldu! ("
				}
			},
			SOCKET_CLOSED_BY_SERVER: "Sunucu tarafından soket kapatıldı",
			PLAYING_WITH: "Şununla oynuyorsunuz: ",
			PLAYING_WITH_YOURSELF: "Kendinizle oynuyorsunuz",
			IN_TOURNAMENT: "Bir turnuvadasınız",
			BOT_WON: "Bir bot'a kaybettiniz. Kaybeden!",
			YOU_WON: "Kazandınız! Şanslı!",
			LEFT_PLAYER_WON: "Sol oyuncu kazandı!",
			RIGHT_PLAYER_WON: "Sağ oyuncu kazandı!",
			MULTIPLAYER_WHO_WON: " kazandı!",
			PLAYER_EXIT: "Oyuncu oyun sırasında çıktı."
		},
		__2FA__:
		{
			TITLE: "2FA",
			HEADER: "E-postanızdan bir kod alacaksınız.",
			SPAN: "Lütfen güvenlik kodunuzu girin",
			PLACEHOLDER_USERNAME: "Güvenlik Kodu",
			ERROR:
			{
				UNKNOWN:
				{
					MESSAGE: "Bilinmeyen hata. Lütfen tekrar deneyin - (",
					TITLE: "Bir şeyler yanlış gitti"
				},
				CODE_CREATE_FAIL:
				{
					MESSAGE: "2FA kodunuzu oluşturmak başarısız oldu.",
					TITLE: "Sunucu Hatası"
				},
				WRONG_CODE:
				{
					MESSAGE: "Yanlış 2FA kodu girdiniz. Lütfen tekrar deneyin!",
					TITLE: "Hata"
				},
				NOT_ENOUGH_CHARACTER:
				{
					MESSAGE: "Bu form için 6 rakam vermeniz gerekiyor.",
					TITLE: "Hata - Yetersiz karakter"
				}
			}
		},
		SETTINGS:
		{
			TITLE: "Ayarlar",
			CHECK__2FA: "Bu profilde 2FA'yı etkinleştir",
			LEFT_PLAYER_COLOR: "Sol Oyuncu Rengi",
			RIGHT_PLAYER_COLOR: "Sağ Oyuncu Reng,",
			BALL_COLOR: "Top Rengi",
			TABLE_COLOR: "Masa Rengi"
		}
	},
	FR:
	{
		ERROR:
		{
			SERVER_500:
			{
				MESSAGE: "Erreur de serveur ! (500)",
				TITLE: "Erreur de connexion au serveur"
			}
		},
		BUTTON:
		{
			OK: "D'accord",
			CANCEL: "Annuler"
		},
		START:
		{
			BUTTON_TEXT: "Démarrer",
			MENU:
			{
				LOGOFF: "Se déconnecter...",
				SETTINGS: "Paramètres"
			}
		},
		BSOD:
		{
			MESSAGE: "Une erreur s'est produite. Pour continuer :\n\n" +
				"Appuyez sur Entrée pour réessayer de vous connecter au serveur, ou\n\n" +
				"Pour réinitialiser les caches, appuyez sur CTRL+SHIFT+R et " +
				"rouvrez le site Web.\n" +
				"Nous sommes vraiment désolés pour cette erreur.\n\n" +
				"Erreur: ",	
			PAUSE_CONTINUE: "Appuyez sur une touche pour continuer "
		},
		LOGIN:
		{
			TITLE: "Écran de connexion",
			HEADER: "Veuillez vous connecter",
			SPAN_USERNAME: "Nom d'utilisateur/Email :",
			SPAN_PASSWORD: "Mot de passe :",
			PLACEHOLDER_USERNAME: "Votre nom d'utilisateur ou email",
			PLACEHOLDER_PASSWORD: "Votre mot de passe",
			REGISTER_BUTTON: "S'inscrire",
			LOGIN_WITH_42_BUTTON: "Se connecter avec 42",
			ERROR:
			{
				_1: // USERNAME OR PASSWORD IS INCORRECT
				{
					TITLE: "Échec de la connexion",
					MESSAGE: "Nom d'utilisateur ou mot de passe incorrect !"
				},
				_2: // INPUT FORMAT ERROR
				{
					TITLE: "Erreur de tentative de connexion",
					MESSAGE: "La syntaxe ou le format que vous essayez sur les entrées sont"
				},
				_3: // SOMETHING WENT WRONG
				{
					TITLE: "Erreur",
					MESSAGE: "Quelque chose s'est mal passé. Veuillez réessayer plus tard :\n"
				},
				_4: // MAX TRY NUMBER REACHED
				{
					TITLE: "Limite d'essai atteinte !",
					MESSAGE: "Vous avez essayé trop de tentatives. Veuillez réessayer plus tard."
				},
				INPUTS_NULL: // SOMETHING WENT WRONG
				{
					TITLE: "Erreur de connexion",
					MESSAGE: "Assurez-vous de remplir toutes les zones à l'intérieur du formulaire de connexion !"
				},
				UNDEXPECTED_START: // SOMETHING WENT WRONG
				{
					TITLE: "Erreur de démarrage du site Web",
					MESSAGE: "Erreur inattendue résultant de la tentative de connexion au serveur !"
				},
				INTRA:
				{
					TITLE: "42 Intra Login",
					MESSAGE: "Échec de la connexion avec Intra"
				},
				FORCE_START_ERROR:
				{
					TITLE: "ERREUR",
					MESSAGE: "Vous avez essayé d'ouvrir le bureau de force !\n Votre demande a été bloquée : "
				}
			}
		},
		REGISTER:
		{
			TITLE: "Écran d'inscription",
			HEADER: "Veuillez entrer vos informations pour vous inscrire",
			SPAN_USERNAME: "Nom d'utilisateur",
			SPAN_EMAIL: "Email",
			SPAN_PASSWORD: "Mot de passe :",
			SPAN_PASSWORD_AGAIN: "Mot de passe à nouveau :",
			PLACEHOLDER_USERNAME: "Votre nom d'utilisateur",
			PLACEHOLDER_EMAIL: "Votre email",
			PLACEHOLDER_PASSWORD: "Votre mot de passe",
			PLACEHOLDER_PASSWORD_AGAIN: "Votre mot de passe à nouveau",
			REGISTER_BUTTON: "S'inscrire",
			ERROR:
			{
				_1: // USERNAME OR PASSWORD IS ALREADY EXIST
				{
					TITLE: "Inscription échouée",
					MESSAGE: "Un utilisateur avec ce nom d'utilisateur existe déjà !"
				},
				_2: // INPUT FORMAT ERROR
				{
					TITLE: "Erreur de tentative d'inscription",
					MESSAGE: "La syntaxe ou le format que vous essayez sur les entrées sont"
				},
				_3: // SOMETHING WENT WRONG
				{
					TITLE: "Erreur",
					MESSAGE: "Quelque chose s'est mal passé. Veuillez réessayer plus tard :\n"
				},
				PASSWORD_NOT_SAME: // SOMETHING WENT WRONG
				{
					TITLE: "Erreur d'inscription",
					MESSAGE: "Les mots de passe ne sont pas les mêmes !"
				},
				INPUTS_NULL: // SOMETHING WENT WRONG
				{
					TITLE: "Erreur d'inscription",
					MESSAGE: "Assurez-vous de remplir toutes les zones à l'intérieur de ce formulaire !"
				}
			},
			SUCCESS:
			{
				TITLE: "Inscription",
				MESSAGE: "Vous êtes inscrit avec succès !!! :-D\n Maintenant, veuillez vous connecter pour continuer."
			}
		},
		MSN:
		{
			GLOBAL_CHAT_BUTTON: "Chat global",
			MESSAGE_PLACEHOLDER: "Vous discutez avec ",
			MESSAGE_PLACEHOLDER_AT: "Vous discutez à ",
			SEND_BUTTON: "Envoyer",
			ERROR:
			{
				WEBSOCKET:
				{
					MESSAGE: "MSN n'a pas réussi à se connecter au serveur pour obtenir des messages.",
					TITLE: "Erreur de connexion MSN"
				}
			}
		},
		PONG:
		{
			TITLE: "Le jeu Pong",
			WON: " a gagné !",
			MAIN_MENU:
			{
				VS_BOT: "Jouer avec BOT",
				TWO_PLAYERS: "Jouer avec vous-même",
				VS_ONLINE: "Jouer en ligne",
				VS_TOURNAMENT: "Jouer en mode tournoi",
				EXIT: "Sortie",
				NEXT: "Suivant"
			},
			ERROR:
			{
				ROOM_CREATE:
				{
					TITLE: "Erreur de salle Pong",
					MESSAGE: "Impossible de créer la salle. Veuillez réessayer. ("
				},
				CONNECTION:
				{
					TITLE: "Erreur Pong",
					MESSAGE: "Pong n'a pas réussi à se connecter au serveur : ("
				},
				ALREADY_IN:
				{
					TITLE: "Mode tournoi Pong",
					MESSAGE: "Vous êtes déjà dans un tournoi !"
				},
				_5:
				{
					TITLE: "Erreur de serveur",
					MESSAGE: "Échec de la communication avec le serveur lors de l'utilisation du jeton d'accès : ("
				},
				JOIN:
				{
					TITLE: "Erreur de tournoi",
					MESSAGE: "Impossible de rejoindre le tournoi ! ("
				}
			},
			SOCKET_CLOSED_BY_SERVER: "Socket fermé par le serveur",
			PLAYING_WITH: "Jouer avec ",
			PLAYING_WITH_YOURSELF: "Jouer avec vous-même",
			IN_TOURNAMENT: "Vous êtes dans un tournoi",
			BOT_WON: "Vous avez perdu contre un bot. Perdant!",
			YOU_WON: "Vous avez gagné! Chanceux!",
			LEFT_PLAYER_WON: "Le joueur de gauche a gagné!",
			RIGHT_PLAYER_WON: "Le joueur de droite a gagné!",
			MULTIPLAYER_WHO_WON: " a gagné!",
			PLAYER_EXIT: "Le joueur est sorti pendant le jeu."
		},
		__2FA__:
		{
			TITLE: "2FA",
			HEADER: "Vous allez recevoir un code de votre e-mail.",
			SPAN: "Veuillez entrer votre code de sécurité",
			PLACEHOLDER_USERNAME: "Code de sécurité",
			ERROR:
			{
				UNKNOWN:
				{
					MESSAGE: "Erreur inconnue. Veuillez réessayer - (",
					TITLE: "Quelque chose s'est mal passé"
				},
				CODE_CREATE_FAIL:
				{
					MESSAGE: "Impossible de créer votre code 2FA.",
					TITLE: "Erreur de serveur"
				},
				WRONG_CODE:
				{
					MESSAGE: "Vous avez entré un mauvais code 2FA. Veuillez réessayer !",
					TITLE: "Erreur"
				},
				NOT_ENOUGH_CHARACTER:
				{
					MESSAGE: "Vous devez donner 6 chiffres pour ce formulaire.",
					TITLE: "Erreur - Pas assez de caractères"
				}
			}
		},
		SETTINGS:
		{
			TITLE: "Paramètres",
			CHECK__2FA: "Activer 2FA sur ce profil",
			LEFT_PLAYER_COLOR: "Couleur du joueur de gauche",
			RIGHT_PLAYER_COLOR: "Couleur du joueur de droite",
			BALL_COLOR: "Couleur de la balle",
			TABLE_COLOR: "Couleur de la table"
		}
	}
};
