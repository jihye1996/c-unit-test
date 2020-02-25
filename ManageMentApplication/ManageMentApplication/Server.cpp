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
		cout << "1. 사용자 모드" << endl;
		cout << "2. 관리자 모드" << endl;
		cout << "3. 회원 가입 요청" << endl;
		cout << "원하는 모드를 입력하세요" << endl;

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

/* mode 1: 사용자 모드 진입을 위한 함수들*/
void Server::LoginUser() {
	string id, passwd, auth;
	cout << "********[로그인]********" << endl;

	cout << "id: ";
	cin >> id; //아이디 입력

	cout << "password: ";
	passwd = sha256(InputToSecret()); //패스워드 입력값 -> '*'로 변환하기

	cout << "auth: ";
	cin >> auth; // 권한 입력

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
				cout << "휴면계정입니다. 관리자에게 문의하세요." << endl;
				return false;
			}
			else {
				if (validUsers[i].passwd == password) { //비밀번호 체크
					if (validUsers[i].auth == auth) {//권한체크
						validUsers[i].tried = 0;
						currentUser = validUsers[i];
						return true;
					}
					else {
						PlusUserTried(&validUsers[i]); //사용자 권한 틀리면 로그인 시도 횟수 ++
						return false;
					}
				}
				else {
					PlusUserTried(&validUsers[i]); //비밀번호 틀리면 로그인 시도 횟수 ++
					return false;
				}
			}

		}
	}
	cout << "일치하는 사용자가 없습니다." << endl;
	return false;
}

void Server::PlusUserTried(UserInfo* user) {
	cout << "일치하는 사용자가 없습니다." << endl;
	user->tried += 1;
	if (user->tried >= 5)
		user->active = false;
}


/* mode 2: 관리자 모드 진입을 위한 함수들*/
void Server::LoginAdmin() {

	cout << "code: ";

	string code = sha256(InputToSecret()); //관리자 입력값 -> '*'로 변환하기

	if (code.length() > 0) {//TODO: 길이 체크 필요?
		if (CheckCode(code)) {
			AdminMode adminMode = AdminMode(&admininfo, &serverInfo, &validUsers, &waitUsers);
			adminMode.initAdminMode();
			return;
		}
		else cout << "코드가 틀립니다." << endl;
	}
}

bool Server::CheckCode(string code) {
	if (admininfo.code == code)
		return true;
	return false;
}

string Server::InputToSecret() {

	//사용자 입력값 -> '*'로 변환
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



/* mode 3: 회원가입 함수들 */
void Server::registerUser() {
	cout << "********[회원가입]********" << endl;
	cout << "id: 6글자 이상, password: 대소문자 + 숫자, 8글자 이상" << endl;

	//사용자 아이디 입력 받기
	string id = InputId();

	//주민번호 입력받기
	string identity = InputIdentity();

	//사용자 비밀번호 입력 받기
	string passwd;
	string passwd_check;//실수 방지
	while (true) {
		cout << "password: ";
		passwd = InputToSecret();
		cout << "password: ";
		passwd_check = InputToSecret();

		//입력된 비밀번호가 다르면 다시 입력받기
		if (passwd != passwd_check) {
			cout << "비밀번호가 다릅니다." << endl;
			continue;
		}
		if (isVaild_Passwd(passwd) && isNotContain_iden(passwd, identity))
			break;

	}; //비밀번호 유효성 체크

	//사용자 권한 요청
	string auth = InputAuth();

	//암호화하기
	string encrypt_passwd = sha256(passwd);
	string encrypt_identity = sha256(identity);

	//대기 유저에 넣기
	UserInfo user = { id, encrypt_passwd , auth, encrypt_identity };
	waitUsers.push_back(user);
	cout << "********[회원가입 완료]********" << endl;
}

string Server::InputId() {
	string returnStr;

	while (true) {
		cout << "id: ";
		cin >> returnStr;
		if (returnStr.length() < 6)
			cout << "길이가 너무 짧습니다. 6글자 이상 입력해주세요." << endl;
		//아이디 중복체크
		else {
			if (isNotVaild_ID(returnStr) || isNotWait_ID(returnStr)) {
				return returnStr;
			}
		}

	}
}

bool Server::isNotVaild_ID(string id) {
	/*
	사용중인 아이디인지 체크
	true: 중복없음
	false: 중복
	*/
	if (validUsers.empty() || validUsers.size() == 0)
		return true;
	else {
		for (UserInfo user : validUsers) {
			if (user.id == id) {
				cout << "사용중인 아이디입니다." << endl;
				return false;
			}
		}
		return true;
	}
}

bool Server::isNotWait_ID(string id) {
	/*
	승인 대기중인 아이디인지 체크
	true: 중복없음
	false: 중복
	*/
	if (waitUsers.empty() || waitUsers.size() == 0)
		return true;
	else {
		for (UserInfo user : waitUsers) {
			if (user.id == id) {
				cout << "승인 대기 중인 아이디입니다." << endl;
				return false;
			}
		}
		return true;
	}

}

bool Server::isVaild_Passwd(string password) {
	/*
	1. 숫자와 영어대소문자인지 체크
	2. 8자 이상인지 체크
	true: 사용가능
	false: 사용불가능
	*/
	regex patter("[a-zA-Z]+[0-9]+");
	if (regex_match(password, patter))//패턴 일치 확인
		if (password.length() >= 8) // 문자 길이 확인
			return true;
		else {
			cout << "8자 이상 입력해주세요." << endl;
			return false;
		}
	else {
		cout << "잘못된 형식입니다. 영어대소문자와 숫자로 입력해주세요." << endl;
		return false;
	}
}


bool Server::isNotContain_iden(string password, string identity) {
	string iden[4] = { identity.substr(0, 4), identity.substr(2, 4),
						identity.substr(7, 4), identity.substr(9, 4) };

	for (int i = 0; i < 4; i++) {
		if ((password.find(iden[i]) != string::npos)) {
			cout << "비밀번호에 주민번호가 포함되면 안됩니다. 다시 시도해주세요." << endl;
			return false;
		}
	}

	return true;
}

string Server::InputAuth() {
	string returnStr;
	cout << "권한 선택: R(읽기), W(쓰기), RW(읽고쓰기)" << endl;
	while (true) {
		cin >> returnStr;

		if (returnStr == "R" || returnStr == "W" || returnStr == "RW")
			return returnStr;
		else
			cout << "R(읽기), W(쓰기), RW(읽고쓰기) 권한 중에 선택해주세요" << endl;
	}
}

string Server::InputIdentity() {
	string returnStr;

	while (true) {
		cout << "주민번호를 입력하세요. ex)000000-000000" << endl;
		cin >> returnStr;

		if (isVaild_Identity(returnStr)) //주민번호 형식 체크
			return returnStr;
		else {
			cout << "형식이 맞지 않습니다." << endl;
		}
	}
}

bool Server::isVaild_Identity(string identity) {

	regex pattern("[0-9]{6}-[0-9]{6}"); // 000000-000000
	if (regex_match(identity, pattern))//패턴 일치 확인
		return true;
	else
		return false;
}