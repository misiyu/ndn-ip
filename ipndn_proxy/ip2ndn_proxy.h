#ifndef WGH_IP2NDN_PROXY_H
#define WGH_IP2NDN_PROXY_H

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#include "connection.h"

#define SERV_TCP_PORT 8000 /* server's port number */
#define BIND_IP "127.0.0.1"

class IP2NDN_proxy{
	
	private :
				
	public :
		IP2NDN_proxy();
	
};

#endif 
