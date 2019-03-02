#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ndn-cxx/face.hpp>
#include <errno.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>

#define BUFF_SIZE 8002
using namespace ndn ;
using namespace std ;

class NDN_Client : noncopyable{
	private : 
		string interest_name ;
		string interest_data_prefix ;
		Face m_face ;
		int segment_num ;
		int get_segment_count ;
		int file_no ;
		FILE * file_out ;
		pthread_t player_pid ; 
		bool player_open ;
		//char file_path[];
	public :
		static void * open_player(void * val){
			char * file_path = (char*)val ;
			string appname = "smplayer";
			string cmd = appname+" "+file_path ;
			system(cmd.data());
			return NULL ;
		}
		NDN_Client(string interest_name){
			this->interest_name = interest_name ;
			this->segment_num = 0 ;
			this->get_segment_count = 0;
			this->file_out = fopen("output","wb");
			this->player_open = false ;

			int tmp1 = this->interest_name.find_last_of('/');
			string str_tmp = this->interest_name.substr(0,tmp1);
			tmp1 = str_tmp.find_last_of('/');
			this->interest_data_prefix = str_tmp.substr(0,tmp1+1)+"data";
			
			Interest interest(Name(this->interest_name.data()));
			interest.setInterestLifetime(2_s);
			this->m_face.expressInterest(interest,
					bind(&NDN_Client::onData,this,_1,_2),
					bind(&NDN_Client::onNack,this,_1,_2),
					bind(&NDN_Client::onTimeout,this,_1));
			cout << "express interest : " << interest.getName() << endl ;

			this->m_face.processEvents();
			pthread_join(this->player_pid,NULL);

		}
	private :
		void onData(const Interest& interest , const Data& data){
			string data_val = (char*)( data.getContent().value() ) ;
			int tmp1 = data_val.find('-');
			stringstream ss ;
			int file_no ;
			int segment_num ;
			ss << data_val.substr(0,tmp1);
			ss >> file_no ;
			ss.str("");
			ss.clear();
			ss << data_val.substr(tmp1+1,data_val.length() - tmp1-1);
			ss >> segment_num ;
			this->segment_num = segment_num ;
			this->file_no = file_no ;

			ss.str("");
			ss.clear();
			ss << this->interest_data_prefix <<"/" <<file_no <<"-"<<this->get_segment_count ;
			string data_segment_name = ss.str();
			Interest interest_d(Name(data_segment_name.data()));
			interest_d.setInterestLifetime(2_s);
			//interest.setMustBeFresh(true);
			this->m_face.expressInterest(interest_d,
					bind(&NDN_Client::onData1,this,_1,_2),
					bind(&NDN_Client::onNack,this,_1,_2),
					bind(&NDN_Client::onTimeout1,this,_1));
			cout << "expressInterest : " << interest_d.getName() << endl ;

		}
		void onData1(const Interest& interest , const Data& data){

			char send_buff[BUFF_SIZE];
			memcpy(send_buff,(char*)(data.getContent().value()),BUFF_SIZE);
			int16_t valid_num = 0 ;
			memcpy(&valid_num, send_buff+BUFF_SIZE-2 , sizeof(int16_t));
			int send_num = 0;
			send_num = fwrite(send_buff,sizeof(char),valid_num,file_out);

			this->get_segment_count ++ ;
			cout << this->get_segment_count << ":"<<this->segment_num << ":"<<send_num <<":" << valid_num <<  endl;

			if(this->get_segment_count % 2000 == 0){
				fclose(this->file_out);
				this->file_out = fopen("output","ab+");
				fseek(this->file_out,0,SEEK_END);
				if(this->player_open == false){
					char file_path[] = "output" ;
					pthread_create(&this->player_pid , NULL , open_player , file_path);
					this->player_open = true ;
				}
			}
			if(this->get_segment_count < this->segment_num){
				//cout << "more data " << endl ;
				stringstream ss ;
				ss << this->interest_data_prefix << "/" << this->file_no << "-" << this->get_segment_count ;
				string data_segment_name = ss.str();
				Interest interest_d(Name(data_segment_name.data()));
				interest_d.setInterestLifetime(2_s);
				this->m_face.expressInterest(interest_d,
						bind(&NDN_Client::onData1,this,_1,_2),
						bind(&NDN_Client::onNack,this,_1,_2),
						bind(&NDN_Client::onTimeout1,this,_1));
				cout << "expressInterest : " << interest_d.getName() << endl ;
			}else{
				fclose(this->file_out);
				if(this->player_open == false){
					char file_path[] = "output" ;
					pthread_create(&this->player_pid , NULL , open_player , file_path);
					this->player_open = true ;
				}
			}
		}
		void onNack(const Interest& interest, const lp::Nack& nack){

		}
		void onTimeout(const Interest& interest){

		}
		void onTimeout1(const Interest& interest){

			this->m_face.expressInterest(interest,
					bind(&NDN_Client::onData1,this,_1,_2),
					bind(&NDN_Client::onNack,this,_1,_2),
					bind(&NDN_Client::onTimeout1,this,_1));
		}
};

int main(int argc , char ** argv)
{
	string interest_name = "/localhost/nfd/testApp/003.mp4";
	if(argc < 2) {
		cout << "Usage : ./client [ndn source name]" << endl ;
		cout << "example : ./ndn_cli /test/aaa/testApp/003.mkv" << endl ;
		exit(1);
	}else{
		interest_name = argv[1];
	}
	NDN_Client ndn_client(interest_name.data());
	return 0;
}
