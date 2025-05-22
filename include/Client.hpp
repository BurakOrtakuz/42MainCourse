#ifndef CLIENT_HPP
# define CLIENT_HPP 202408

# include "Libraries.hpp"
# include "Channel.hpp"

class Channel;
class Client{
public:
	Client();
	virtual ~Client();

	bool					isInChannel(string channel_name);
	bool					isBotClient() const;
	bool					isRegistered() const;

	int						getClientFd() const;
	struct sockaddr_in		getClientAddr() const;
	vector<Channel *>&		getChannels();
	Channel*				getChannel(string channel_name);
	string					getPassword() const;
	string					getNickname() const;
	string					getUsername() const;
	string					getHostname() const;
	string					getServername() const;
	string					getRealname() const;

	void					setClientFd(int client_fd);
	void					setClientAddr(struct sockaddr_in& client_addr);
	void					addChannel(Channel* channel);
	void					quitChannel(string channel_name);
	void					setPassword(string password);
	void					setNickname(string nickname);
	void					setUsername(string username);
	void					setHostname(string hostname);
	void					setServername(string servername);
	void					setRealname(string realname);

	void					displayChannels() const;

	bool operator==(const Client& other) const;
protected:
	bool					isBot;

private:
	int						client_fd;
	struct sockaddr_in		client_addr;

	vector<Channel *>		_channels;

	string					password;
	string					nickname;
	string					username;
	string					hostname;
	string					servername;
	string					realname;
};

#endif /* CLIENT_HPP */