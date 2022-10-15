#include "../includes/irc.hpp"

void	irc(int ac, char **av) {
	if (ac == 3) {
		// Server serv;
		try {
			Server serv(av[2], av[1]);;
			serv.start();
		}
		catch (std::exception & ex) {
			std::cout << ex.what() << std::endl;
			return ;
		}
	} else 
	{ std::cout << "Must be called like : ./ircserv <port> <password>" << std::endl; return; }
}	