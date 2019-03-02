#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

int main()
{
	int sockfd ;
	struct sockaddr_in server_addr ;
	//char * server_ip = "localhost" ;
	struct hostent * host_ptr ;
	int port = 8000 ;
	int buff_size ;

	bzero(&server_addr , sizeof(server_addr));
	server_addr.sin_family = AF_INET ;
	//server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_addr.s_addr = inet_addr("192.168.7.21");
	server_addr.sin_port = htons(port);

	// open a TCP socket 
	sockfd = socket(AF_INET , SOCK_STREAM , 0 );
	//connect to server 
	connect(sockfd , (struct sockaddr *)&server_addr , sizeof(server_addr));
	//send(sockfd,"hello world",sizeof("hello world"),0);

	write(sockfd,"/example/testApp/003.mp4",sizeof("/example/testApp/003.mp4"));

	close(sockfd);

	return 0;
}
