#ifndef AdminMode_H //�ߺ�����
#define AdminMode_H

#include <iostream>
#include <conio.h>
#include "sha256.h"
#include "ServerInfo.h"
#include "UserInfo.h"
#include "AdminInfo.h"

using namespace std;

class AdminMode {
private:
	AdminInfo* admin;
	ServerInfo* sInfo;
	vector<UserInfo>* vup;//valid user vector pointer
	vector<UserInfo>* wup;//wait user vector pointer

public:
	//constructor
	AdminMode();
	//constructor, admin, server, validuser,waituser
	AdminMode(AdminInfo* a, ServerInfo* s, vector<UserInfo>* validU, vector<UserInfo>* waitU);

	//getter and setter
	void UpdateServerInfo() { sInfo->IncAddDisk(); }

	/*
	����� ��� ���� �� �α��� ���� �� ��� ����
	initAdminMode: ������ ��� -> ������ ���� ����
	ChangeCode: ������ ��� ���� �ڵ� ����
	InputCode(): ������ �ڵ� �Է� -> '*' ����
	ShowUserInfo(): ���ε� ���� ���� id �� ����ϱ�
	AddDisk(): ��ũ �뷮 �߰��ϱ�
	CheckChangedDisk(): ��ũ �߰� Ƚ�� Ȯ��
	showWaitUser(): ��� ���� ���� ���� id�� ����ϱ�
	ApproveUser(): ��� ���� ��� ���� ���� + ��� ���� ���� ����
	PrintUsers(): ���� �ڷᱸ�� ����ϴ� �Լ�
	UploadUpdate: �뷮�� ������ ���� �߰�, �ӽ�
	DeleteUpdate: ������ ������ ������ ���� ����, �ӽ�
	FileDownload: ���� �ٿ�ε�, ��ü�� ����� ����
	PrintFiles: ������ �ִ� ���� ���, �ӽ�
	showDiskInfo: ���� ���� ��ũ �뷮 ���
	*/
	void initAdminMode();

	void ChangeCode(); //1�� �ڵ� ����
	string InputCode();
	void ShowUserInfo(); //2��. ���� ���� ����
	void AddDisk(); //3��. ��ũ
	bool CheckChangedDisk();
	void showWaitUser(); //4��. ��� ���� ����
	void ApproveUser();
	void PrintUsers(UserInfo user);

	void UploadUpdate(); //5. ���� ���ε�
	void DeleteUpdate();//6��. ���� ����
	void FileDownload(); //7��. ���� �ٿ�ε�
	void PrintFiles();
	void showDiskInfo();

};
#endif

