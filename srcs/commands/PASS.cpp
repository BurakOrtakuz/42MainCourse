#include "../../include/Server.hpp"
/*
Burada şifrenin doğruluğunu kontrol etmiyorum
çünkü standart gereği kullanıcı NICK ve USER komutlarını göndermeden önce
birden fazla PASS komutu gönderebilir, ve bu iki komutu aldıktan sonra
şifrenin doğruluğunu kontrol edebilirim. 
Elbette bir satırda birden fazla PASS komutu yazmak doğru değil !!
[Writer: Enver Yılmaz][Date: 04.08.2024] */

/*
PASS <password>

ERRORS:
	ERR_NEEDMOREPARAMS (461)
	ERR_ALREADYREGISTERED (462)
	ERR_PASSWDMISMATCH (464)
*/
void Server::PASS(vector<string>& params, Client& client)
{
	if (params.size() != 1)
		sendMessage(client.getClientFd(), "ERR_NEEDMOREPARAMS 461\r\n");
	else if (client.getNickname().size() || client.getUsername().size())
		sendMessage(client.getClientFd(), "ERR_ALREADYREGISTERED 462\r\n");
	else
	{
		client.setPassword(params[0]);
		cout << "Pasword is set! [" << client.getPassword() << "]" << endl;//YORUM
	}
}