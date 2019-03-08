#include "connection.h"

Connection::Connection(int sockfd){
	this->sockfd = sockfd ;
	this->get_segment_count = 0;
}

void Connection::start(){
	int ret = pthread_create(&(this->tid) , NULL , run , (void*)this);
}
ssize_t writen(int fd, const char *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0){
        if ( (nwritten = write(fd, ptr, nleft)) <= 0){
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; // 再次执行write()
            else 
                return -1; // error
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}
void Connection::onData(const Interest& interest , const Data& data){
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
	//cout << "file_no=" << file_no << endl ;
	//cout << "segment_num=" << segment_num << endl ;
	this->segment_num = segment_num ;
	this->file_no = file_no ;
	//cout << (data.getContent().value()) << endl ;

	ss.str("");
	ss.clear();
	ss << this->interest_data_prefix <<"/" <<file_no <<"-"<<this->get_segment_count ;
	string data_segment_name = ss.str();
	Interest interest_d(Name(data_segment_name.data()));
	interest_d.setInterestLifetime(2_s);
	//interest.setMustBeFresh(true);
	this->m_face.expressInterest(interest_d,
			bind(&Connection::onData1,this,_1,_2),
			bind(&Connection::onNack,this,_1,_2),
			bind(&Connection::onTimeout1,this,_1));
	cout << "expressInterest : " << interest_d.getName() << endl ;
}
void Connection::onData1(const Interest& interest , const Data& data){

	char send_buff[BUFF_SIZE];
	memcpy(send_buff,(char*)(data.getContent().value()),BUFF_SIZE);
	int16_t tmp = 0 ;
	memcpy(&tmp, send_buff+BUFF_SIZE-2 , sizeof(int16_t));
	int send_num = 0;
	//send(this->sockfd , send_buff, BUFF_SIZE,0);
	send_num = writen(this->sockfd , send_buff , BUFF_SIZE);
	char buff_ack[1];
	int recv_len = read(this->sockfd , buff_ack,1 );
	if(recv_len <= 0) pthread_exit(NULL);

	this->get_segment_count ++ ;
	//if(this->get_segment_count == 100) pthread_exit(NULL);
	//cout << this->get_segment_count << ":"<<this->segment_num << endl ;
	cout << this->get_segment_count << ":"<<this->segment_num << ":"<<send_num <<":" << tmp <<  endl;
	//sleep(1);

	if(this->get_segment_count < this->segment_num){
		//cout << "more data " << endl ;
		stringstream ss ;
		ss << this->interest_data_prefix << "/" << this->file_no << "-" << this->get_segment_count ;
		string data_segment_name = ss.str();
		Interest interest_d(Name(data_segment_name.data()));
		interest_d.setInterestLifetime(2_s);
		this->m_face.expressInterest(interest_d,
				bind(&Connection::onData1,this,_1,_2),
				bind(&Connection::onNack,this,_1,_2),
				bind(&Connection::onTimeout1,this,_1));
		cout << "expressInterest : " << interest_d.getName() << endl ;
	}else{
		close(this->sockfd);
	}
}
void Connection::onNack(const Interest& interest, const lp::Nack& nack){

}
void Connection::onTimeout(const Interest& interest){

}
void Connection::onTimeout1(const Interest& interest){
	this->m_face.expressInterest(interest,
			bind(&Connection::onData1,this,_1,_2),
			bind(&Connection::onNack,this,_1,_2),
			bind(&Connection::onTimeout1,this,_1));
}

void Connection::send2client(string buff){
	
}
