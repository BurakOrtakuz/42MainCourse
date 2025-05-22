#include "../../include/Server.hpp"

void Server::CAP(vector<string>& params, Client& client)
{
    cout << YELLOW "[" << client.getClientFd() << "] " << "CAP command called" << RESET << endl;
    (void)params;
}