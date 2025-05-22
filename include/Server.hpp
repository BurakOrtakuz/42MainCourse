#ifndef SERVER_HPP
# define SERVER_HPP 202408

# include "Libraries.hpp"
# include "Channel.hpp"
# include "Client.hpp"
# include "Bot.hpp"

class Bot;
class Server;
typedef void (Server::*Commands)(vector<string>&, Client&);

class Server{
private:
//ServerInformation
	string					password;
	uint16_t				portID;
	int						server_fd;
	char					buffer[1024];
	struct sockaddr_in		server_addr;
//
	int						kq;
//Map
	map<string, Channel *>	_channelMap;
	map<int   , Client  *>	_clientMap;
	map<string, Commands>	_commandMap;
	map<string, Bot     *>	_botMap;

public:
	Server(size_t, string);
	~Server();

	void	start();
	void	acceptRequest();
	void	disconnectClient(int client_fd);
	
	vector<pair<string, vector<string> > > getParams(const std::string& str);
	void	handleCommand(int i);
	void	readEvent(int client_fd);

	int		getServerfd() const;
//Server Utils
	void	isValidPort();
	void	setAdd();
	void	createSocket();
	void	initCommands();

	int		errCheck(int errcnd, int res, string message);
	void	sendMessage(int client_fd, const char* message);
	
//Commands
	void	BOT (vector<string>& params, Client& client);
	void	CAP (vector<string>& params, Client& client);
	void	JOIN(vector<string>& params, Client& client);
	void	KICK(vector<string>& params, Client& client);
	void	MODE(vector<string>& params, Client& client);
	void	NICK(vector<string>& params, Client& client);
	void	PART(vector<string>& params, Client& client);
	void	PASS(vector<string>& params, Client& client);
	void	PRIVMSG(vector<string>& params, Client& client);
	void	QUIT(vector<string>& params, Client& client);
	void	USER(vector<string>& params, Client& client);
	void	WHO(vector<string>& params, Client& client);

//Command Utils
	void	casting(int _fd, vector<Client *> _clients, const string &message);
	void	sendNamesList(const string& channelName, Client& client);
	void	newBot(string botname, Client& client);

	
};

#endif  /* SERVER_HPP */