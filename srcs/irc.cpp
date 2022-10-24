#include "../includes/irc.hpp"

int	irc(int ac, char **av) {
	if (ac == 3) {
		// Server serv;
		try {
			Server serv(av[2], av[1]);;
			serv.start();
		}
		catch (std::exception & ex) {
			std::cout << ex.what() << std::endl;
		}
	} else 
	{ std::cout << "Must be called like : ./irc <port> <password>" << std::endl;}
	return 0;
}	