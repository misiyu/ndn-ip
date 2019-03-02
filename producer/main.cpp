#include <iostream>
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <sys/stat.h>

#include <iostream>

#define BUFF_SIZE 8

using namespace ndn;
using namespace std;

typedef struct Struct_WGH1{
	std::string file_name ;
	int segment_num ;
	Data * datas ;
}FILE_data_list_t ;

class FileTable{
	private :
		static const int Table_Size = 20 ;
		short int mark[Table_Size];
		FILE_data_list_t filetable[Table_Size];

	public :
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
		Data get_data(int file_no , int segment_no){
			return this->filetable[file_no].datas[segment_no];
		}
		int load_file(int segment_num , std::string file_name , std::string data_prefix_name , KeyChain &m_keyChain , int file_no){
			if(this->mark[file_no] == 1) return 0 ;
			this->mark[file_no] = 1;
			this->filetable[file_no].file_name = file_name ;
			this->filetable[file_no].segment_num = segment_num ;
			cout << "segment_num = "<<segment_num << endl ;
			this->filetable[file_no].datas = (Data*)malloc(sizeof(Data)*segment_num);
			cout << "50 =============== " << endl ;
			FILE * file = fopen(file_name.data(),"rb");
			int read_size = 0;
			int segment_no = 0;
			char buff_read[BUFF_SIZE];
			while(( read_size = fread(buff_read,sizeof(char),BUFF_SIZE,file) ) > 0){

				char buff[BUFF_SIZE];
				memcpy(buff,buff_read,BUFF_SIZE);
				cout << buff << endl ;
				cout << "65 =============== " << endl ;
				std::stringstream ss ;
				ss <<data_prefix_name<< "/"<<file_no<<"-"<< segment_no  ;
				cout << "62 =============== " << ss.str() <<  endl ;
				//this->filetable[file_no].datas[segment_no].setName("hello");
				cout << "65 =============== " << endl ;
				this->filetable[file_no].datas[segment_no].setContent(reinterpret_cast<const uint8_t*>(buff),BUFF_SIZE);
				cout << "65 =============== " << endl ;
				segment_no ++ ;
			}	
			fclose(file);
			for (int i = 0; i < segment_num; i++) {
				string str =(char*)this->filetable[file_no].datas[i].getContent().value() ; 
				str[BUFF_SIZE-1] = '\0';
				cout << str << endl ;
			}
		}



};
int main()
{
	FileTable filetable ;
	KeyChain m_keyChain ;
	filetable.load_file(9, "002.txt" , "/example/data" , m_keyChain , 0);
	return 0;
}
