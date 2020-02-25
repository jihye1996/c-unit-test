#ifndef Server_H //�ߺ�����
#define Server_H

#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <conio.h>
#include <stdlib.h>
#include "UserInfo.h"
#include "ServerInfo.h"
#include "AdminInfo.h"
#include "AdminMode.h"
#include "sha256.h" //��ȣȭ
#include "UserMode.h"

using namespace std;

class Server {
private:
	/*
	validUsers: ���� ����
	waitUsers: ��� ���� ����
	currentUser: ���� ���� ���� ����(�α��� �� ����)
	userMode: ����� ���� Ŭ����
	serverInfo: ���� �뷮 ����(default �� �뷮:100, �����: 0, ��밡��100)
	admininfo: ���� ��ũ ���� �ڷᱸ��
	adminMode: ������ ���� Ŭ����
	*/
	vector<UserInfo> validUsers;
	vector<UserInfo> waitUsers;
	UserInfo currentUser;

	ServerInfo serverInfo;
	AdminInfo admininfo;

public:

	//constructor
	Server();
	Server(ServerInfo s, AdminInfo a);//serverinfo, admininfo

	//getter and setter
	ServerInfo getServerInfo() { return serverInfo; }
	ServerInfo *getServerInfoP() { return &serverInfo; }
	UserInfo getCurrentUser() { return currentUser; }
	UserInfo *getcurrentUserP() { return &currentUser; }

	AdminInfo getAdminInfo() { return admininfo; }
	AdminInfo *getAdminInfoP() { return &admininfo; }

	//for test
	void setServerInfo(ServerInfo server) { serverInfo = server; }
	void setCurrentUser(UserInfo user) { currentUser = user; }
	void addValidUser(UserInfo user) { validUsers.push_back(user); }
	void addTestUser(UserInfo user) { waitUsers.push_back(user); }

	/*
	�޴� ����
	initConsole: ���� �޴� + ����� �Է°� �ޱ�(1~3)
	LoginUser: �α��νõ�
	registerUser: ȸ������ �õ�
	*/
	void initConsole();
	void LoginUser();
	void LoginAdmin();
	void registerUser();


	/*
	mode 1: ����� ��� ������ ���� �Լ��� -> LoginUser �Լ����� ����
	CheckUser: ����� �Է� id, passwd, auth ��ġ ���� üũ
	PlusUserTried: ����� �α��� Ƚ�� +1
	*/
	bool CheckUser(string id, string password, string auth);
	void PlusUserTried(UserInfo* user);


	/*
	mode 2: ������ ��� ������ ���� �Լ��� -> LoginAdmin �Լ����� ����
	CheckCode: ������ �ڵ� ��
	InputToSecret: ����� �Է� �� -> "*"
	*/
	bool CheckCode(string code);
	string InputToSecret();


	/*
	mode 3: ȸ�������� ���� �Լ��� -> registerUser �Լ����� ����
	InputId: ���̵� �Է¹ޱ�
	IsNotValid_ID: ���̵� �ߺ� üũ
	isNotWait_ID: ��� �� ���� ���̵�� �ߺ� üũ
	isVaild_Passwd: ��й�ȣ ��ȿ�� üũ
	isNotContained_identity: ��й�ȣ�� �ֹι�ȣ ���ԵǾ��ִ��� Ȯ��
	InputAuth: ���� �Է¹ޱ�
	InputIdentity: �ֹι�ȣ �Է¹ޱ�
	isVaild_Identity: �ֹι�ȣ ���� üũ�ϱ�
	*/
	string InputId(); //���̵�
	bool isNotVaild_ID(string id);
	bool isNotWait_ID(string id);
	bool isVaild_Passwd(string password);
	bool isNotContain_iden(string password, string identity);
	string InputAuth(); //����
	string InputIdentity(); //�ֹι�ȣ
	bool isVaild_Identity(string identity);

};

#endif