#pragma once

#include "irc.hpp"
#include "Server.hpp"
#include "Client.hpp"

class Server;
class Client;

class parse {
	private:
		std::string	currMess;
		std::vector<std::string>	tab;
		


	public:
		parse() : currMess(NULL) { }

		parse(char *buffer) : currMess(buffer) {
			// std::cout << "test" << std::endl;
			std::string delim("\r\n");
			tab = split(currMess, delim);
			if (tab.size() == 1) {
				delim = "\n";
				tab = split(currMess, delim);
			}
			// std::cout << tab.size() << std::endl;
			for (size_t i = 0; i < tab.size(); i++) {
				std::cout << "ARG[" << i << "] = " << tab[i] << std::endl;
			}
		}

		void	to_register(Server & serv, Client * Client) {
			std::cout << "Server starting to parse what the client has send" << std::endl;
			std::string delim(" ");
			for (size_t i = 0; i < tab.size(); i++) {
				std::vector<std::string> line = split(tab[i], delim);
				// for (size_t j = 0; j < line.size(); j++)
				// 	std::cout << "{" << line[j] << "}" << std::endl;
				if (line[0] == "NICK" && line.size() == 2)
					cmdNick(serv, Client, line[1]);
				else if (line[0] == "NICK" && line.size() == 1) {
					std::string to_send = "431 " + Client->getNick() + " :No nickname given";
					send(Client->getFd(), to_send.c_str(), strlen(to_send.c_str()), 0);
				}	
				else if (line[0] == "USER" && line.size() >= 5)
					cmdUser(Client, line);
				else if (line[0] == "USER" && line.size() <= 5) {
					std::string to_send = "461 USER :Not enough parameters";
					send(Client->getFd(), to_send.c_str(), strlen(to_send.c_str()), 0); 
				}
				else if (line[0] == "PASS")
					cmdPass(line[1], serv, Client);
				// else if (line[0] == "MODE") {
				// 	cmdMode(serv, client, line);
				// }
				// else if (line[0] == "QUIT" && line.size() > 1) {
				// 	cmdQuit(serv, client);
				// }
			}
		}
};