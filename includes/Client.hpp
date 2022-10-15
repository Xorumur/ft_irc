#pragma once

#include "irc.hpp"

class Client {
	private:
		std::string		_password;
		std::string		_nickname;
		std::string 	_realname;
		std::string 	_username;

		// Channel*		_curr;
	
		unsigned long	fd;

	public:
		bool	pass;
		bool	nick;
		bool	real;
		bool	user;
		// int				sfd;

	public:
		Client() : _password() { 
			fd = 0;
			pass = false;
			nick = false;
			real = false;
			user = false;

			// _curr = NULL;
		}

		Client(unsigned long _n) {
			fd = _n;
			pass = false;
			nick = false;
			real = false;
			user = false;
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

		
};