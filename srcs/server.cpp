#include "../includes/irc.hpp"


#define TRUE   1 
#define FALSE  0 
#define SA struct sockaddr
#define MAX 80

// void tcp(Server serv) {
// 	int	connfd;
// 	socklen_t len;
// 	struct sockaddr_in servaddr;
// 	struct sockaddr_in cli;
// 	serv.sfd = socket(AF_INET, SOCK_STREAM, 0);
// 	if (serv.sfd == -1 )
// 		throw SocketCreaFailed();
// 	bzero(&servaddr, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//     servaddr.sin_port = htons(serv.getPort());

// 	// Binding newly created socket to given IP and verification
// 	if ((bind(serv.sfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
// 		throw SocketBindFailed();

// 	// Now server is ready to listen and verification
// 	if ((listen(serv.sfd, 5)) != 0)
// 		throw SocketListenFailed();
// 	len = sizeof(cli);

// 	// Accept the data packet from client and verification
//     connfd = accept(serv.sfd, (SA*)&cli, &len);
// 	// serv.setID(connfd);
//     if (connfd < 0)
// 		throw ServerAcceptFailed();
// 	else
// 		std::cout << "Connexction established" << std::endl;
// 	Server_loop(serv, serv.sfd);
// }

void tcp(Server serv) {
	int opt = TRUE;  
    int addrlen , client_socket[30] , 
          max_clients = 30 , i;  
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
    if( (serv.sfd = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
		throw SocketCreaFailed();
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(serv.sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
		throw SetSocketOptFailed();
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(serv.getPort());  
         
    //bind the socket to localhost port 8888 
    if (bind(serv.sfd, (struct sockaddr *)&address, sizeof(address))<0)  
		throw SocketBindFailed();

    printf("Listener on port %d \n", serv.getPort());  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(serv.sfd, 3) < 0)  
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
        FD_SET(serv.sfd, &readfds);  
        max_sd = serv.sfd;  
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
        if ((activity < 0) && (errno!=EINTR))  
			throw SelectFailed();
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(serv.sfd, &readfds))  
        { 
			// Client	*tmp = new Client;
            // if ((new_socket = accept(serv.sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
			// 	throw AcceptFailed();
			// else
			// 	tmp->setFd(new_socket);
			// serv.user.push_back(tmp);
            serv.addClient();
			// std::cout << serv.user.size() << std::endl;
            //inform user of socket number - used in send and receive commands 
            // printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
            //       (address.sin_port));  
           
            //send new connection greeting message 
            // if( (int)send(new_socket, message, strlen(message), 0) != (int)strlen(message) )  
            // {  
            //     perror("send");  
            // }  
                 
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = serv.fresh_fd;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
				
                // if ((valread = read( sd , buffer, 1024)) == 0) 
				if ((valread = recv(sd, buffer, 1024, 0)) == 0)
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';
					// for (size_t i = 0; i < serv.user.size(); i++)
					// 	send(serv.user[i]->getFd(), buffer, strlen(buffer), 0);
					// parse parse(buffer);
					std::cout << buffer << std::endl;
                    send(sd , buffer , strlen(buffer) , 0 );  
                }  
            }  
        }  
    }  
         
    return ;
}

// void	Server_loop(Server serv, int sockfd) {
// 	char buff[MAX];
// 	int n;
// 	(void)serv;
// 	std::cout << sockfd << std::endl;
// 	for (;;) {
// 		bzero(buff, MAX);
// 		n = recv(sockfd, buff, 80, 0);
// 		send(sockfd, "I got it", strlen("I got it"), 0);
// 	}
// }