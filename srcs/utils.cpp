#include "../includes/irc.hpp"

// PASS
// NICK
// REAL

void	parser_cmd(std::string cmd, int s, Server serv) {
	// char	**tab = str.strtok
	(void)s;
	Client *tmp = serv.findClientByFd(s);
	if (tmp == NULL)
	{
		std::cout << "NULL" << std::endl;
		return ;
	}
	if (cmd.find("PASS") == 0 && tmp->getPwd().empty() == 0)
	{
		// std::string pass = cmd.substr(5, cmd.find(" "));
		// std::cout << pass << std::endl;
		tmp->setPwd(cmd.substr(5, cmd.find(" ")));
	}
}