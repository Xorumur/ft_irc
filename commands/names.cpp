#include "../includes/irc.hpp"

void	cmdNames(Server & serv, Client* client, std::vector<std::string> line)
{
	std::string	msg;
	Channel*	chan = NULL;
	if (line.size() < 2)
	{
        msg = "461 " + client->getNick() + " :Not enough parameters\r\n";
		rplDisplay(msg);
        send(client->getFd(), msg.c_str(), strlen(msg.c_str()), 0);
        return;
    }
	else if (line.size() == 2)
	{
		chan = serv.findChannelByName(line[1]);
		if (chan == NULL)
        {
            msg = ":" + client->getNick() + "!" + client->getUser() + "@127.0.0.1 " + line[1] + " :No such channel\r\n";
            rplDisplay(msg);
            send(client->getFd(), msg.c_str() , msg.length(), 0);
            return ;
        }
        else {
            if (chan->isHere(client) == true)
                sendChannelInfo(chan, client);
            else {
                msg = "442 " + client->getNick() + " " + chan->getName() + " :You're not on that channel\r\n";
                rplDisplay(msg);
                send(client->getFd(), msg.c_str(), msg.size(), 0);
            }
        }
	}
}