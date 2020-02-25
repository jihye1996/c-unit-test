#ifndef UserInfo_H //중복방지
#define UserInfo_H

#include <string>

struct UserInfo {
	/*
	id: 아이디
	passwd: 비밀번호
	auth: 권한 R W RW
	identity: 주민번호
	tried: 로그인 도전 횟수
	valid: 휴면여부

	관리자 승인 여부 -> Server.h 에서 validUser는 승인된 유저,
									   waitUser는 승인 대기 중인 유저
	*/
	std::string id;
	std::string passwd;
	std::string auth;
	std::string identity;
	unsigned int tried = 0;
	bool active = true;
};
#endif