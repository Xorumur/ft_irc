#include "../includes/irc.hpp"


void	cmdJoin(Server & serv, Client * client, std::vector<std::string> cmd) {
	std::string errMsg;
	if (cmd.size() == 1) {
		/* If there is only JOIN it miss some parameters */
		errMsg = "461 JOIN :Not enough parameters\r\n";
		send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
		return ;
	}
	else if (cmd[1][0] != '#' && cmd[1][0] != '&') {
		/* When you want to join a channel the name of the channel must start with a # or & */
		errMsg = "476 JOIN :Bad Channel Mask\r\n";
		send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
		return ;
	}
	/* _wtj means want to join, here we gonna search if the channel exist in the vector 
	   of channel that we have in the serv, and if it does not exist,
	   we will have to create one */
	Channel* _wtj = serv.findChannelByName(&cmd[1][1]);
	if (!_wtj) {
		/* If _wtj is NULL it means that there is no Channel with this name. 
		   So here I create a Channel and push it back to the vector of channel that the server possess */
		Channel  *to_add = new Channel(&cmd[1][1]);
		to_add->addSuper(client);
		serv.Chan.push_back(to_add);
		return ;
	}
	else {
		/* If it's not NULL it means a channel with this name already exists. 
		   So we have to make this client join this channel */
		_wtj->members.push_back(client);
		return ;
	}
	return ;
}