#pragma once

#include "irc.hpp"

class Channel {
	private:
		// int	_port;
		std::string name;

		std::vector<Client *> members;
		std::vector<Client *> superUser;
	public:
		Channel() { }
		~Channel() { }

		// void	sendToMembers(std::string msg) {
		// 	for (size_t i = 0; i < members.size(); i++) {
				
		// 	}
		// }
};