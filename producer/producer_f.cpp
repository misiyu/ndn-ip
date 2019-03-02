#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <sys/stat.h>
#include <fstream>

#include <iostream>
#include <vector>

#define BUFF_SIZE 8002

using namespace ndn;
using namespace std;

typedef struct WGH_struct2{
	string file_name ;
	int segment_num ;
	FILE * file ;
}Name_FILE_t ;

class Producer : noncopyable
{
	public:
		Producer(){
			this->bind_mana_prefix = "/localhost/nfd/testApp";
			this->bind_data_prefix = "/localhost/nfd/data";
			this->file_num = 0 ;
			this->load_file();
			this->add_prefix();
		}
		~Producer(){
			for (int i = 0; i < this->file_num; i++) {
				fclose(this->file_table[i].file);
			}
		}

		void run()
		{
			int prefix_num = this->listen_prefix.size();
			for (int i = 0; i < prefix_num; i++) {
				string prefix_tmp = this->listen_prefix[i];
				cout << "listen on : " << prefix_tmp << endl ;
				m_face.setInterestFilter(prefix_tmp.data(),
						bind(&Producer::onInterest, this, _1, _2),
						RegisterPrefixSuccessCallback(),
						bind(&Producer::onRegisterFailed, this, _1, _2));

				int tmp = prefix_tmp.find_last_of('/');
				string data_prefix = prefix_tmp.substr(0,tmp+1)+"data";

				m_face.setInterestFilter(data_prefix.data(),
						bind(&Producer::onInterest_data, this, _1, _2),
						RegisterPrefixSuccessCallback(),
						bind(&Producer::onRegisterFailed, this, _1, _2));
			}
			//m_face.setInterestFilter(this->bind_mana_prefix.data(),
					//bind(&Producer::onInterest, this, _1, _2),
					//RegisterPrefixSuccessCallback(),
					//bind(&Producer::onRegisterFailed, this, _1, _2));
			
			//m_face.setInterestFilter(this->bind_data_prefix.data(),
					//bind(&Producer::onInterest_data, this, _1, _2),
					//RegisterPrefixSuccessCallback(),
					//bind(&Producer::onRegisterFailed, this, _1, _2));
			cout << "producer start listening" << endl ;

			m_face.processEvents();
		}

	private:
		void load_file(){
			cout << "load file " << endl ;
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
				this->file_table[this->file_num].file_name = line ;
				this->file_table[this->file_num].segment_num = segment_num ;
				this->file_table[this->file_num].file = fopen(line.data(),"rb");
				if(this->file_table[this->file_num].file == NULL){
					cout << "can not open file " << line << endl ;
					exit(1);
				}
				this->file_num ++ ;
			}

		}
		void add_prefix(){

			cout << "load prefix " << endl ;
			string dirname = "./source" ;
			std::ifstream infile("./prefix.conf", ios::binary);
			if(!infile.is_open()){
				cout << "can not find ./prefix.conf " << endl;
				exit(1);
			}
			string line ;
			while(getline(infile,line))
			{
				this->listen_prefix.push_back(line);
			}
		}
		int get_file_no(string file_name){
			for (int i = 0; i < this->file_num; i++) {
				if(this->file_table[i].file_name == file_name) return i ;
			}
			return -1 ;

		}
		void onInterest(const InterestFilter& filter, const Interest& interest)
		{
			std::cout << "<< I: " << interest << std::endl;
			std::cout << interest.getName() << std::endl ;
			std::string interst_name = interest.getName().toUri();
			int tmp  = interst_name.find_last_of('/');
			string file_name = interst_name.substr( tmp+1 , interst_name.length()-tmp);
			file_name = "./source/"+file_name ;
			std::cout << "interest file name=" <<  file_name << "$" <<std::endl ;
			int segment_num = 0;
			unsigned long filesize = get_file_size(file_name.data(),segment_num);
			std::cout << "interest file name size=" << filesize <<"$" << std::endl ;
			std::cout << "interest file segment_num =" << segment_num <<"$" << std::endl ;

			int file_no = 0;
			file_no =  this->get_file_no(file_name);
			if(file_no == -1 ){
				std::cout << "do not have file " << file_name << std::endl ;
				return ;
			} 
			std::stringstream ss ;
			ss << file_no << "-" << segment_num ;
			Data data(interest.getName());
			data.setContent(reinterpret_cast<const uint8_t*>(ss.str().data()), sizeof(ss.str().length()));
			m_keyChain.sign(data);

			m_face.put(data);
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
			//memcpy(content,this->m_filetable.get_data(file_index,segment_no),BUFF_SIZE);
			fseek(this->file_table[file_index].file,(BUFF_SIZE-2)*segment_no,SEEK_SET);
			int16_t read_size = fread(content,sizeof(char),BUFF_SIZE-2,this->file_table[file_index].file);
			memcpy(content+BUFF_SIZE-2,&read_size,sizeof(int16_t));
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
		string bind_mana_prefix ;
		string bind_data_prefix ;
		vector<string> listen_prefix ;
		int file_num ;
		Name_FILE_t file_table[100];
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
