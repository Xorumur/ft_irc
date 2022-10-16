#include "../includes/irc.hpp"

void	cmdPass(std::string pass, Server & serv, Client * client) {
	if (client->accepted == true)
		return ;
	else if (pass == serv.getPassword()) {
		client->setPwd(pass);
		client->pass = true;
	}
	else if (pass != serv.getPassword() && client->pass == true) {
		client->pass = false;
		client->setPwd(pass);
	}
	is_Accepted(client);
	return ;
}