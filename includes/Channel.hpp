#pragma once

#include "irc.hpp"

class Channel {
	private:
		int	_port;

		std::vector<Client *> members;
	public:
		Channel() { }

		// void	sendToMembers(std::string msg) {
		// 	for (size_t i = 0; i < members.size(); i++) {
				
		// 	}
		// }
};