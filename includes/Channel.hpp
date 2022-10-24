#pragma once

#include "irc.hpp"

class Channel {
	private:
		// int	_port;
		std::string name;
		std::string password;
	public:
		bool					pass;
		std::vector<Client *>	members;
		std::vector<Client *>	superUser;
	public:
		Channel() { }
		Channel(std::string _name) : name(_name) { }
		Channel(char* _name) { 
			std::string tmp(_name);
			name = tmp;
			pass = false;
		}
		// Channel(std::string _name, Client * super) : name(_name) { 
		// 	superUser.push_back(super);
		// }
		~Channel() { }

		void	addSuper(Client * client) {
			superUser.push_back(client);
		}

		void	addMembers(Client * client) {
			members.push_back(client);
		}

		std::string getName() {
			return (name);
		}

		void	setPass(std::string _pass) {
			password = _pass;
		}

		std::string	getPass(void) {
			return (password);
		}

		bool	isSuper(Client * client) {
			for (size_t i = 0; i < superUser.size(); i++) {
				if (client->getNick() == superUser[i]->getNick())
					return true;
			}
			return false;
		}

		bool isMembers(Client * client) {
			for (size_t i = 0; i < members.size(); i++) {
				if (client->getNick() == members[i]->getNick())
					return true;
			}
			return false;
		}

		void	deleteMembers(Client * client) {
			std::vector<Client *>::iterator it = members.begin();
			for (size_t i = 0; i < members.size(); i++, it++) {
				if (members[i]->getNick() == client->getNick()) {
					members.erase(it);
					return ;
				}
			}
		}

		void	deleteClient(Client * client) {
			std::vector<Client *>::iterator it = members.begin();
			for (size_t i = 0; i < members.size(); i++, it++) {
				if (members[i]->getNick() == client->getNick()) {
					members.erase(it);
				}
			}
			it = superUser.begin();
			for (size_t i = 0; i < superUser.size(); i++, it++) {
				if (superUser[i]->getNick() == client->getNick())
					superUser.erase(it);
			}
		}

		// void	sendToMembers(std::string msg) {
		// 	for (size_t i = 0; i < members.size(); i++) {
				
		// 	}
		// }
};