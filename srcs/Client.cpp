#include "../include/Client.hpp"

Client::Client()
{
	this->isBot = false;
	this->client_fd = -1;
	memset(&this->client_addr, 0, sizeof(this->client_addr));
	this->password = "";
	this->nickname = "";
	this->username = "";
	this->hostname = "";
	this->servername = "";
	this->realname = "";
}
Client::~Client(){}

bool Client::isInChannel(string channel_name){
	for (vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if ((*it)->getChannelName() == channel_name) {
			return true;
		}
	}
	return false;
}
bool Client::isBotClient() const{return isBot;}
bool Client::isRegistered() const{return nickname.size() && username.size();}
int Client::getClientFd() const {
	return this->client_fd;
}
struct sockaddr_in Client::getClientAddr() const {
	return this->client_addr;
}
vector<Channel *>& Client::getChannels() {
	return this->_channels;
}
Channel* Client::getChannel(string channel_name) {
	for (vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if ((*it)->getChannelName() == channel_name) {
			return *it;
		}
	}
	return NULL;
}
string Client::getPassword() const {
	return this->password;
}
string Client::getNickname() const {
	return this->nickname;
}
string Client::getUsername() const {
	return this->username;
}
string Client::getHostname() const {
	return this->hostname;
}
string Client::getServername() const {
	return this->servername;
}
string Client::getRealname() const {
	return this->realname;
}

void Client::setClientFd(int client_fd) {
	this->client_fd = client_fd;
}
void Client::setClientAddr(struct sockaddr_in& client_addr) {
	this->client_addr = client_addr;
}
void Client::addChannel(Channel* channel) {
	if (!isInChannel(channel->getChannelName()))
		_channels.push_back(channel);
}
void Client::quitChannel(string channel_name) {
	for (vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if ((*it)->getChannelName() == channel_name) {
			this->_channels.erase(it);
			break;
		}
	}	
}
void Client::setPassword(string password) {
	this->password = password;
}
void Client::setNickname(string nickname) {
	this->nickname = nickname;
}
void Client::setUsername(string username) {
	this->username = username;
}
void Client::setHostname(string hostname) {
	this->hostname = hostname;
}
void Client::setServername(string servername) {
	this->servername = servername;
}
void Client::setRealname(string realname) {
	this->realname = realname;
}

void Client::displayChannels() const{
	cout <<endl << "Client " << this->getNickname() << " is in the following channels:" << endl;
	cout << "Channels: " << endl;
	for (vector<Channel *>::const_iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		cout << (*it)->getChannelName() << endl;
	}
	cout << endl << endl;
}

bool Client::operator==(const Client& other) const {
	// Compare the relevant members of the Client class.
	// Replace the following line with the actual members you need to compare.
	return this->client_fd == other.client_fd;
}