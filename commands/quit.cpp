#include "../includes/irc.hpp"

void	cmdQuit(Server & serv, Client * client, ) {
	
	
	serv.deleteClient(client->getFd());
}