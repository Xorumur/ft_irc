#include "../includes/irc.hpp"

// PASSWORD
// NICKNAME
// USERNAME

std::vector<std::string> split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    // res.push_back (s.substr (pos_start));
    return res;
}

// std::vector<std::string> split(std::string name, std::string delim) {
// 	std::vector<std::string>	ret;

// 	for (size_t i = 0; name.find(delim) != std::string::npos; ) {
		
// 	}
// }

// void	parser_cmd(std::string cmd, int s, Server serv) {
// 	// char	**tab = str.strtok
// 	(void)s;
// 	Client *tmp = serv.findClientByFd(s);
// 	if (tmp == NULL)
// 	{
// 		std::cout << "NULL" << std::endl;
// 		return ;
// 	}
// 	if (cmd.find("PASS") == 0 && tmp->getPwd().empty() == 0)
// 	{
// 		// std::string pass = cmd.substr(5, cmd.find(" "));
// 		// std::cout << pass << std::endl;
// 		tmp->setPwd(cmd.substr(5, cmd.find(" ")));
// 	}
// }