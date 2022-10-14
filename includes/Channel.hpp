#pragma once

#include "irc.hpp"

class Channel {
	private:
		int	_port;

		std::vector<Client *> members;
	public:
		Channel() { }

		Channel()
};