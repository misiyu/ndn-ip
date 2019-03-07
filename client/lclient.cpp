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
#include <errno.h>
#include <pthread.h>
#include <cstdlib>

#define BUFF_SIZE 8002

using namespace std;

int if_open_player = 0 ;
string proxy_ip  ;

ssize_t readn(int fd, char *buf, int n){
    size_t nleft = n; //还需要读取的字节数
    char *bufptr = buf; //指向read函数当前存放数据的位置
    ssize_t  nread;
    while(nleft > 0){
        if((nread = read(fd, bufptr, n)) < 0){
            if(errno == EINTR){ //遇到中断
                continue;
            }
            else            // 其他错误
                return -1;
        }
        else if(nread == 0){ // 遇到EOF
            break;
        }
 
        nleft -= nread;
        bufptr += nread;
    }
    return (n - nleft);
}

void * open_player(void * val){
	char * file_path = (char*)val ;
	string appname = "smplayer";
	string cmd = appname+" "+file_path ;
	system(cmd.data());
	return NULL ;
}


int main(int argc , char ** argv)
{
	int sockfd ;
	struct sockaddr_in server_addr ;
	int port = 8000 ;

	bzero(&server_addr , sizeof(server_addr));
	server_addr.sin_family = AF_INET ;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(port);

	sockfd = socket(AF_INET , SOCK_STREAM , 0 );
	connect(sockfd , (struct sockaddr *)&server_addr , sizeof(server_addr));

	string interest_name = "/localhost/nfd/testApp/003.mkv";
	if(argc < 2) {
		cout << "Usage : ./client [ndn source name]" << endl ;
		cout << "example : ./lcndn /localhost/nfd/testApp/003.mkv" << endl ;
		exit(1);
	}else{
		interest_name = argv[1];
	}
	write(sockfd,interest_name.data(),interest_name.length());
	FILE * file = fopen("output","wb");
	char recv_buff[BUFF_SIZE];
	int recv_count = 0 ;
	int recv_num = 0;


	while((recv_num = readn(sockfd,recv_buff,BUFF_SIZE))){
		write(sockfd,"o",1);
		if(recv_num == -1) continue ;
		if(recv_num != 8002) break ;
		int16_t valid_num = 0 ;
		memcpy(&valid_num,recv_buff+BUFF_SIZE-2,sizeof(int16_t));
		recv_count ++ ;
		cout << recv_count << " : valid_num = " << valid_num << "  recv_num = "<<recv_num << endl ;
		if(valid_num > BUFF_SIZE-2) valid_num = BUFF_SIZE-2 ;
		fwrite(recv_buff,sizeof(char),valid_num,file);
		if(recv_count % 2000 == 0) break ;

	}
	fclose(file);
	pthread_t tid ;
	char file_path[]="output" ;
	pthread_create(&tid,NULL,open_player,file_path);

	while(1)
	{
		file = fopen("output","ab+");
		fseek(file,0,SEEK_END);

		while((recv_num = readn(sockfd,recv_buff,BUFF_SIZE))){
			write(sockfd,"o",1);

			if(recv_num == -1) continue ;
			if(recv_num != 8002) break ;
			int16_t valid_num = 0 ;
			memcpy(&valid_num,recv_buff+BUFF_SIZE-2,sizeof(int16_t));
			recv_count ++ ;
			cout << recv_count << " : valid_num = " << valid_num << "  recv_num = "<<recv_num << endl ;
			if(valid_num > BUFF_SIZE-2) valid_num = BUFF_SIZE-2 ;
			fwrite(recv_buff,sizeof(char),valid_num,file);
			if(recv_count % 2000 == 0) break ;
		}
		if(recv_num == 0) break ;
		fclose(file);
		cout << "write buff" << endl ;
	}

	close(sockfd);
	fclose(file);
	pthread_join(tid,NULL);

	return 0;
}
