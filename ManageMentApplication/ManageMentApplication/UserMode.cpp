#include "UserMode.h"

UserMode::UserMode() {
	currentUser = NULL;
	serverInfo = NULL;
};

UserMode::UserMode(UserInfo* u, ServerInfo* s) {
	currentUser = u;
	serverInfo = s;
}

void UserMode::initUserMode() {

	while (true) {
		cout << endl;
		showServerInfo();

		cout << "\n********[사용자모드]********" << endl;
		cout << "1. 파일업로드" << endl;
		cout << "2. 파일 삭제" << endl;
		cout << "3. 파일 다운로드" << endl;
		cout << "q. 로그아웃" << endl;
		cout << "원하는 작업을 입력하세요" << endl;

		//get user input
		char input;
		cin >> input;

		switch (input)
		{
		case '1':
			FileUpload();
			break;
		case '2':
			FileRemove();
			break;
		case '3':
			FileDownload();
			break;
		case 'q':
			currentUser = {};
			return;
		case 'Q':
			currentUser = {};
			return;
		default:
			cout << "wrong input" << endl;
			break;
		}
	}

}

void UserMode::showServerInfo() {
	cout << "\n********[로그인 성공]********" << endl;
	cout << "서버 전체 용량: " << serverInfo->GetTotal() << endl;
	cout << "현재 사용 용량: " << serverInfo->GetUsed() << endl;
	cout << "사용 가능 용량: " << serverInfo->GetAvail() << endl;
}

void UserMode::FileUpload() {
	if (CheckPermission()) {
		UploadUpdate();
	}
}

void UserMode::FileRemove() {
	if (CheckPermission()) {
		DeleteUpdate();
		

	}
}

void UserMode::FileDownload() {
	if (CheckPermission()) {
		if (serverInfo->GetUsed() <= 0)
			cout << "다운로드 할 파일이 없습니다." << endl;
		else {
			cout << "파일이 다운로드 되었습니다." << endl;
		}
	}
		
}

bool UserMode::CheckPermission() {
	if (currentUser->auth == "RW" || currentUser->auth == "W")
		return true;

	cout << "읽기 권한밖에 없습니다. 권한을 확인해주세요." << endl;
	return false;
}

void UserMode::PrintFiles() {
	if (serverInfo->GetAllFiles().empty() || serverInfo->GetAllFiles().size() == 0)
		cout << "파일이 없습니다." << endl;
	else {
		vector<std::string> serverFiles = serverInfo->GetAllFiles();
		for (string file : serverFiles) {
			cout << file << endl;
		}
	}

}

void UserMode::UploadUpdate() {
	if (serverInfo->GetAvail() <= 0)
		cout << "용량이 없습니다." << endl;
	else {
		serverInfo->AddFile("upload");
		serverInfo->SetUsed(serverInfo->GetUsed() + 1);
		serverInfo->SetAvail(serverInfo->GetAvail() - 1);
		cout << "파일을 업로드 했습니다." << endl;
		PrintFiles();
	}
}

void UserMode::DeleteUpdate() {
	if (serverInfo->GetUsed() <= 0)
		cout << "삭제 할 파일이 없습니다." << endl;
	else {
		serverInfo->DeleteFile();
		serverInfo->SetUsed(serverInfo->GetUsed() - 1);
		serverInfo->SetAvail(serverInfo->GetAvail() + 1);
		cout << "파일을 삭제했습니다." << endl;
		PrintFiles();
		
	}
	
}