#include "../../include/Server.hpp"

/*
USER <username>
USER <username> 0 * <realname>
USER <username> <hostname> <servername> <realname>
ERRORS:
	ERR_NEEDMOREPARAMS (461)
	ERR_ALREADYREGISTERED (462)

*/
void Server::USER(vector<string>& params, Client& client)
{
	if (client.getPassword().empty()) //PASS henüz girilmemiş ise, yani client.reg[0] false ise
		sendMessage(client.getClientFd(), "MY_UNKOWN_COMMAN[USER]\r\n");
	if (params.size() != 4)
		{sendMessage(client.getClientFd(), "ERR_NEEDMOREPARAMS 461[USER]\r\n"); cout << "User Params size:"<<params.size()<<endl;}
	else if (client.getUsername().size())
		sendMessage(client.getClientFd(), "ERR_ALREADYREGISTERED 462\r\n");
	else
	{
		client.setUsername(params[0]);
		client.setHostname(params[1]);
		client.setServername(params[2]);
		client.setRealname(params[3].substr(1));
		
		cout << "UserName is set! [" << client.getUsername() << "]" << endl;//YORUM
		if (client.getNickname().size())
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