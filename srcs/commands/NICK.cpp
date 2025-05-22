#include "../../include/Server.hpp"

static bool isValidNick(string& nick){
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}_|";

	if (nick.empty() || nick.length() > 9)
        return false;
	if (!isalpha(nick[0]))
        return false;
	if (nick.find_first_not_of(allowedChars) != std::string::npos)
		return false;
	if ((nick[0] == 'B' || nick[0] == 'b') && (nick[0] == 'O' || nick[1] == 'o') && (nick[2] == 'T' || nick[2] == 't'))
		return false;
	return true;
}

static bool isUniqueNick(string& nick, map<int, Client*>& _clientMap){
	for (map<int, Client*>::iterator it = _clientMap.begin(); it != _clientMap.end(); ++it)
		if (it->second->getNickname() == nick)
			return false;
	return true;
}
/*
NICK <nickname>
	- Allowed characters: a-z, A-Z, 0-9, []{}_|
	- Must start with a letter(a-z, A-Z)
	- Must not exceed 9 characters
ERRORS:
	- ERR_NONICKNAMEGIVEN (431)
	- ERR_NICKNAMEINUSE (433)
	- ERR_ERRONEUSNICKNAME (432)
*/
void Server::NICK(vector<string>& params, Client& client)
{
	if (client.getPassword().empty()) //PASS henüz girilmemiş ise, yani client.reg[0] false ise
		sendMessage(client.getClientFd(), "MY_UNKOWN_COMMAND[NICK]\r\n");
	else if (params.size() != 1) //eğer parametre verilmemiş ise
		sendMessage(client.getClientFd(), "ERR_NONICKNAMEGIVEN 431\r\n");
	else if (!isValidNick(params[0]))
		sendMessage(client.getClientFd(), "ERR_ERRONEUSNICKNAME 432\r\n");
	else if (!isUniqueNick(params[0], _clientMap)) //eğer bu nick, kullanımda ise > mevcut clienların nicklerine bakan bir fonksiyon yazılacak
		sendMessage(client.getClientFd(), "ERR_NICKNAMEINUSE 433\r\n");
	else if (client.isRegistered())
	{
		client.setNickname(params[0]);
		cout << "NickName is set! [" << client.getNickname() << "]" << endl;//YORUM
		for (vector<Channel *>::iterator it = client.getChannels().begin(); it != client.getChannels().end(); it++)
		{
			sendNamesList((*it)->getChannelName(), client);
		}
	}
	else
	{
		client.setNickname(params[0]);
		cout << "NickName is set! [" << client.getNickname() << "]" << endl;//YORUM
		if (client.getUsername().size())
		{
			if (client.getPassword() != this->password){
				sendMessage(client.getClientFd(), "WRONG_PASSWORD\r\n");
				disconnectClient(client.getClientFd());
			}
			else
				sendMessage(client.getClientFd(), "WELCOME TO OUR[ENVER&BURAK] THE IRC SERVER\r\n");
		}
	}
}