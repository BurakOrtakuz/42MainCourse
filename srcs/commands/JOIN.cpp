#include "../../include/Server.hpp"

void Server::JOIN(vector<string>& params, Client& client)
{
	if (client.isRegistered() == false)
	{
		sendMessage(client.getClientFd(), "451 JOIN :You have not registered\r\n");
		return;
	}
	string msg;
	if (params.size() < 1)
	{
		sendMessage(client.getClientFd(), "461 JOIN :Not enough parameters\r\n");
		return;
	}
	if (params[0][0] != '#') {
		params[0] = "#" + params[0];
	}
	for (size_t i = 0; i < client.getChannels().size(); i++){
		if (client.getChannels()[i]->getChannelName() == params[0])
		{
			sendMessage(client.getClientFd(), "You're already on this channel!\r\n");
			return;
		}
	}
	if (_channelMap.find(params[0]) == _channelMap.end())
	{
		string msg;
		msg = params[0] + " creating channel...\r\n";
		sendMessage(client.getClientFd(), msg.c_str());
		msg = "Admin login\r\n";
		sendMessage(client.getClientFd(), msg.c_str());
		string channelPassword = "";
		if (params.size() > 2) {
			channelPassword = params[2];
		}
		_channelMap[params[0]] = new Channel(&client, params[0], channelPassword);
		client.getChannels().push_back(_channelMap[params[0]]);
		msg = ":" + client.getNickname() + " JOIN " + params[0] + "\r\n";
		casting(client.getClientFd(), _channelMap[params[0]]->getClients(), msg);
		sendNamesList(params[0], client); // Send the list of users in the channel
		return ;
	}
	if (_channelMap[params[0]]->getClients().size() >= _channelMap[params[0]]->getUserLimit())
	{
		sendMessage(client.getClientFd(), "Channel is full!\r\n");
		return;
	}
	else if (!(_channelMap[params[0]]->getChannelPassword().empty()) && _channelMap[params[0]]->getChannelPassword() != params[1]) {
		sendMessage(client.getClientFd(), "Wrong password!\r\n");
		return;
	}
	else {
		_channelMap[params[0]]->getClients().push_back(&client);
		client.getChannels().push_back(_channelMap[params[0]]);
		msg = ":" + client.getNickname() + " JOIN " + params[0] + "\r\n";
		casting(client.getClientFd(), _channelMap[params[0]]->getClients(), msg);
		sendNamesList(params[0], client); // Send the list of users in the channel
	}
}