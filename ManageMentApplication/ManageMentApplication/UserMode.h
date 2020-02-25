#ifndef UserMode_H //중복방지
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
	사용자 모드 진입 후 로그인 성공 시 사용 가능
	initUserMode: 사용자 행위 선택
	showServerInfo: 서버 정보 보여주기
	FileUpload:파일 업로드, 사용자 권한이 R인 경우 사용 불가능
				구체적 기능은 없음
	FileRemove: 파일 지우기, 사용자 권한이 R인 경우 사용 불가능
				구체적 기능은 없음
	FileDownload: 파일 다운로드, 사용자 권한이 R인 경우 사용 불가능
				구체적 기능은 없음
	CheckPermission: 권한 체크 true이면 사용 가능, false이면 사용불가능
	PrintFiles: 서버에 있는 파일 출력, 임시
	UploadUpdate: 용량이 있으면 파일 추가, 임시
	DeleteUpdate: 삭제할 파일이 있으면 파일 삭제, 임시
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

