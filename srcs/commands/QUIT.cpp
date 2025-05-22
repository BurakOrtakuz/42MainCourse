#include "../../include/Server.hpp"

void Server::QUIT(vector<string>& params, Client& client)
{
    string message = "";
    for(int i = 0; i < client.getChannels().size(); i++)
    {
        vector<string> params;
        params.push_back(client.getChannels()[i]->getChannelName());
        params.push_back(message);
        PRIVMSG(params, client);
    }
    message = "Goodbye " + client.getNickname() + "\r\n";
    sendMessage(client.getClientFd(), message.c_str());
    disconnectClient(client.getClientFd());
}