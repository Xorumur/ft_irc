#include "../includes/irc.hpp"

std::vector<std::string> split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


/* It's function that monitor when a Client Info is set.
   If all of his info are set so I can accept him and return true */
void	is_Accepted(Client * client) {
	if (client->nick == true && client->pass == true && client->user == true) {
		std::string Welcome;
		client->accepted = true;
		Welcome = "001 " + client->getNick() + " :Welcome to the Internet Relay Network ";
		Welcome += client->getNick() + "!" + client->getUser() + "@127.0.0.1\r\n";
		std::cout << Welcome << std::endl;
		send(client->getFd(), Welcome.c_str(), strlen(Welcome.c_str()), 0); 
	}
	return ;
}

/* Here I send the message to all the client who belong to this channel */
void	sendToChannel(std::string msg, Channel * chan, Client * client, bool himself) {
	std::cout << "Size of vector channel on serv : " << chan->members.size() << std::endl;
	for (size_t i = 0; i < chan->members.size(); i++) {
		if (chan->members[i]->getNick() == client->getNick() && himself == false)
			;
		else
			send(chan->members[i]->getFd(), msg.c_str(), msg.size(), 0);
	}
}
