#include "../includes/irc.hpp"


void	cmdUser(Server & serv, Client * client, std::vector<std::string> line) {
	// for (size_t i = 0; serv.user.size(); i++) {
	// 	if (client->getUser() == serv.user[i]->getUser())
	// 	{
	// 		std::string err;
	// 		return ;
	// 	}
	// }
	(void)serv;
	client->setUser(line[1]);
	client->user = true;
	is_Accepted(client);
}