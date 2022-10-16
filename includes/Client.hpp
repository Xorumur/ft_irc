#pragma once

#include "irc.hpp"

class Client {
	private:
		std::string		_password;
		std::string		_nickname;
		std::string 	_realname;
		std::string 	_username;
		
		// char			mode;
		// Channel*		_curr;
	
		unsigned long	fd;

	public:
		bool	pass;
		bool	nick;
		bool	real;
		bool	user;
		bool	accepted; // Check if the user is accepted by the server
		// int				sfd;

	public:
		Client() : _password() { 
			fd = 0;
			pass = false;
			nick = false;
			real = false;
			user = false;
			accepted = false;

			// _curr = NULL;
		}

		Client(unsigned long _n) {
			fd = _n;
			pass = false;
			nick = false;
			real = false;
			user = false;
			accepted = false;
		}

		Client(const Client & rhs) {
			*this = rhs;
		}

		Client & operator=(const Client & rhs) {
			_nickname = rhs._nickname;
			_realname = rhs._realname;
			_username = rhs._username;
			// _curr = rhs._curr;
			fd = rhs.fd;
			return (*this);
		}

		void	setFd(int _n) {
			fd = _n;
		}

		unsigned long getFd(void) {
			return (fd);
		}

		std::string getPwd(void) {
			return (_password);
		}

		void	setPwd(std::string name) {
			_password = name;
		}

		std::string getNick(void) {
			return (_nickname);
		}

		void	setNick(std::string nick) {
			_nickname = nick;
		}

		std::string getUser(void) {
			return (_username);
		}
		
		void	setUser(std::string user) {
			_username = user;
		}

		void	setReal(std::string real) {
			_realname = real;
		}
};