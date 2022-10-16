#include "../includes/irc.hpp"

#define E_NMP "461"
#define ERR_NEEDMOREPARAMS ":Not enough parameters"

#define E_UDM "502"
#define ERR_USERSDONTMATCH "change mode for other users"

#define E_MUF "501"
#define ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"

void	cmdMode(Server & serv, Client * client, std::vector<std::string> line) {
	// ERR_NEEDMOREPARAMS
	std::string errMsg;

	if (line.size() == 2) {
		errMsg = E_NMP + " MODE " + ERR_NEEDMOREPARAMS;
		send(client->getFd(), errMsg.c_str(), strlen(errMsg.c_str()), 0);
		return ;
	}
	else {
		for (size_t i = 0; serv.user[i])
	}
}