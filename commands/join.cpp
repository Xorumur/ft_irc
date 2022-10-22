#include "../includes/irc.hpp"


/*  Command: JOIN
   Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
*/

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
		for (size_t i = 0; i < serv.Chan.size();  i++)
			serv.delClientFromChann(client, serv.Chan[i], serv);
		client->setCurrChannelNull();
		return;
	}

	/* The third argument of the command JOIN is the key (password of the Channel).
	   Here I'll try to get it */
	
	bool setK = false;
	std::vector<std::string>	keys;
	if (cmd.size() == 3){
		std::string d = ",";
		keys  = split(cmd[2], d);
		setK = true;
	}

	/* Here I split the arg with ',' because you can join multiples channels with JOIN like :
	   JOIN #first,#second */
	std::string delim = ",";
	std::vector<std::string> newChann = split(cmd[1], delim);

	/* _wtj means want to join, here we gonna search if the channel exist in the vector 
	   of channel that we have in the serv, and if it does not exist,
	   we will have to create one */
	for (size_t i = 0; i < newChann.size(); i++) {
		Channel* _wtj = serv.findChannelByName(&newChann[i][1]);
		if (!_wtj) {
			/* If _wtj is NULL it means that there is no Channel with this name. 
			So here I create a Channel and push it back to the vector of channel that the server possess */
			Channel  *to_add = new Channel(&newChann[i][1]);
			to_add->addSuper(client);
			if (setK == true && i < keys.size())
				to_add->setPass(keys[i]);
			serv.Chan.push_back(to_add);
			client->setCurrChannel(to_add);
			// return ;
		}
		else {
			/* If it's not NULL it means a channel with this name already exists. 
			So we have to make this client join this channel */
			if (_wtj->pass == false || keys[i] == _wtj->getPass()) {
				_wtj->members.push_back(client);
				client->setCurrChannel(_wtj);
			}
			else if (keys[i] != _wtj->getPass()) {
				errMsg = "475 " + _wtj->getName() + " :Cannot join channel (+k)\r\n";
				send(client->getFd(), errMsg.c_str(), errMsg.size(), 0);
			}

			// else if (keys[i] == _wtj->getPass()) {
			// 	_wtj->members.push_back(client);
			// 	client->setCurrChannel(_wtj);
			// }
		}
	}
	std::cout << "This user belong to the channel : " << client->getCurr()->getName() << std::endl;
	return ;
}