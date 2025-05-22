#ifndef CHANNEL_HPP
# define CHANNEL_HPP 202408

# include "Libraries.hpp"
# include "Client.hpp"

class Client;
class Channel{
public:
	Channel(Client* admin, string channelName, string channelPassword);
	~Channel();

	bool				isModerator(Client* client) const;
	bool				isClient(Client* client) const;
	bool				isClient(string nickname) const;
	bool				isFull() const;
	bool				isModerated() const;

	Client*				getModerator(size_t fd) const;
	Client*				getClient(size_t fd) const;
	Client*				getClient(string nickname) const;

	vector<Client *>&	getModerators();
	vector<Client *>&	getClients();
	size_t				getUserLimit() const;
	string				getChannelName() const;
	string				getChannelPassword() const;

	void				quitModerator(int fd);
	Client*				quitClient(int fd);
	Client*				quitClient(string nickname);

	void				addModerator(Client* moderator);
	void				addClient(Client* client);
	void				setUserLimit(size_t userLimit);
	void				setChannelName(string channelName);
	void				setChannelPassword(string channelPassword);
	void				setModerated(bool target);

	void				makeOperator(string nickname);
	void				displayClients() const;
	
	
private:
	vector<Client *>	_moderators;
	vector<Client *>	_clients;
	size_t				userLimit;
	string				channelName;
	string				channelPassword;
	bool				moderated;
};

#endif /* CHANNEL_HPP */