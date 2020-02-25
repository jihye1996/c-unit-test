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
		cout << "********[�����ڸ��]********" << endl;
		cout << "1. ������ �ڵ� ����" << endl;
		cout << "2. ������ ���� ����" << endl;
		cout << "3. �ϵ� �뷮 �߰�" << endl;
		cout << "4. ��� ���� ���� ����" << endl;
		cout << "5. ���� ���ε�" << endl;
		cout << "6. ���� ����" << endl;
		cout << "7. ���� �ٿ�ε�" << endl;
		cout << "Q. �����ϱ�" << endl;
		cout << "���ϴ� �۾��� �Է��ϼ���" << endl;

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

	cout << "������ Ȯ���� ���� ������ �ڵ带 �Է����ּ���." << endl;
	string checkcode = InputCode();

	if (sha256(checkcode) == admin->code) {
		cout << "������ Ȯ���� �Ϸ�Ǿ����ϴ�. �ٲٰ� ���� ������ �ڵ带 �Է����ּ���." << endl;
		string code = InputCode();//������ �Է°� -> '*'�� ��ȯ�ϱ�
		string codeCheck = InputCode();//������ �Է°� -> '*'�� ��ȯ�ϱ�
		if (code == codeCheck)
			admin->code = sha256(code);
		else {

		}
	}
	else {
		cout << "�ڵ尡 ��ġ���� �ʽ��ϴ�." << endl;
	}



}

string AdminMode::InputCode() {

	//����� �Է°� -> '*'�� ��ȯ
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
		cout << "����ڰ� �����ϴ�." << endl;
	else {
		int i = 0;
		for (UserInfo user : *vup) {
			cout << "********[���ε� ����� " << i + 1 << "]********" << endl;
			PrintUsers(user);
			i++;
		}
	}
}

void AdminMode::AddDisk() {
	if (CheckChangedDisk()) {
		showDiskInfo();
		cout << "****���ǻ���: �ִ� 3������ �߰� ����!!!****" << endl;
		cout << "�߰��� ��ũ �뷮�� �Է��ϼ���." << endl;

		unsigned int disk;
		cin >> disk;

		if (disk > 0) {
			sInfo->SetTotal(sInfo->GetTotal() + disk);
			sInfo->SetAvail(sInfo->GetAvail() + disk);
			cout << "�߰��Ǿ����ϴ�." << endl;
			showDiskInfo();
			sInfo->IncAddDisk();
		}
		else {
			cout << "0���� ū ���� �Է����ּ���." << endl;
		}
	}
	else {
		cout << "�� �̻� �߰��� �� �����ϴ�." << endl;
	}



}

bool AdminMode::CheckChangedDisk() {
	if (sInfo->GetAddDisk() < 3)
		return true;
	return false;
}

void AdminMode::showWaitUser() {
	if (wup->empty() || wup->size() == 0)
		cout << "��� ���� ����ڰ� �����ϴ�." << endl;
	else {

		int i = 0;
		for (UserInfo user : *wup) {
			cout << "********[��� ����� " << i+1 << "]********" << endl;
			PrintUsers(user);
		}

		cout << "\n" << endl;
		cout << "��� ������ �����Ͻðڽ��ϱ�? Y" << endl;
		string in;
		cin >> in;

		if (in == "Y" || in == "y") ApproveUser();//���� ����

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
	cout << "������ �ٿ�ε� �Ǿ����ϴ�." << endl;
}

void AdminMode::PrintFiles() {
	cout << "********[���� ���� ���]********" << endl;
	if (sInfo->GetAllFiles().empty() || sInfo->GetAllFiles().size() == 0)
		cout << "������ �����ϴ�." << endl;
	else {
		vector<std::string> serverFiles = sInfo->GetAllFiles();
		for (string file : serverFiles) {
			cout << file << endl;
		}
	}
}

void AdminMode::UploadUpdate() {
	if (sInfo->GetAvail() <= 0)
		cout << "�뷮�� �����ϴ�." << endl;
	else {
		sInfo->AddFile("upload");
		sInfo->SetUsed(sInfo->GetUsed() + 1);
		sInfo->SetAvail(sInfo->GetAvail() - 1);
		cout << "������ ���ε� �߽��ϴ�." << endl;
		PrintFiles();
	}
	showDiskInfo();
}

void AdminMode::DeleteUpdate() {

	if (sInfo->GetUsed() <= 0)
		cout << "���� �� ������ �����ϴ�." << endl;
	else {
		sInfo->DeleteFile();
		sInfo->SetUsed(sInfo->GetUsed() - 1);
		sInfo->SetAvail(sInfo->GetAvail() + 1);
		cout << "������ �����߽��ϴ�." << endl;
		PrintFiles();
	}
	
	showDiskInfo();

}

void AdminMode::showDiskInfo() {

	cout << "\n********[���� �뷮 Ȯ��]********" << endl;
	cout << "���� ��ü �뷮: " << sInfo->GetTotal() << endl;
	cout << "���� ��� �뷮: " << sInfo->GetUsed() << endl;
	cout << "��� ���� �뷮: " << sInfo->GetAvail() << endl;

}
