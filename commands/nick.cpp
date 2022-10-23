#include "../includes/irc.hpp"

#define N_ERROR " :Nickname is already in use"

void	cmdNick(Server & serv, Client * client, std::string nick) {
	for (size_t i = 0; i < serv.user.size(); i++) {
		if (serv.user[i]->getNick() == nick) {
			std::string ERR;
			ERR = "433 * " + nick + N_ERROR;
			send(client->getFd(), ERR.c_str(), strlen(ERR.c_str()), 0);
			std::cout << "ERROR IN THE NICKNAME" << std::endl;
			return ;
		}
	}
	client->setNick(nick);
	client->nick = true;
	std::cout << "NICKNAME IMPLEMENTED" << std::endl;
	is_Accepted(client);
	return ;
}