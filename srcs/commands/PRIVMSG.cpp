#include "../../include/Server.hpp"
std::string getMessages(vector<string>& params, int start)
{
    std::string message = "";
    for(int i = start; i<params.size(); i++)
    {
        message += params[i];
        if(i != params.size() - 1)
            message += " ";
    }
    return message;
}
void Server::PRIVMSG(vector<string>& params, Client& client)
{
    if(params[0].front() == '#') // If mask is about channel
    {
        for(int i = 0; i < client.getChannels().size(); i++) // Search whole channels
        {
            if(client.getChannels()[i]->getChannelName() == params[0]) // If channel is matched
            {
                if(client.getChannels()[i]->isModerated() && !client.getChannels()[i]->isModerator(&client)) // If channel is moderated and client is not operator
                {
                    sendMessage(client.getClientFd(), "482 PRIVMSG :You're not channel operator\r\n");
                    return;
                }
                for(int j = 0; j < client.getChannels()[i]->getClients().size(); j++) // Get all clients in the channel
                {
                    if(client.getChannels()[i]->getClients()[j]->getNickname() == client.getNickname()) // If client is sender
                        continue;
                    if (client.getChannels()[i]->getClients()[j]->isBotClient())
                        continue;
                    string message = ":" + client.getNickname() + " PRIVMSG " + params[0] + " :" + getMessages(params,1) + "\r\n";
                    sendMessage(client.getChannels()[i]->getClients()[j]->getClientFd(), message.c_str());
                }
                return;
            }
        }
        sendMessage(client.getClientFd(), "403 PRIVMSG :No such channel\r\n");
    }
    else // If mask is about user
    {
        std::string nickname = params[0];
        std::map<int, Client*>::iterator it;
        if (_botMap[nickname])
        {
            string msg = getMessages(params,1);
            string msg2 = msg.substr(msg.find_first_not_of(" :"), msg.find_last_not_of(" :"));
            _botMap[nickname]->takeMessage(msg2, client.getNickname());
            return;
        }
        for (it = _clientMap.begin(); it != _clientMap.end(); ++it)
        {
            if (it->second->getNickname() == nickname)
            {
                int client_fd = it->second->getClientFd();
                std::string message = ":" + client.getNickname() + " PRIVMSG " + params[0] + " :" + getMessages(params,1) + "\r\n";
                sendMessage(client_fd, message.c_str());
                return;
            }
        }
        sendMessage(client.getClientFd(), "401 PRIVMSG :No such nick\r\n");
    }
}