#include "../../include/Server.hpp"
#include "../../include/GuessBot.hpp"

void Server::BOT(vector<string>& params, Client& client)
{
	if (client.isRegistered() == false)
	{
		sendMessage(client.getClientFd(), "451 JOIN :You have not registered\r\n");
		return;
	}
	if (params.size() < 2){
		sendMessage(client.getClientFd(), "461 BOT :Not enough parameters\r\n");
		return;
	}

	if (_channelMap.find(params[0]) != _channelMap.end() && params[1] == "GuessBot"){
		GuessBot *newBot = new GuessBot(*this);
		_botMap[newBot->getNickname()] = newBot;
		_channelMap[params[0]]->addClient(newBot);
		newBot->addChannel(_channelMap[params[0]]);
		sendNamesList(params[0], client);

		newBot->sendMessage("Selam, ben bir oyun botuyum " + client.getNickname() + " tarafından başlatıldım.", params[0]);
		newBot->sendMessage("Benim anladığım komutlar şunlardır {p, q, r, h}", params[0]);
		newBot->sendMessage("> p(play: Oyunu başlatır)", params[0]);
		newBot->sendMessage("> q(quit: Oyunu bitirir)", params[0]);
		newBot->sendMessage("> r(restart: Oyunu sıfırlar)", params[0]);
		newBot->sendMessage("> h(help: Yardım menüsünü açar)", params[0]);
	}
}