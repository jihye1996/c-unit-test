#ifndef UserMode_H //�ߺ�����
#define UserMode_H

#include "UserInfo.h"
#include "ServerInfo.h"\

class UserMode {
private:
	UserInfo* currentUser;
	ServerInfo* serverInfo;

public:
	//constructor
	UserMode();
	UserMode(UserInfo* u, ServerInfo* s);//user, server

	//getter and setter
	ServerInfo* getServerInfo() const { return serverInfo; }
	UserInfo* getCurrentUser() const { return currentUser; }
	string getAuth()const { return currentUser->auth; }

	void setServerInfo(ServerInfo *server) { serverInfo = server; }
	void setCurrentUser(UserInfo *user) { currentUser = user; }

	/*
	����� ��� ���� �� �α��� ���� �� ��� ����
	initUserMode: ����� ���� ����
	showServerInfo: ���� ���� �����ֱ�
	FileUpload:���� ���ε�, ����� ������ R�� ��� ��� �Ұ���
				��ü�� ����� ����
	FileRemove: ���� �����, ����� ������ R�� ��� ��� �Ұ���
				��ü�� ����� ����
	FileDownload: ���� �ٿ�ε�, ����� ������ R�� ��� ��� �Ұ���
				��ü�� ����� ����
	CheckPermission: ���� üũ true�̸� ��� ����, false�̸� ���Ұ���
	PrintFiles: ������ �ִ� ���� ���, �ӽ�
	UploadUpdate: �뷮�� ������ ���� �߰�, �ӽ�
	DeleteUpdate: ������ ������ ������ ���� ����, �ӽ�
	*/
	void initUserMode();
	void showServerInfo();
	void FileUpload();
	void FileRemove();
	void FileDownload();
	bool CheckPermission();
	void PrintFiles();
	void UploadUpdate();
	void DeleteUpdate();
};
#endif

