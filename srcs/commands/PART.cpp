#include "../../include/Server.hpp"

void Server::PART(vector<string>& params, Client& client)
{
    if(params.size() < 1)
    {
        sendMessage(client.getClientFd(), "461 PART :Not enough parameters\r\n");
        return;
    }
    if(params[0].front() != '#')
    {
        sendMessage(client.getClientFd(), "403 PART :No such channel\r\n");
        return;
    }
    for(int i = 0; i < client.getChannels().size(); i++)
    {
        std::__1::vector<Channel *> channels = client.getChannels();
        if(channels[i]->getChannelName() == params[0])
        {
            channels[i]->quitClient(client.getClientFd());
            client.quitChannel(params[0]);
            sendMessage(client.getClientFd(), ("PART Leaved Channel " + params[0] + "\r\n").c_str());
            return;
        }
    }
    sendMessage(client.getClientFd(), "403 PART :No such channel\r\n");
}