#include <iostream>
#include "ip2ndn_proxy.h"
using namespace std ;

IP2NDN_proxy::IP2NDN_proxy(){
	int server_sockfd ;
	socklen_t client_sock_len ;
	struct sockaddr_in cli_addr , serv_addr ;
	int port ;

	port = SERV_TCP_PORT ;

	server_sockfd = socket(AF_INET, SOCK_STREAM , 0);
	bzero((char*)&serv_addr , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET ;
	//serv_addr.sin_addr.s_addr = inet_addr("192.168.7.21");
	serv_addr.sin_addr.s_addr = inet_addr(BIND_IP);
	serv_addr.sin_port = htons(port);

	for (int i = 0; i < 10; i++) {
		
		int ret = bind(server_sockfd, (struct sockaddr *)&serv_addr , sizeof(serv_addr));
	}

	listen(server_sockfd , 10) ;

	while(1){
		client_sock_len = sizeof(cli_addr);		
		int new_sockfd = accept(server_sockfd,(struct sockaddr *)&cli_addr , &client_sock_len);
		cout << " new socket accept " << new_sockfd <<  endl ;
		Connection * con = new Connection(new_sockfd);
		con->start();
		// this place do not release the memory yet !!!
	}
}



