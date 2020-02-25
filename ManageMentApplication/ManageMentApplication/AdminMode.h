#ifndef AdminMode_H //중복방지
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
	사용자 모드 진입 후 로그인 성공 시 사용 가능
	initAdminMode: 관리자 모드 -> 관리자 행위 선택
	ChangeCode: 관리자 모드 접속 코드 수정
	InputCode(): 관리자 코드 입력 -> '*' 변경
	ShowUserInfo(): 승인된 유저 정보 id 만 출력하기
	AddDisk(): 디스크 용량 추가하기
	CheckChangedDisk(): 디스크 추가 횟수 확인
	showWaitUser(): 대기 중인 유저 정보 id만 출력하기
	ApproveUser(): 대기 중인 모든 유저 승인 + 대기 유저 벡터 비우기
	PrintUsers(): 유저 자료구조 출력하는 함수
	UploadUpdate: 용량이 있으면 파일 추가, 임시
	DeleteUpdate: 삭제할 파일이 있으면 파일 삭제, 임시
	FileDownload: 파일 다운로드, 구체적 기능은 없음
	PrintFiles: 서버에 있는 파일 출력, 임시
	showDiskInfo: 서버 보유 디스크 용량 출력
	*/
	void initAdminMode();

	void ChangeCode(); //1번 코드 수정
	string InputCode();
	void ShowUserInfo(); //2번. 승인 유저 정보
	void AddDisk(); //3번. 디스크
	bool CheckChangedDisk();
	void showWaitUser(); //4번. 대기 유저 정보
	void ApproveUser();
	void PrintUsers(UserInfo user);

	void UploadUpdate(); //5. 파일 업로드
	void DeleteUpdate();//6번. 파일 삭제
	void FileDownload(); //7번. 파일 다운로드
	void PrintFiles();
	void showDiskInfo();

};
#endif

