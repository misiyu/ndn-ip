#include <iostream>
#include <sys/stat.h>
#include <cstdio>

using namespace std;

unsigned long get_file_size(const char *path)
{
	unsigned long filesize = -1;	
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}

unsigned long get_file_size1(const char *path)
{
	unsigned long filesize = -1;
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL)
		return filesize;
	fseek(fp, 0L, SEEK_END);
	filesize = ftell(fp);
	fclose(fp);
	return filesize;

}

int main()
{

	cout << get_file_size("./003.mp4") << endl;
	cout << get_file_size1("./003.mp4") << endl;
	return 0;
}
