#include "../../include/Server.hpp"

void Server::casting(int _fd, vector<Client *> _clients, const string &message) {
	for (vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->isBotClient())
			continue;
		sendMessage((*it)->getClientFd(), message.c_str());
	}
}
void Server::sendNamesList(const string& channelName, Client& client) {
	
	string namesList = channelName + " :";
	
	for (vector<Client *>::iterator it = _channelMap[channelName]->getClients().begin(); it != _channelMap[channelName]->getClients().end(); it++)
	{
		namesList += (*it)->getNickname() + " ";
	}

	vector<Client *> clients = client.getChannel(channelName)->getClients();
	for (size_t i=0; i<clients.size(); i++) {
		if (clients.at(i)->isBotClient())
			continue;
		// 353 response format: ":server_name 353 nickname = channel :nickname_list"
		sendMessage(clients.at(i)->getClientFd(), (":serverName 353 " + (clients.at(i))->getNickname() + " = " + namesList + "\r\n").c_str());
		// 366 response format: ":server_name 366 nickname channel :End of /NAMES list."
		sendMessage(clients.at(i)->getClientFd(), (":serverName 366 " + (clients.at(i))->getNickname() + " " + channelName + " :End of /NAMES list.\r\n").c_str());
	}
}