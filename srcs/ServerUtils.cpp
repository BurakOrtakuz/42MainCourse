#include "../include/Server.hpp"

void Server::isValidPort(){
	if (portID <= 0 || portID >= 65535)
		throw runtime_error("Invalid Port!!");
}
void Server::setAdd(){
	memset((char *)&server_addr, 0, sizeof(server_addr));// Clear the structure
	this->server_addr.sin_addr.s_addr = INADDR_ANY; // Set the IP address to listen to any address
	this->server_addr.sin_family = AF_INET; // Set the address family
	this->server_addr.sin_port = htons(portID); // Set the port in such a way that it can be used by server
}
void Server::createSocket(){
	int optval = 1;	// Set socket option

	server_fd = errCheck(-1, socket(AF_INET, SOCK_STREAM, 0), "ERROR | Failed to Create Socket!\n"); // Create a socket
	errCheck(-1, setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)), "Set socket failed!!"); // Set socket option
	errCheck(-1, fcntl(this->server_fd, F_SETFL, O_NONBLOCK), "Set socket to non-blocking failed!!"); // Set socket to non-blocking
	errCheck(-1, bind(this->server_fd, (struct sockaddr*)&(this->server_addr), sizeof(this->server_addr)), "ERROR | Binding Failed!"); // Bind the socket
	errCheck(-1, listen(this->server_fd, SOMAXCONN), "ERROR | Port Listening Failed...!"); // Listen on the port
}

void Server::initCommands(){
	this->_commandMap["BOT"]  = &Server::BOT;
	this->_commandMap["CAP"]  = &Server::CAP;
	this->_commandMap["JOIN"] = &Server::JOIN;
	this->_commandMap["KICK"] = &Server::KICK;
	this->_commandMap["MODE"] = &Server::MODE;
	this->_commandMap["NICK"] = &Server::NICK;
	this->_commandMap["PART"] = &Server::PASS;
	this->_commandMap["PASS"] = &Server::PASS;
	this->_commandMap["PRIVMSG"] = &Server::PRIVMSG;
	this->_commandMap["QUIT"] = &Server::USER;
	this->_commandMap["USER"] = &Server::USER;
	this->_commandMap["WHO"] = &Server::WHO;
}

/**
* @param errcnd : error condition
* @param res : return value
* @param message : error message
* @if res == errcnd
* @throw runtime_error(message)
* @endif
* @return res : return value
* */
int Server::errCheck(int errcnd, int res, string message)
{
	if (res == errcnd)
		throw runtime_error(message);
	return res;
}
/**
 * @param client_fd : client file descriptor
 * @param message : message to send
 * @if send(client_fd, message, message_len, 0) == -1
 * @throw runtime_error("ERROR | Failed to send message to client " + client_fd)
 * @elseif bytes_sent < message_len
 * @throw runtime_error("WARNING | Not all data sent to client " + client_fd)
 * @else
 * @return void
 */
void Server::sendMessage(int client_fd, const char* message) {
    ssize_t bytes_sent;
    size_t message_len = strlen(message);

    bytes_sent = send(client_fd, message, message_len, 0);

    if (bytes_sent == -1) {
        cerr << "ERROR | Failed to send message to client " << client_fd << endl;
    } else if (bytes_sent < message_len) {
        cerr << "WARNING | Not all data sent to client " << client_fd << endl;
    } else {
		return;
    }
}