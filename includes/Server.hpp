#pragma once 

# include "irc.hpp"

#define TRUE   1 
#define FALSE  0 
#define SA struct sockaddr
#define MAX 80

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
            if ((new_socket = accept(sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)  
				throw AcceptFailed();
			else
				tmp->setFd(new_socket);
			this->user.push_back(tmp);
			// std::cout << "New size = " << this->user.size() << std::endl;
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                   (address.sin_port));
			fresh_fd = new_socket;
		}

		void	deleteClient(unsigned long s) {
			std::vector<Client *>::iterator	it = user.begin();

			for (size_t i = 0; i < user.size() && user[i]->getFd() != s; i++, it++)
				;
			user.erase(it);
		}

		void	start(void) {
			int opt = TRUE;  
   			int addrlen , client_socket[30] , max_clients = 30 , i;  
    		struct sockaddr_in address;  
         
			// char buffer[1025];  //data buffer of 1K 
				
			//set of socket descriptors 
			fd_set readfds;  
				
			//a message 
			// char *message = "ECHO Daemon v1.0 \r\n";  
			
			//initialise all client_socket[] to 0 so not checked 
			for (i = 0; i < max_clients; i++)  
			{  
				client_socket[i] = 0;  
			}  
				
			//create a master socket 
			if( (sfd = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
				throw SocketCreaFailed();
			
			//set master socket to allow multiple connections , 
			//this is just a good habit, it will work without this 
			if( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
				throw SetSocketOptFailed();
			
			//type of socket created 
			address.sin_family = AF_INET;  
			address.sin_addr.s_addr = INADDR_ANY;  
			address.sin_port = htons(getPort());  
				
			//bind the socket to localhost port 8888 
			if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0)  
				throw SocketBindFailed();

			printf("Listener on port %d \n", getPort());  
				
			//try to specify maximum of 3 pending connections for the master socket 
			if (listen(sfd, 3) < 0)  
				throw SocketListenFailed();
				
			//accept the incoming connection 
			addrlen = sizeof(address);  
			puts("Waiting for connections ...");  
		// 	Server_loop(serv, readfds, max_clients, address, addrlen, i, client_socket);
		// }
		// 	// FIN TCP

		// void	Server_loop(Server serv, fd_set readfds, int max_clients, struct sockaddr_in address, int addrlen, int i, int *client_socket)
		// {
			char buffer[1025];
			int valread;
			int max_sd;
			int sd;
			int activity;
			// int new_socket;
			while(42)  
			{  
				//clear the socket set 
				FD_ZERO(&readfds);  
				//add master socket to set 
				FD_SET(sfd, &readfds);  
				max_sd = sfd;  
				for (size_t i = 0; i < user.size(); i++) {
					sd = user[i]->getFd();
					if (sd > 0)
						FD_SET(sd, &readfds);
					if (sd > max_sd)
						max_sd = sd;
				}
				//wait for an activity on one of the sockets , timeout is NULL , 
				//so wait indefinitely
				activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
				if ((activity < 0) && (errno!=EINTR))  
					throw SelectFailed();
					
				//If something happened on the master socket , 
				//then its an incoming connection 
				if (FD_ISSET(sfd, &readfds))  
					addClient();
				for (size_t i = 0; i < user.size(); i++) {
					sd = user[i]->getFd();
					// std::cout << "SD : " << sd << std::endl;
					if (FD_ISSET(sd, &readfds)) {
						// std::cout << "ici" << std::endl;
						if ((valread = recv(sd, buffer, 1024, 0)) == 0)
						{  
							//Somebody disconnected , get his details and print 
							getpeername(sd , (struct sockaddr*)&address , \
								(socklen_t*)&addrlen);  
							printf("Host disconnected , ip %s , port %d \n" , 
								inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
							
							//Close the socket and mark as 0 in list for reuse 
							close( sd ); 
							deleteClient(sd);
							client_socket[i] = 0;  
						}
			
						else {
							// std::cout << "la" << std::endl;
							buffer[valread] = '\0';
							std::cout << buffer << std::endl;
							// parse parse(buffer);
							send(sd, buffer, strlen(buffer), 0);
						}
					}
				}  		
			}
			return ;
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

