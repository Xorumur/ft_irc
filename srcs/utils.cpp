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

void	is_Accepted(Client * client) {
	if (client->nick == true && client->pass == true && client->user == true) {
		std::string Welcome;
		client->accepted = true;
		Welcome = "42.Mathieu.com 001 " + client->getNick() + " :Welcome to the Internet Relay Network " + client->getNick() + "!" + client->getUser() + "@127.0.0.1";
		send(client->getFd(), Welcome.c_str(), strlen(Welcome.c_str()), 0); 
	}
	return ;
}
