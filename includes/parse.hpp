#pragma once

#include "irc.hpp"

class parse {
	private:
		std::string	currMess;
		std::vector<std::string>	tab;
		


	public:
		parse() : currMess(NULL) { }

		parse(char *buffer) : currMess(buffer) {
			std::cout << "test" << std::endl;
			std::string delim("\r\n");
			tab = split(currMess, delim);
			if (tab.size() == 1) {
				delim = "\n";
				tab = split(currMess, delim);
			}
			std::cout << tab.size() << std::endl;
			for (size_t i = 0; i < tab.size(); i++) {
				std::cout << "ARG[" << i << "] = " << tab[i] << std::endl;
			}
		}

		void	exec(Server * serv) {
			if (tab[0].find("CAP LS ") == std::string::npos)
		}
};