#include "AdminMode.h"

AdminMode::AdminMode()
{
	admin = NULL;
	sInfo = NULL;
	vup = NULL;
	wup = NULL;

}

AdminMode::AdminMode(AdminInfo* a, ServerInfo* s, vector<UserInfo>* validU, vector<UserInfo>* waitU) {
	admin = a;
	sInfo = s;
	vup = validU;
	wup = waitU;
}

void AdminMode::initAdminMode() {
	while (true) {
		cout << endl;
		cout << "********[관리자모드]********" << endl;
		cout << "1. 관리자 코드 변경" << endl;
		cout << "2. 가입한 유저 정보" << endl;
		cout << "3. 하드 용량 추가" << endl;
		cout << "4. 대기 중인 유저 정보" << endl;
		cout << "5. 파일 업로드" << endl;
		cout << "6. 파일 삭제" << endl;
		cout << "7. 파일 다운로드" << endl;
		cout << "Q. 종료하기" << endl;
		cout << "원하는 작업을 입력하세요" << endl;

		//get user input
		char input;
		cin >> input;

		switch (input)
		{
		case '1':
			ChangeCode();
			break;
		case '2':
			ShowUserInfo();
			break;
		case '3':
			AddDisk();
			break;
		case '4':
			showWaitUser();
			break;
		case '5':
			UploadUpdate();
			break;
		case '6':
			DeleteUpdate();
			break;
		case '7':
			FileDownload();
			break;
		case 'q':
			return;
		case 'Q':
			return;
		default:
			cout << "wrong input" << endl;
			break;
		}
	}


}

void AdminMode::ChangeCode() {

	cout << "관리자 확인을 위해 관리자 코드를 입력해주세요." << endl;
	string checkcode = InputCode();

	if (sha256(checkcode) == admin->code) {
		cout << "관리자 확인이 완료되었습니다. 바꾸고 싶은 관리자 코드를 입력해주세요." << endl;
		string code = InputCode();//관리자 입력값 -> '*'로 변환하기
		string codeCheck = InputCode();//관리자 입력값 -> '*'로 변환하기
		if (code == codeCheck)
			admin->code = sha256(code);
		else {

		}
	}
	else {
		cout << "코드가 일치하지 않습니다." << endl;
	}



}

string AdminMode::InputCode() {

	//사용자 입력값 -> '*'로 변환
	string returnStr;

	cout << "code: ";
	int input;
	input = _getch();

	while (input != 13) {//character 13 is enter
		returnStr.push_back((char)input);
		cout << '*';
		input = _getch();
	}
	cout << endl;
	return returnStr;
}


void AdminMode::ShowUserInfo() {
	if (vup->empty() || vup->size() == 0)
		cout << "사용자가 없습니다." << endl;
	else {
		int i = 0;
		for (UserInfo user : *vup) {
			cout << "********[승인된 사용자 " << i + 1 << "]********" << endl;
			PrintUsers(user);
			i++;
		}
	}
}

void AdminMode::AddDisk() {
	if (CheckChangedDisk()) {
		showDiskInfo();
		cout << "****주의사항: 최대 3번까지 추가 가능!!!****" << endl;
		cout << "추가할 디스크 용량을 입력하세요." << endl;

		unsigned int disk;
		cin >> disk;

		if (disk > 0) {
			sInfo->SetTotal(sInfo->GetTotal() + disk);
			sInfo->SetAvail(sInfo->GetAvail() + disk);
			cout << "추가되었습니다." << endl;
			showDiskInfo();
			sInfo->IncAddDisk();
		}
		else {
			cout << "0보다 큰 값을 입력해주세요." << endl;
		}
	}
	else {
		cout << "더 이상 추가할 수 없습니다." << endl;
	}



}

bool AdminMode::CheckChangedDisk() {
	if (sInfo->GetAddDisk() < 3)
		return true;
	return false;
}

void AdminMode::showWaitUser() {
	if (wup->empty() || wup->size() == 0)
		cout << "대기 중인 사용자가 없습니다." << endl;
	else {

		int i = 0;
		for (UserInfo user : *wup) {
			cout << "********[대기 사용자 " << i+1 << "]********" << endl;
			PrintUsers(user);
		}

		cout << "\n" << endl;
		cout << "모든 유저를 승인하시겠습니까? Y" << endl;
		string in;
		cin >> in;

		if (in == "Y" || in == "y") ApproveUser();//유저 승인

	}
}

void AdminMode::ApproveUser() {
	for (UserInfo user : *wup) {
		vup->push_back(user);
	}
	wup->clear();
}

void AdminMode::PrintUsers(UserInfo user) {

	cout << "id: " << user.id << endl;
	cout << "password: " << user.passwd << endl;
	cout << "auth: " << user.auth << endl;
	cout << "identity: " << user.identity << endl;
	cout << "tried: " << user.tried << endl;
	cout << "active: " << user.active << endl;

}

void AdminMode::FileDownload() {
	cout << "파일이 다운로드 되었습니다." << endl;
}

void AdminMode::PrintFiles() {
	cout << "********[파일 정보 출력]********" << endl;
	if (sInfo->GetAllFiles().empty() || sInfo->GetAllFiles().size() == 0)
		cout << "파일이 없습니다." << endl;
	else {
		vector<std::string> serverFiles = sInfo->GetAllFiles();
		for (string file : serverFiles) {
			cout << file << endl;
		}
	}
}

void AdminMode::UploadUpdate() {
	if (sInfo->GetAvail() <= 0)
		cout << "용량이 없습니다." << endl;
	else {
		sInfo->AddFile("upload");
		sInfo->SetUsed(sInfo->GetUsed() + 1);
		sInfo->SetAvail(sInfo->GetAvail() - 1);
		cout << "파일을 업로드 했습니다." << endl;
		PrintFiles();
	}
	showDiskInfo();
}

void AdminMode::DeleteUpdate() {

	if (sInfo->GetUsed() <= 0)
		cout << "삭제 할 파일이 없습니다." << endl;
	else {
		sInfo->DeleteFile();
		sInfo->SetUsed(sInfo->GetUsed() - 1);
		sInfo->SetAvail(sInfo->GetAvail() + 1);
		cout << "파일을 삭제했습니다." << endl;
		PrintFiles();
	}
	
	showDiskInfo();

}

void AdminMode::showDiskInfo() {

	cout << "\n********[서버 용량 확인]********" << endl;
	cout << "서버 전체 용량: " << sInfo->GetTotal() << endl;
	cout << "현재 사용 용량: " << sInfo->GetUsed() << endl;
	cout << "사용 가능 용량: " << sInfo->GetAvail() << endl;

}
