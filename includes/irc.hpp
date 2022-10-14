#pragma once

# include <iostream>
# include <exception>
# include <cstdlib>
# include <string>
# include <vector>

# include <stdio.h>
# include <netdb.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/socket.h>
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 

# include "except.hpp"

# include "Client.hpp"
# include "Server.hpp"

// # include "Channel.hpp"


void	irc(int ac, char **av);
void 	tcp(Server serv);
// void	Server_loop(Server serv, int sockfd);
void	Server_loop(Server serv, fd_set readfds, int max_clients, struct sockaddr_in address, int addrlen, int i, int *client_socket);
void	parser_cmd(std::string cmd, int s, Server serv);