#include "ServerInfo.h"

ServerInfo::ServerInfo() {

}

ServerInfo::ServerInfo(unsigned int total, unsigned int use, unsigned int avail) {
	total_disk = total;
	use_disk = use;
	avail_disk = avail;
}

ServerInfo::ServerInfo(unsigned int total, unsigned int use, unsigned int avail, vector<std::string> file) {
	total_disk = total;
	use_disk = use;
	avail_disk = avail;
	files = file;
}

ServerInfo::~ServerInfo() {

}

//getter
unsigned int ServerInfo::GetTotal() { return total_disk; }
unsigned int ServerInfo::GetUsed() { return use_disk; }
unsigned int ServerInfo::GetAvail() { return avail_disk; }
unsigned int ServerInfo::GetAddDisk() { return addDisk; }
vector<std::string> ServerInfo::GetAllFiles() { return files; }

//setter
void ServerInfo::SetTotal(unsigned int total) { total_disk = total; }
void ServerInfo::SetUsed(unsigned int used) { use_disk = used; }
void ServerInfo::SetAvail(unsigned int avail) { avail_disk = avail; }
void ServerInfo::SetAddDisk(unsigned int count) { addDisk = count; }
void ServerInfo::IncAddDisk() { addDisk++; }
void ServerInfo::AddFile(string file) { files.push_back(file); }
void ServerInfo::DeleteFile() { files.pop_back(); }