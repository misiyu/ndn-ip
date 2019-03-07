#ifndef WGH_CONNECTION_H
#define WGH_CONNECTION_H
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ndn-cxx/face.hpp>
#include <errno.h>

#include <iostream>

#define BUFF_SIZE 8002
using namespace ndn ;
using namespace std ;

class Connection : noncopyable{

	private :
		pthread_t tid ;
		int sockfd ;
		string interest_name ;
		string interest_data_prefix ;
		int file_no ;
		int segment_num ;
		int get_segment_count ;
		Face m_face ;
		void onData(const Interest& interest , const Data& data);
		void onData1(const Interest& interest , const Data& data);
		void onNack(const Interest& interest, const lp::Nack& nack);
		void onTimeout(const Interest& interest);
		void onTimeout1(const Interest& interest);

		void send2client(string buff);
	public :
		Connection(int sockfd);
		void start();

		static void * run(void * para){

			Connection * _this = (Connection*)para ;
			char buff[1000];
			//cout << "Connection sockfd = "<< (_this->sockfd) << endl ;
			int len = recv((_this->sockfd), buff,1000,0); 
			//cout << "" << len << endl ;
			buff[len] = '\0';
			//cout << buff << endl ;
			_this->interest_name = buff ;
			//cout << "send insterst name =" << _this->interest_name << "$" << endl ;

			int tmp1 = _this->interest_name.find_last_of('/');
			string str_tmp = _this->interest_name.substr(0,tmp1);
			tmp1 = str_tmp.find_last_of('/');
			_this->interest_data_prefix = str_tmp.substr(0,tmp1+1)+"data";

			Interest interest(Name(_this->interest_name.data()));
			interest.setInterestLifetime(2_s);
			_this->m_face.expressInterest(interest,
					bind(&Connection::onData,_this,_1,_2),
					bind(&Connection::onNack,_this,_1,_2),
					bind(&Connection::onTimeout,_this,_1));
			cout << "express interest : " << interest.getName() << endl ;

			_this->m_face.processEvents();

			close(_this->sockfd);
			return NULL;
		}

		static void * getData(void * para){
			//Connection * _this = (Connection*)para ;
		}

		
};

#endif 
