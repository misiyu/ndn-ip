#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <sys/stat.h>
#include <fstream>

#include <iostream>

#define BUFF_SIZE 8002

using namespace ndn;
using namespace std;

typedef struct Struct_WGH1{
	std::string file_name ;
	int segment_num ;
	char ** datas ;
}FILE_data_list_t ;

class FileTable{
	private :
		static const int Table_Size = 20 ;
		short int mark[Table_Size];
		FILE_data_list_t filetable[Table_Size];

	public :
		~FileTable(){
			for (int i = 0; i < this->filetable[0].segment_num ; i++) {
				free(this->filetable[0].datas[i]);
			}
			free(this->filetable[0].datas);
		}
		FileTable(){
			for (int i = 0; i < Table_Size; i++) {
				this->mark[i] = 0 ;
			}
		}

		int is_need_load(std::string filename ){
			for (int i = 0; i < Table_Size; i++) {
				if(this->filetable[i].file_name == filename) return i ;
			}
			for (int i = 0; i < Table_Size; i++) {
				if(this->mark[i] == 0){
					return i ;
				}	
			}
			return -2 ;
		}
		char * get_data(int file_no , int segment_no){
			return ( this->filetable[file_no].datas[segment_no] );
		}
		int load_file(int segment_num , std::string file_name , std::string data_prefix_name , KeyChain &m_keyChain , int file_no){
			if(this->mark[file_no] == 1) return 0 ;
			this->mark[file_no] = 1;
			this->filetable[file_no].file_name = file_name ;
			this->filetable[file_no].segment_num = segment_num ;
			this->filetable[file_no].datas = (char**)malloc(sizeof(char*)*segment_num);
			char buff_read[BUFF_SIZE];
			FILE * file = fopen(file_name.data(),"rb");
			int16_t read_size = 0;
			int i = 0;
			while(( read_size = fread(buff_read,sizeof(char),BUFF_SIZE-2,file) ) > 0){
				//buff_read[BUFF_SIZE-1] = read_size ;
				memcpy(buff_read+BUFF_SIZE-2,&read_size,sizeof(int16_t));
				int16_t tmp ;
				//memcpy(&tmp , buff_read+BUFF_SIZE-2,sizeof(int16_t));
				//cout << "read_size = " << tmp << endl ;
				this->filetable[file_no].datas[i]=(char*)malloc(sizeof(char)*BUFF_SIZE);
				memcpy(this->filetable[file_no].datas[i],buff_read,BUFF_SIZE);
				std::stringstream ss ;
				i++ ;
			}	
			fclose(file);
		}
};

class Producer : noncopyable
{
	public:
		Producer(){
			this->bind_mana_prefix = "/localhost/nfd/testApp";
			this->bind_data_prefix = "/localhost/nfd/data";
			this->file_num = 0 ;
			//int segment_num = 0;
			//this->get_file_size("003.mp4",segment_num);
			//cout << "segment_num = " << segment_num << endl ;
			//this->m_filetable.load_file(segment_num , "003.mp4" , this->bind_data_prefix.data(), this->m_keyChain , 0);
			this->load_file();
		}

		void load_file(){
			cout << "load file " << endl ;
			string dirname = "./source" ;
			std::ifstream infile("./source.conf", ios::binary);
			if(!infile.is_open()){
				cout << "can not find ./source.conf " << endl;
				exit(1);
			}
			string line ;
			while(getline(infile,line))
			{
				cout << line << endl ;
				cout << "load file " << line << endl ;
				int segment_num = 0;
				this->get_file_size(line.data(),segment_num);
				cout << "segment_num = " << segment_num << endl ;
				this->m_filetable.load_file(segment_num , line.data() , this->bind_data_prefix.data(), this->m_keyChain , this->file_num);
				this->file_num ++ ;
			}

		}

