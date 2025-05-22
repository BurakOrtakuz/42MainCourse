#include "../include/Channel.hpp"

Channel::Channel(Client* admin, string channelName, string channelPassword)
{		
		_moderators.push_back(admin);
		_clients.push_back(admin);
		this->userLimit = MAX_USER;
		this->channelName = channelName;
		this->channelPassword = channelPassword;
		this->moderated = false;
}
Channel::~Channel() {};

bool		Channel::isModerator(Client* client) const
{
	for (vector<Client *>::const_iterator it = _moderators.begin(); it != _moderators.end(); it++)
	{
		if (*it == client)
			return true;
	}
	return false;
}
bool		Channel::isClient(Client* client) const
{
	for (vector<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (*it == client)
			return true;
	}
	return false;
}
bool		Channel::isClient(string nickname) const
{
	for (vector<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
			return true;
	}
	return false;
}
bool		Channel::isFull() const { return _clients.size() >= userLimit; }
bool		Channel::isModerated() const { return moderated; }

Client*		Channel::getModerator(size_t fd) const
{
	for (vector<Client *>::const_iterator it = _moderators.begin(); it != _moderators.end(); it++)
	{
		if ((*it)->getClientFd() == fd)
			return *it;
	}
	return NULL;
}
Client*		Channel::getClient(size_t fd) const
{
	for (vector<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->getClientFd() == fd)
			return *it;
	}
	return NULL;
}
Client*		Channel::getClient(string nickname) const
{
	for (vector<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
			return *it;
	}
	return NULL;
}

void		Channel::quitModerator(int fd)
{
	for (vector<Client *>::iterator it = _moderators.begin(); it != _moderators.end(); it++)
	{
		if ((*it)->getClientFd() == fd)
		{
			_moderators.erase(it);
			break;
		}
	}
}
Client*		Channel::quitClient(int fd)
{
	for (vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->getClientFd() == fd)
		{
			if (isModerator(*it))
				quitModerator(fd);
			_clients.erase(it);
			return *it;
		}
	}
	return NULL;
}
Client*		Channel::quitClient(string nickname)
{
	return quitClient(getClient(nickname)->getClientFd());
}

vector<Client *>&	Channel::getModerators() { return _moderators; }
vector<Client *>&	Channel::getClients() { return _clients; }
size_t				Channel::getUserLimit() const { return userLimit; }
string				Channel::getChannelName() const { return channelName; }
string				Channel::getChannelPassword() const { return channelPassword; }

void				Channel::addModerator(Client* moderator)
{
	if (!isModerator(moderator) && isClient(moderator))
		_moderators.push_back(moderator);
}
void				Channel::addClient(Client* client)
{
	if (!isClient(client))
		_clients.push_back(client);
}
void				Channel::setUserLimit(size_t userLimit) { this->userLimit = userLimit; }
void				Channel::setChannelName(string channelName) { this->channelName = channelName; }
void				Channel::setChannelPassword(string channelPassword) { this->channelPassword = channelPassword; }
void				Channel::setModerated(bool target) { this->moderated = target; }

void				Channel::makeOperator(string nickname){
	addModerator(getClient(nickname));
}

void				Channel::displayClients() const{
	cout << endl << "Channel: " << channelName << endl;
	cout << "Moderators: ";
	for (vector<Client *>::const_iterator it = _moderators.begin(); it != _moderators.end(); it++)
		cout << (*it)->getNickname() << " ";
	cout << endl;
	cout << "Clients: ";
	for (vector<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
		cout << (*it)->getNickname() << " ";
	cout << endl << endl;
}