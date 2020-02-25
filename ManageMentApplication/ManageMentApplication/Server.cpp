#include "Server.h"

Server::Server() {
	currentUser = UserInfo();
	serverInfo = ServerInfo();
}

Server::Server(ServerInfo s, AdminInfo a) {
	serverInfo = s;
	admininfo = a;
}

void Server::initConsole() {
	while (true) {
		cout << "1. ����� ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "3. ȸ�� ���� ��û" << endl;
		cout << "���ϴ� ��带 �Է��ϼ���" << endl;

		//get user input
		char input;
		cin >> input;

		switch (input)
		{
		case '1':
			LoginUser();
			cout << endl;
			break;
		case '2':
			LoginAdmin();
			cout << endl;
			break;
		case '3':
			registerUser();
			cout << endl;
			break;
		default:
			cout << "wrong input" << endl;
			break;
		}


	}
}

/* mode 1: ����� ��� ������ ���� �Լ���*/
void Server::LoginUser() {
	string id, passwd, auth;
	cout << "********[�α���]********" << endl;

	cout << "id: ";
	cin >> id; //���̵� �Է�

	cout << "password: ";
	passwd = sha256(InputToSecret()); //�н����� �Է°� -> '*'�� ��ȯ�ϱ�

	cout << "auth: ";
	cin >> auth; // ���� �Է�

	if (CheckUser(id, passwd, auth)) {


		UserMode userMode = UserMode(&currentUser, &serverInfo);
		userMode.initUserMode();
		return;

	}

}

bool Server::CheckUser(string id, string password, string auth) {
	for (unsigned int i = 0; i < validUsers.size(); i++) {
		if (validUsers[i].id == id) {
			if (!validUsers[i].active) {
				cout << "�޸�����Դϴ�. �����ڿ��� �����ϼ���." << endl;
				return false;
			}
			else {
				if (validUsers[i].passwd == password) { //��й�ȣ üũ
					if (validUsers[i].auth == auth) {//����üũ
						validUsers[i].tried = 0;
						currentUser = validUsers[i];
						return true;
					}
					else {
						PlusUserTried(&validUsers[i]); //����� ���� Ʋ���� �α��� �õ� Ƚ�� ++
						return false;
					}
				}
				else {
					PlusUserTried(&validUsers[i]); //��й�ȣ Ʋ���� �α��� �õ� Ƚ�� ++
					return false;
				}
			}

		}
	}
	cout << "��ġ�ϴ� ����ڰ� �����ϴ�." << endl;
	return false;
}

void Server::PlusUserTried(UserInfo* user) {
	cout << "��ġ�ϴ� ����ڰ� �����ϴ�." << endl;
	user->tried += 1;
	if (user->tried >= 5)
		user->active = false;
}


/* mode 2: ������ ��� ������ ���� �Լ���*/
void Server::LoginAdmin() {

	cout << "code: ";

	string code = sha256(InputToSecret()); //������ �Է°� -> '*'�� ��ȯ�ϱ�

	if (code.length() > 0) {//TODO: ���� üũ �ʿ�?
		if (CheckCode(code)) {
			AdminMode adminMode = AdminMode(&admininfo, &serverInfo, &validUsers, &waitUsers);
			adminMode.initAdminMode();
			return;
		}
		else cout << "�ڵ尡 Ʋ���ϴ�." << endl;
	}
}

bool Server::CheckCode(string code) {
	if (admininfo.code == code)
		return true;
	return false;
}

