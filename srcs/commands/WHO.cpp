#include "../../include/Server.hpp"

std::string getInfo(Client& client)
{
    std::string message = "";
    message += client.getUsername();
    message += " ";
    message += client.getNickname();
    return message;
}
void Server::WHO(vector<string>& params, Client& client)
{
    if(params.size() == 1)
    {
        if(params[0].front() == '#') // If mask is about channel
        {
            for(int i = 0; i < client.getChannels().size(); i++) // Search whole channels
            {
                if(client.getChannels()[i]->getChannelName() == params.at(0)) // If channel is matched 
                {
                    std::string message = "";
                    for(int j = 0; j < client.getChannels()[i]->getClients().size(); j++) // Get all clients in the channel
                    {
                        message += getInfo(*client.getChannels()[i]->getClients()[j]);
                        if(j == client.getChannels()[i]->getClients().size() - 1)
                            break;
                        message += "\n";
                    }
                    message += "\r\n";
                    sendMessage(client.getClientFd(), message.c_str());
					return;
				}
            }
            sendMessage(client.getClientFd(), "403 WHO :No such channel\r\n");
        }
        else // If mask is about user
        {
            for(int i = 0; i < client.getChannels().size(); i++) // Search whole channels
			{
				for(int j = 0; j < client.getChannels()[i]->getClients().size(); j++) // Search whole clients in the channel
                {
                    if(client.getChannels()[i]->getClients()[j]->getNickname() == params.at(0)) // If client is matched
                    {
                        std::string message = getInfo(*client.getChannels()[i]->getClients()[j]);
                        message += "\r\n";
                        sendMessage(client.getClientFd(), message.c_str());
                        return;
                    }
                }
            }
			sendMessage(client.getClientFd(), "403 WHO :No such user\r\n");
        }
    }
    else
    {
        sendMessage(client.getClientFd(), "461 WHO :Not enough parameters\r\n");
    }
}