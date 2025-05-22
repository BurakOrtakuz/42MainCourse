#include "../../include/Server.hpp"

void Server::KICK(vector<string>& params, Client& client)
{
	if (client.isRegistered() == false)
	{
		sendMessage(client.getClientFd(), "451 JOIN :You have not registered\r\n");
		return;
	}
	if (params.size() != 2)
	{sendMessage(client.getClientFd(), "461 KICK :Not enough parameters"); return;}

	if (_channelMap.find(params[0]) == _channelMap.end())
	{sendMessage(client.getClientFd(), "403 KICK :No such channel"); return;}

	if (_channelMap[params[0]]->isClient(&client) == false)
	{sendMessage(client.getClientFd(), "441 KICK :User not in channel"); return;}

	if (_channelMap[params[0]]->isClient(params[1]) == false)
	{sendMessage(client.getClientFd(), "441 KICK :User not in channel"); return;}

	if (_channelMap[params[0]]->isModerator(&client) == false)
	{sendMessage(client.getClientFd(), "482 KICK :You're not a channel operator"); return;}
	if (params[1] == client.getNickname())
    {sendMessage(client.getClientFd(), "482 KICK :You can't kick yourself");return;}
	string msg = ":" + client.getNickname() + " KICK " + params[0] + " " + params[1] + "\r\n";
	casting(client.getClientFd(), _channelMap[params[0]]->getClients(), msg);

	Client *target = (_channelMap[params[0]]->quitClient(params[1]));
	if (target == nullptr)
	{
		cout << "target is nullptr" << endl;
		return;
	}
	target->quitChannel(params[0]);
	sendNamesList(params[0], client);
}