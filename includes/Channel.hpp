#pragma once

#include "irc.hpp"

class Channel {
	private:
		// int	_port;
		std::string name;
	public:
		std::vector<Client *> members;
		std::vector<Client *> superUser;
	public:
		Channel() { }
		Channel(char* _name) { 
			std::string tmp(_name);
			name = tmp;
		}
		// Channel(std::string _name, Client * super) : name(_name) { 
		// 	superUser.push_back(super);
		// }
		~Channel() { }

		void	addSuper(Client * client) {
			superUser.push_back(client);
		}

		std::string getName() {
			return (name);
		}
		// void	sendToMembers(std::string msg) {
		// 	for (size_t i = 0; i < members.size(); i++) {
				
		// 	}
		// }
};