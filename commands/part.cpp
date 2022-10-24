#include "../includes/irc.hpp"

void	cmdPart(Server & serv, Client * client, std::vector<std::string> cmd) {
	std::string errMsg;

	/* If there is just only the commad PART it miss the name of the channel to leave */
	if (cmd.size() == 1) {
		errMsg = "461 PART :Not enough parameters\r\n";
		send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
		return ;
	}

	/* I split with the delim ',' because you can leave multiples channel in one command like this : 
	   PART #FIRST,#SECOND */
	std::string delim(",");
	std::vector<std::string> Chan_to_leave = split(cmd[1], delim);


	for (size_t i = 0; i < Chan_to_leave.size(); i++) {
		std::string Chann = Chan_to_leave[i];
		Channel * to_leave = serv.findChannelByName(Chann);
		if (!to_leave) {
			/* If the channel the client wants to leave doesn't exist */
			errMsg = "403 " + Chann + " :No such channel\r\n";
			send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
		}
		else {
			/* If the client belong to the channel I leave it */
			if (to_leave->isMembers(client) == true || to_leave->isSuper(client) == true) {
				errMsg = client->getNick() + "!" + client->getUser() + "@127.0.0.1 PART";
				errMsg += " " + Chann;
				if (cmd.size() > 2) {
					/* If a the client leave with a message */
					std::string partMsg(&cmd[2][0]);
					errMsg += partMsg;
				}
				errMsg += "\r\n";
				std::cout << "This is what I send to PART commad to all the other clients : " << errMsg << std::endl;
				/* Send the information that the client leave the channel to all the other user that belongs to the CHANNEl */
				sendToChannel(errMsg, to_leave, client, false);
				to_leave->deleteClient(client);
			}
			else {
				/* Otherwise I send to the client an error message */ 
				errMsg = "442 " + Chann + " :You're not on that channel\r\n";
				send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
			}
		}
	}
}
