#include "../includes/irc.hpp"


void	cmdUser(Client * client, std::vector<std::string> line) {
	client->setUser(line[1]);
	client->user = true;
	is_Accepted(client);
}