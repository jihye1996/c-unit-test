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

		cout << "\n********[����ڸ��]********" << endl;
		cout << "1. ���Ͼ��ε�" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� �ٿ�ε�" << endl;
		cout << "q. �α׾ƿ�" << endl;
		cout << "���ϴ� �۾��� �Է��ϼ���" << endl;

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
	cout << "\n********[�α��� ����]********" << endl;
	cout << "���� ��ü �뷮: " << serverInfo->GetTotal() << endl;
	cout << "���� ��� �뷮: " << serverInfo->GetUsed() << endl;
	cout << "��� ���� �뷮: " << serverInfo->GetAvail() << endl;
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
			cout << "�ٿ�ε� �� ������ �����ϴ�." << endl;
		else {
			cout << "������ �ٿ�ε� �Ǿ����ϴ�." << endl;
		}
	}
		
}

bool UserMode::CheckPermission() {
	if (currentUser->auth == "RW" || currentUser->auth == "W")
		return true;

	cout << "�б� ���ѹۿ� �����ϴ�. ������ Ȯ�����ּ���." << endl;
	return false;
}

void UserMode::PrintFiles() {
	if (serverInfo->GetAllFiles().empty() || serverInfo->GetAllFiles().size() == 0)
		cout << "������ �����ϴ�." << endl;
	else {
		vector<std::string> serverFiles = serverInfo->GetAllFiles();
		for (string file : serverFiles) {
			cout << file << endl;
		}
	}

}

void UserMode::UploadUpdate() {
	if (serverInfo->GetAvail() <= 0)
		cout << "�뷮�� �����ϴ�." << endl;
	else {
		serverInfo->AddFile("upload");
		serverInfo->SetUsed(serverInfo->GetUsed() + 1);
		serverInfo->SetAvail(serverInfo->GetAvail() - 1);
		cout << "������ ���ε� �߽��ϴ�." << endl;
		PrintFiles();
	}
}

void UserMode::DeleteUpdate() {
	if (serverInfo->GetUsed() <= 0)
		cout << "���� �� ������ �����ϴ�." << endl;
	else {
		serverInfo->DeleteFile();
		serverInfo->SetUsed(serverInfo->GetUsed() - 1);
		serverInfo->SetAvail(serverInfo->GetAvail() + 1);
		cout << "������ �����߽��ϴ�." << endl;
		PrintFiles();
		
	}
	
}