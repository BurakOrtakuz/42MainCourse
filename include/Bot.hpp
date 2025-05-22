#ifndef BOT_HPP
# define BOT_HPP 202408

# include "Client.hpp"
# include "Server.hpp"

class Server;
class Bot : public Client{
public:
	Bot(string botname, Server& server);
	virtual ~Bot();

	virtual void 	sendMessage(const string &message, const string &target);
	virtual void	takeMessage(const string &message, const string &target);

	int				getServerfd() const;

	static short	bot_count;

protected:
	Server&			server;
};



#endif /* BOT_HPP */