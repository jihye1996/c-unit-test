#ifndef UserInfo_H //�ߺ�����
#define UserInfo_H

#include <string>

struct UserInfo {
	/*
	id: ���̵�
	passwd: ��й�ȣ
	auth: ���� R W RW
	identity: �ֹι�ȣ
	tried: �α��� ���� Ƚ��
	valid: �޸鿩��

	������ ���� ���� -> Server.h ���� validUser�� ���ε� ����,
									   waitUser�� ���� ��� ���� ����
	*/
	std::string id;
	std::string passwd;
	std::string auth;
	std::string identity;
	unsigned int tried = 0;
	bool active = true;
};
#endif