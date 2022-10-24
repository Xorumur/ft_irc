#include "../includes/irc.hpp"


/*  Command: JOIN
   Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
*/

void	sendChannelInfo(Channel * chan, Client * client) {
	std::string chanInfo;


	/* RPL_TOPIC */
	chanInfo = "332 " + client->getNick() + " " + chan->getName() + " :No Topic set\r\n";
	send(client->getFd(), chanInfo.c_str(), chanInfo.size(), 0);
	chanInfo.clear();


	/* RPL_NAMREPLY */
	chanInfo = "353 " + client->getNick() + " = " + chan->getName() + " :";
	for (size_t i = 0; i < chan->members.size(); i++) {
		if (chan->isSuper(chan->members[i]) == true)
			chanInfo += "@";
		chanInfo += chan->members[i]->getNick() + " ";
	}
	chanInfo.erase(chanInfo.length() - 1);
	chanInfo += "\r\n";
	send(client->getFd(), chanInfo.c_str(), chanInfo.size(), 0);
	chanInfo.clear();


	/* RPL_ENDOFNAMES */
	chanInfo = "366 " + client->getNick() + " " + chan->getName() + " :End of NAMES ist\r\n";
	send(client->getFd(), chanInfo.c_str(), chanInfo.size(), 0);
	return ;
}

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
	else if (cmd.size() == 2 && cmd[1][0] == '0')
	{
		/* In the RFC they that the '0' parameters must make the client leave all the channel where he is
		   but I don't know if we have to do it, so just in case I've made it */
		for (size_t i = 0; i < serv.Chan.size();  i++)
			serv.delClientFromChann(client, serv.Chan[i], serv);
		client->setCurrChannelNull();
		return;
	}

	/* The third argument of the command JOIN is the key (password of the Channel).
	   Here I'll try to get it */
	
	bool setK = false;
	std::vector<std::string>	keys;
	size_t	sizeK = 0;
	if (cmd.size() == 3){
		std::string d = ",";
		keys  = split(cmd[2], d);
		setK = true;
		sizeK = keys.size();
	}

	/* Here I split the arg with ',' because you can join multiples channels with JOIN like :
	   JOIN #first,#second */
	std::string delim = ",";
	std::vector<std::string> newChann = split(cmd[1], delim);

	/* _wtj means want to join, here we gonna search if the channel exist in the vector 
	   of channel that we have in the serv, and if it does not exist,
	   we will have to create one */
	for (size_t i = 0; i < newChann.size(); i++) {
		Channel* _wtj = serv.findChannelByName(newChann[i]);
		if (!_wtj) {
			/* If _wtj is NULL it means that there is no Channel with this name. 
			So here I create a Channel and push it back to the vector of channel that the server possess */
			Channel  *to_add = new Channel(newChann[i]);
			to_add->addSuper(client);
			to_add->addMembers(client);
			if (setK == true && i < keys.size())
				to_add->setPass(keys[i]);
			serv.Chan.push_back(to_add);
			client->setCurrChannel(to_add);
			std::cout << "Size of chann : " << serv.Chan.size() << std::endl;
			/* There is a specific message to send to all the users of the channel that the client join */
			// std::string wlcMsg;
			// wlcMsg = client->getNick() + "!" + client->getUser() + "@127.0.0.1 JOIN " + newChann[i] + "\r\n";
			// sendToChannel(wlcMsg, _wtj, client, true); 
		}
		else {
			/* If it's not NULL it means a channel with this name already exists. 
			So we have to make this client join this channel */
			if (i < sizeK) {
				/* Here is the case where the client send a key to join a channel */
				/* The case where the client send a key but the channel does not have one is handle by the 
				   _wtj->pass == false */
				std::cout << "i < sizeK" << std::endl;
				if (_wtj->pass == false || keys[i] == _wtj->getPass()) {
					_wtj->members.push_back(client);
					client->setCurrChannel(_wtj);

					/* There is a specific message to send to all the users of the channel that the client join */
					std::string wlcMsg;
					wlcMsg = client->getNick() + "!" + client->getUser() + "@127.0.0.1 JOIN " + newChann[i] + "\r\n";
					sendToChannel(wlcMsg, _wtj, client, true);
					sendChannelInfo(_wtj, client);
				}
				else if (keys[i] != _wtj->getPass()) {
					/* Wrong key */
					errMsg = "475 " + _wtj->getName() + " :Cannot join channel (+k)\r\n";
					send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
				}
			}
			else {
				if (_wtj->pass == false) {
					/* Channel don't have a key */
					std::cout << "No key" << std::endl;
					_wtj->members.push_back(client);
					client->setCurrChannel(_wtj);

					/* There is a specific message to send to all the users of the channel that the client join */
					std::string wlcMsg;
					wlcMsg = client->getNick() + "!" + client->getUser() + "@127.0.0.1 JOIN " + newChann[i] + "\r\n";
					sendToChannel(wlcMsg, _wtj, client, true); 
					sendChannelInfo(_wtj, client);
				}
				else {
					/* Channel have a key but client don't have sent the key */
					errMsg = "475 " + _wtj->getName() + " :Cannot join channel (+k)\r\n";
					send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
				}
			}
		}
	}
	std::cout << "This user belong to the channel : " << client->getCurr()->getName() << std::endl;
	return ;
}