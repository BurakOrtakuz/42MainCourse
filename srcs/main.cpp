#include "../include/Server.hpp"

int main(int ac, char **av)
{
	try {
		if (ac != 3)
			throw std::runtime_error("./ircserv <port> <password>");
		Server *s = new Server(atoi(av[1]), av[2]);
		s->start();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}