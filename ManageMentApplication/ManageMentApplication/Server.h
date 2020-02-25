#ifndef Server_H //중복방지
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
#include "sha256.h" //암호화
#include "UserMode.h"

using namespace std;

class Server {
private:
	/*
	validUsers: 승인 유저
	waitUsers: 대기 중인 유저
	currentUser: 현재 접속 중인 유저(로그인 한 유저)
	userMode: 사용자 행위 클래스
	serverInfo: 서버 용량 생성(default 총 용량:100, 사용중: 0, 사용가능100)
	admininfo: 서버 디스크 정보 자료구조
	adminMode: 관리자 행위 클래스
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
	메뉴 선택
	initConsole: 시작 메뉴 + 사용자 입력값 받기(1~3)
	LoginUser: 로그인시도
	registerUser: 회원가입 시도
	*/
	void initConsole();
	void LoginUser();
	void LoginAdmin();
	void registerUser();


	/*
	mode 1: 사용자 모드 진입을 위한 함수들 -> LoginUser 함수부터 시작
	CheckUser: 사용자 입력 id, passwd, auth 일치 여부 체크
	PlusUserTried: 사용자 로그인 횟수 +1
	*/
	bool CheckUser(string id, string password, string auth);
	void PlusUserTried(UserInfo* user);


	/*
	mode 2: 관리자 모드 진입을 위한 함수들 -> LoginAdmin 함수부터 시작
	CheckCode: 관리자 코드 비교
	InputToSecret: 사용자 입력 값 -> "*"
	*/
	bool CheckCode(string code);
	string InputToSecret();


	/*
	mode 3: 회원가입을 위한 함수들 -> registerUser 함수부터 시작
	InputId: 아이디 입력받기
	IsNotValid_ID: 아이디 중복 체크
	isNotWait_ID: 대기 중 유저 아이디와 중복 체크
	isVaild_Passwd: 비밀번호 유효성 체크
	isNotContained_identity: 비밀번호에 주민번호 포함되어있는지 확인
	InputAuth: 권한 입력받기
	InputIdentity: 주민번호 입력받기
	isVaild_Identity: 주민번호 형식 체크하기
	*/
	string InputId(); //아이디
	bool isNotVaild_ID(string id);
	bool isNotWait_ID(string id);
	bool isVaild_Passwd(string password);
	bool isNotContain_iden(string password, string identity);
	string InputAuth(); //권한
	string InputIdentity(); //주민번호
	bool isVaild_Identity(string identity);

};

#endif