		void run()
		{

			m_face.setInterestFilter(this->bind_mana_prefix.data(),
					bind(&Producer::onInterest, this, _1, _2),
					RegisterPrefixSuccessCallback(),
					bind(&Producer::onRegisterFailed, this, _1, _2));
			
			m_face.setInterestFilter(this->bind_data_prefix.data(),
					bind(&Producer::onInterest_data, this, _1, _2),
					RegisterPrefixSuccessCallback(),
					bind(&Producer::onRegisterFailed, this, _1, _2));
			this->m_filetable.get_data(0,0);
			cout << "producer start listening" << endl ;

			m_face.processEvents();
		}

	private:
		void onInterest(const InterestFilter& filter, const Interest& interest)
		{
			std::cout << "<< I: " << interest << std::endl;
			std::cout << interest.getName() << std::endl ;
			// Create new name, based on Interest's name
			std::string interst_name = interest.getName().toUri();
			int tmp  = interst_name.find_last_of('/');
			string file_name = interst_name.substr( tmp+1 , interst_name.length()-tmp);
			file_name = "./source/"+file_name ;
			std::cout << "interest file name=" <<  file_name << "$" <<std::endl ;
			int segment_num = 0;
			unsigned long filesize = get_file_size(file_name.data(),segment_num);
			std::cout << "interest file name size=" << get_file_size(file_name.data(),segment_num) <<"$" << std::endl ;
			std::cout << "interest file segment_num =" << segment_num <<"$" << std::endl ;

			int file_no = 0;
			file_no =  this->m_filetable.is_need_load(file_name);
			if(file_no == -2 ){
				std::cout << "table full !!!" << std::endl ;
			} 
			std::stringstream ss ;
			ss << file_no << "-" << segment_num ;
			Data data(interest.getName());
			data.setContent(reinterpret_cast<const uint8_t*>(ss.str().data()), sizeof(ss.str().length()));

			m_keyChain.sign(data);

			m_face.put(data);
			this->m_filetable.load_file(segment_num , file_name , this->bind_data_prefix.data(), this->m_keyChain , file_no);
		}

		void onInterest_data(const InterestFilter& filter, const Interest& interest)
		{
			std::string interst_name = interest.getName().toUri();
			cout << "get data " << interst_name << endl ;
			int tmp1 = interst_name.find_last_of('/');
			int tmp2 = interst_name.find('-',tmp1);
			int file_index ;
			int segment_no ;
			std::stringstream ss ;
			ss << interst_name.substr(tmp1+1,tmp2-tmp1-1);
			ss >> file_index ;
			ss.str("");
			ss.clear();
			ss << interst_name.substr(tmp2+1,interst_name.length()-tmp2-1);
			ss >> segment_no ;
			cout << file_index << " segment_no = " << segment_no << endl ;

			//string content = this->m_filetable.get_data(file_index,segment_no);
			char content[BUFF_SIZE] ;
			memcpy(content,this->m_filetable.get_data(file_index,segment_no),BUFF_SIZE);
			Data data; 
			data.setName(interst_name);
			data.setContent(reinterpret_cast<const uint8_t*>(content),BUFF_SIZE);

			int16_t tmp ;
			memcpy(&tmp , content+BUFF_SIZE-2,sizeof(int16_t));
			cout << "valid_num = "<<tmp << endl ;
			m_keyChain.sign(data);
			m_face.put(data);
			cout << "send data's name : " << data.getName() <<endl ;

		}


		void onRegisterFailed(const Name& prefix, const std::string& reason)
		{
			std::cerr << "ERROR: Failed to register prefix \""
				<< prefix << "\" in local hub's daemon (" << reason << ")"
				<< std::endl;
			m_face.shutdown();
		}

		unsigned long get_file_size(const char *path , int & segment_num)
		{
			unsigned long filesize = -1;	
			struct stat statbuff;
			if(stat(path, &statbuff) < 0){
				return filesize;
			}else{
				filesize = statbuff.st_size;
			}
			segment_num = filesize/(BUFF_SIZE-2) ;
			if(filesize % (BUFF_SIZE-2) != 0) segment_num ++ ;
			return filesize;
		}

	private:
		Face m_face;
		KeyChain m_keyChain;
		FileTable m_filetable ;
		string bind_mana_prefix ;
		string bind_data_prefix ;
		int file_num ;
};

int main()
{
	Producer producer;
	try {
		producer.run();
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
