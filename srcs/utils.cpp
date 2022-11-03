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
		// Welcome = "001 " + client->getNick() + " :Welcome to the Internet Relay Network ";
		// Welcome += client->getNick() + "!" + client->getUser() + "@127.0.0.1\r\n";
		Welcome = ":localhost 001 " + client->getNick() + "\r\n" + "\"Welcome to the Internet Relay Chat Network " + client->getNick() + "!" + client->getUser() + "@localhost" + "\"" + "\r\n";
		// std::cout << Welcome << std::endl;
		std::cout << "\e[1;31mWelcome message send successfuly\e[0m" << std::endl; 
		send(client->getFd(), Welcome.c_str(), strlen(Welcome.c_str()), 0);
		std::cout << "\e[1;36mClient has sent all the information requiered to be log\e[0m" << std::endl; 
	}
	return ;
}

/* Here I send the message to all the client who belong to this channel */
void	sendToChannel(std::string msg, Channel * chan, Client * client, bool himself) {
	// std::cout << "Size of vector channel on serv : " << chan->members.size() << std::endl;
	for (size_t i = 0; i < chan->members.size(); i++) {
		if (chan->members[i]->getNick() == client->getNick() && himself == false)
			;
		else
			send(chan->members[i]->getFd(), msg.c_str(), msg.size(), 0);
	}
}

/* Functions that helps to display the error message with the strict format to send */
void	send_error_code(unsigned int fd, std::string error_code, std::string nickname, std::string arg, std::string error_msg)
{
	std::string		msg;
	msg = ":NiceIRC " + error_code + " " + nickname + " " + arg + " " + error_msg + "\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
}

void	colorMsg(std::string colorCode, char *msg)
{
	if (msg[strlen(msg) - 1] == '\n')
		std::cout << colorCode << msg << "\e[0m" << std::endl;
	else
		std::cout << colorCode << msg << "\e[0m";
}