#include "../../include/Server.hpp"


void Server::MODE(vector<string>& params, Client& client)
{
	if (params.size() != 3 && params.size() != 2)
		{sendMessage(client.getClientFd(), "461 MODE :Not enough parameters\r\n"); return; }
	if (params[0][0] != '#' || (!(params[1][0] == '+' || params[1][0] == '-')) || (!(params[1][1] == 'o' || params[1][1] == 'k' || params[1][1] == 'l' || params[1][1] == 'm')))
	{
		sendMessage(client.getClientFd(), "ERR_UNKNOWNMODE (472)\r\n");
		cout << "params[0][0] [" << params[0][0] << "]" << endl;
		cout << "params[1][0] [" << params[1][0] << "]" << endl;
		cout << "params[1][1] [" << params[1][1] << "]" << endl;
		return;
	}
	if (_channelMap.find(params[0]) == _channelMap.end())
		{sendMessage(client.getClientFd(), "ERR_NOSUCHCHANNEL (403)\r\n"); return;}

	string channelName = params[0];
	bool token = params[1][0] == '+';
	char mode = params[1][1] = params[1][1];
	string arg = "";
	if (params.size() == 3)
		arg = params[2];
	
	if (mode == 'o') //MODE #mychannel +o alice
	{
		if (_channelMap[channelName] == nullptr)
			{sendMessage(client.getClientFd(), "ERR_NOSUCHCHANNEL (403)\r\n"); return;}
		if (_channelMap[channelName]->isModerator(&client) == false)
			{sendMessage(client.getClientFd(), "You are not allowed to use +o\r\n"); return;}
		_channelMap[channelName]->makeOperator(arg);
	}
	else if (mode == 'k') //MODE #mychannel +k secretpass
	{
		if (_channelMap[channelName] == nullptr)
			{sendMessage(client.getClientFd(), "ERR_NOSUCHCHANNEL (403)\r\n"); return;}
		if (_channelMap[channelName]->isModerator(&client) == false)
			{sendMessage(client.getClientFd(), "You are not allowed to use +k\r\n"); return;}
		_channelMap[channelName]->setChannelPassword(arg);
	}
	else if (mode == 'l') //MODE #mychannel +l 50
	{
		if (_channelMap[channelName] == nullptr)
			{sendMessage(client.getClientFd(), "ERR_NOSUCHCHANNEL (403)\r\n"); return;}
		if (_channelMap[channelName]->isModerator(&client) == false)
			{sendMessage(client.getClientFd(), "You are not allowed to use +l\r\n"); return;}
		_channelMap[channelName]->setUserLimit(stoi(arg));
	}
	else if (mode == 'm') //MODE #mychannel +m
	{
		if (_channelMap[channelName] == nullptr)
			{sendMessage(client.getClientFd(), "ERR_NOSUCHCHANNEL (403)\r\n"); return;}
		if (_channelMap[channelName]->isModerator(&client) == false)
			{sendMessage(client.getClientFd(), "You are not allowed to use +m\r\n"); return;}
		_channelMap[channelName]->setModerated(true);
	}
	else
		{sendMessage(client.getClientFd(), "ERR_UNKNOWNMODE (472)\r\n"); return;}
	
}