string Server::InputToSecret() {

	//����� �Է°� -> '*'�� ��ȯ
	string returnStr;


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



/* mode 3: ȸ������ �Լ��� */
void Server::registerUser() {
	cout << "********[ȸ������]********" << endl;
	cout << "id: 6���� �̻�, password: ��ҹ��� + ����, 8���� �̻�" << endl;

	//����� ���̵� �Է� �ޱ�
	string id = InputId();

	//�ֹι�ȣ �Է¹ޱ�
	string identity = InputIdentity();

	//����� ��й�ȣ �Է� �ޱ�
	string passwd;
	string passwd_check;//�Ǽ� ����
	while (true) {
		cout << "password: ";
		passwd = InputToSecret();
		cout << "password: ";
		passwd_check = InputToSecret();

		//�Էµ� ��й�ȣ�� �ٸ��� �ٽ� �Է¹ޱ�
		if (passwd != passwd_check) {
			cout << "��й�ȣ�� �ٸ��ϴ�." << endl;
			continue;
		}
		if (isVaild_Passwd(passwd) && isNotContain_iden(passwd, identity))
			break;

	}; //��й�ȣ ��ȿ�� üũ

	//����� ���� ��û
	string auth = InputAuth();

	//��ȣȭ�ϱ�
	string encrypt_passwd = sha256(passwd);
	string encrypt_identity = sha256(identity);

	//��� ������ �ֱ�
	UserInfo user = { id, encrypt_passwd , auth, encrypt_identity };
	waitUsers.push_back(user);
	cout << "********[ȸ������ �Ϸ�]********" << endl;
}

string Server::InputId() {
	string returnStr;

	while (true) {
		cout << "id: ";
		cin >> returnStr;
		if (returnStr.length() < 6)
			cout << "���̰� �ʹ� ª���ϴ�. 6���� �̻� �Է����ּ���." << endl;
		//���̵� �ߺ�üũ
		else {
			if (isNotVaild_ID(returnStr) || isNotWait_ID(returnStr)) {
				return returnStr;
			}
		}

	}
}

bool Server::isNotVaild_ID(string id) {
	/*
	������� ���̵����� üũ
	true: �ߺ�����
	false: �ߺ�
	*/
	if (validUsers.empty() || validUsers.size() == 0)
		return true;
	else {
		for (UserInfo user : validUsers) {
			if (user.id == id) {
				cout << "������� ���̵��Դϴ�." << endl;
				return false;
			}
		}
		return true;
	}
}

bool Server::isNotWait_ID(string id) {
	/*
	���� ������� ���̵����� üũ
	true: �ߺ�����
	false: �ߺ�
	*/
	if (waitUsers.empty() || waitUsers.size() == 0)
		return true;
	else {
		for (UserInfo user : waitUsers) {
			if (user.id == id) {
				cout << "���� ��� ���� ���̵��Դϴ�." << endl;
				return false;
			}
		}
		return true;
	}

}

bool Server::isVaild_Passwd(string password) {
	/*
	1. ���ڿ� �����ҹ������� üũ
	2. 8�� �̻����� üũ
	true: ��밡��
	false: ���Ұ���
	*/
	regex patter("[a-zA-Z]+[0-9]+");
	if (regex_match(password, patter))//���� ��ġ Ȯ��
		if (password.length() >= 8) // ���� ���� Ȯ��
			return true;
		else {
			cout << "8�� �̻� �Է����ּ���." << endl;
			return false;
		}
	else {
		cout << "�߸��� �����Դϴ�. �����ҹ��ڿ� ���ڷ� �Է����ּ���." << endl;
		return false;
	}
}


bool Server::isNotContain_iden(string password, string identity) {
	string iden[4] = { identity.substr(0, 4), identity.substr(2, 4),
						identity.substr(7, 4), identity.substr(9, 4) };

	for (int i = 0; i < 4; i++) {
		if ((password.find(iden[i]) != string::npos)) {
			cout << "��й�ȣ�� �ֹι�ȣ�� ���ԵǸ� �ȵ˴ϴ�. �ٽ� �õ����ּ���." << endl;
			return false;
		}
	}

	return true;
}

string Server::InputAuth() {
	string returnStr;
	cout << "���� ����: R(�б�), W(����), RW(�а���)" << endl;
	while (true) {
		cin >> returnStr;

		if (returnStr == "R" || returnStr == "W" || returnStr == "RW")
			return returnStr;
		else
			cout << "R(�б�), W(����), RW(�а���) ���� �߿� �������ּ���" << endl;
	}
}

string Server::InputIdentity() {
	string returnStr;

	while (true) {
		cout << "�ֹι�ȣ�� �Է��ϼ���. ex)000000-000000" << endl;
		cin >> returnStr;

		if (isVaild_Identity(returnStr)) //�ֹι�ȣ ���� üũ
			return returnStr;
		else {
			cout << "������ ���� �ʽ��ϴ�." << endl;
		}
	}
}

bool Server::isVaild_Identity(string identity) {

	regex pattern("[0-9]{6}-[0-9]{6}"); // 000000-000000
	if (regex_match(identity, pattern))//���� ��ġ Ȯ��
		return true;
	else
		return false;
}