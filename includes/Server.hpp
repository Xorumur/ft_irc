#pragma once 

# include "irc.hpp"

class ErrorInPort : public std::exception {
	public:
		virtual const char* what() const throw()	
		{
			return ("Not a valable number for the Port between [0; 65,353]");
		}
};

class ErrorInPortInput : public std::exception {
	public:
		virtual const char* what() const throw()	
		{
			return ("Port must contain only digit");
		}
};

class	Server {
	private:
		std::string 			_password;
		int						_port;
		
		// int					_id;
	public:
		std::vector<Client *>	user;
		int						sfd;
		int						fresh_fd;
	public:
		Server() {} 

		Server(char *pwd, char *New_p) : _password(pwd) {
			std::string parse(New_p);

			for (size_t i = 0; i < parse.length(); i++) {
				if (!isdigit(parse[i]))
					throw ErrorInPortInput();
			}
			_port = atoi(New_p);
			if (_port < 0 || _port > 65535)
				throw ErrorInPort();
		}

		Server(const Server & rhs) {
			_port = rhs.getPort();
			_password = rhs.getPassword();
		}
		
		~Server() { }

		std::string getPassword(void) const {
			return (_password);
		}

		int	getPort(void) const {
			return (_port);
		}

		void	setPort(int port) {
			_port = port;
		}

		void	setPassword(std::string pass) {
			_password = pass;
		}

		void	addClient(void) {
			struct sockaddr_in address;
			int new_socket;
			int addrlen = sizeof(address);

			Client	*tmp = new Client;
            if ((new_socket = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
				throw AcceptFailed();
			else
				tmp->setFd(new_socket);
			this->user.push_back(tmp);
			std::cout << "New size = " << this->user.size() << std::endl;
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                   (address.sin_port));
			fresh_fd = new_socket;
		}


		Client * findClientByFd(unsigned long s) {
			std::cout << "SIZE = " << this->user.size() << std::endl;
			for (size_t i = 0; i < user.size(); i++) {
				std::cout << s << " : " << user[i]->getFd() << std::endl;
				if (user[i]->getFd() == s)
					return (user[i]);
			}
			return (NULL);
		}
};

