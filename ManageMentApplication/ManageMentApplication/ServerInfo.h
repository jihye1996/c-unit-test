#ifndef ServerInfo_H //중복방지
#define ServerInfo_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class ServerInfo {
private:
	/*
	total_disk: 서버 전체 용량
	use_disk: 현재 사용 용량
	avail_disk: 사용 가능 용량
	files: 파일 리스트
	*/
	unsigned int total_disk = 100;
	unsigned int use_disk = 0;
	unsigned int avail_disk = 100;
	vector<std::string> files;
	unsigned int addDisk = 0;

public:
	//constructor
	ServerInfo();
	ServerInfo(unsigned int total, unsigned int use, unsigned int avail);
	ServerInfo(unsigned int total, unsigned int use, unsigned int avail, vector<std::string> file);
	~ServerInfo();

	//getter
	unsigned int GetTotal();
	unsigned int GetUsed();
	unsigned int GetAvail();
	unsigned int GetAddDisk();
	vector<std::string> GetAllFiles();

	//setter
	void SetTotal(unsigned int total);
	void SetUsed(unsigned int used);
	void SetAvail(unsigned int avail);
	void SetAddDisk(unsigned int count);
	void IncAddDisk();

	/*
	AddFile: 파일 추가, 임시
	DeleteFile: 파일 삭제, 임시
	*/
	void AddFile(string file);
	void DeleteFile();
};

#endif //ServerInfo_H