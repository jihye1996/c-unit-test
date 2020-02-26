#include "pch.h"
#include "CppUnitTest.h"
#include "../ManageMentApplication/AdminInfo.h"
#include "../ManageMentApplication/AdminMode.cpp"
#include "../ManageMentApplication/Server.cpp"
#include "../ManageMentApplication/ServerInfo.cpp"
#include "../ManageMentApplication/UserInfo.h"
#include "../ManageMentApplication/UserMode.cpp"
#include "../ManageMentApplication/sha256.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:


		TEST_METHOD(UserModeFunctions)
		{
			/*
			테스트 함수 1개
			bool CheckPermission(); 사용자 권한 체크, RW와 W일 경우만 TRUE
									관련테스트시트 번호 14, 15, 16
			*/

			//arrange, 권한이 다른 4명의 사용자
			Server server = Server();
			UserInfo rUser = { "jihye123", "a8bce92702f16a3abcb340b1c1e4b6a0503f82c29a6129b0d961949817104466",
							"R", "b2f490207b3b3abde513c3ac538aa73d1a633d60cbe1f544a9e2a5e61ddf27a1" };
			UserInfo wUser = { "jihye123", "a8bce92702f16a3abcb340b1c1e4b6a0503f82c29a6129b0d961949817104466",
							"W", "b2f490207b3b3abde513c3ac538aa73d1a633d60cbe1f544a9e2a5e61ddf27a1" };
			UserInfo rwUser = { "jihye123", "a8bce92702f16a3abcb340b1c1e4b6a0503f82c29a6129b0d961949817104466",
							"RW", "b2f490207b3b3abde513c3ac538aa73d1a633d60cbe1f544a9e2a5e61ddf27a1" };
			UserInfo otherUser = { "jihye123", "a8bce92702f16a3abcb340b1c1e4b6a0503f82c29a6129b0d961949817104466",
							"123", "b2f490207b3b3abde513c3ac538aa73d1a633d60cbe1f544a9e2a5e61ddf27a1" };

			//act & Assert
			server.setCurrentUser(rUser);
			UserMode userM = UserMode(server.getcurrentUserP(), server.getServerInfoP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());//값 체크
			Assert::IsFalse(userM.CheckPermission()); //권한이 R일때, false

			server.setCurrentUser(wUser);
			userM.setCurrentUser(server.getcurrentUserP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());// 권한 값 체크
			Assert::IsTrue(userM.CheckPermission()); //권한이 W일때, true

			server.setCurrentUser(rwUser);
			userM.setCurrentUser(server.getcurrentUserP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());// 권한 값 체크
			Assert::IsTrue(userM.CheckPermission()); //권한이 RW일때, true

			server.setCurrentUser(otherUser);
			userM.setCurrentUser(server.getcurrentUserP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());// 권한 값 체크
			Assert::IsFalse(userM.CheckPermission()); //그 외 값이 들어왔을 때, false
		}

		TEST_METHOD(adminModeFunctions)
		{
			/*
			bool CheckChangedDisk(): 디스크 추가 횟수 확인: 관련테스트시트 번호 24
			*/

			//arrange
			Server server = Server();
			AdminMode adminM = AdminMode(server.getAdminInfoP(), server.getServerInfoP(), NULL, NULL);//테스트 시 두개의 인자만 있어도 OK

			//act & Assert
			Assert::IsTrue(adminM.CheckChangedDisk()); //disk 추가 횟수: 0

			adminM.UpdateServerInfo();//disk 추가 횟수: 1
			Assert::IsTrue(adminM.CheckChangedDisk()); //disk 추가 횟수: 1

			adminM.UpdateServerInfo();//disk 추가 횟수: 2
			Assert::IsTrue(adminM.CheckChangedDisk()); //disk 추가 횟수: 2

			adminM.UpdateServerInfo();//disk 추가 횟수: 3
			Assert::IsFalse(adminM.CheckChangedDisk()); //disk 추가 횟수: 3

			adminM.UpdateServerInfo();//disk 추가 횟수: 4
			Assert::IsFalse(adminM.CheckChangedDisk()); //disk 추가 횟수: 
		}

		TEST_METHOD(server)
		{
			/*
			bool CheckUser: 사용자 입력 id, passwd, auth 일치 여부 체크, 관련 테스트시티: 8 ~12
			bool CheckCode: 관리자 코드 비교: 관련 테스트시티 20

			bool isNotVaild_ID: 아이디 중복 체크: 관련 테스트시티 32 33
			bool isNotWait_ID: 대기 중 유저 아이디와 중복 체크: 관련 테스트시티 32 33
			bool isVaild_Passwd: 비밀번호 유효성 체크: 관련 테스트시티36, 37
			bool isNotContain_iden: 비밀번호에 주민번호 포함되어있는지 확인: 관련 테스트시티37
			bool isVaild_Identity: 주민번호 형식 체크하기: 관련 테스트시티 34 35
			*/

			//arrange
			Server server = Server();


			//act & Assert: 유효한 사용자와 중복되는 id 인지 체크하는 함수
			Assert::IsTrue(server.isNotVaild_ID("jihye123")); //서버에 유효한 사용자가 없을 때 
			UserInfo validUser = { "jihye123", sha256("jihye123"), "R", sha256("960313-123123") };
			server.addValidUser(validUser);
			Assert::IsFalse(server.isNotVaild_ID("jihye123")); //서버에 사용자가 있고 중복되는 사용자가 있을 때
			Assert::IsTrue(server.isNotVaild_ID("jihye111")); //서버에 사용자가 있고 중복되는 사용자가 없을 대

			//act & Assert: 대기중인 사용자와 중복되는 id 인지 체크하는 함수
			Assert::IsTrue(server.isNotWait_ID("Leehye123")); //서버에 대기중인 사용자가 없을 때 
			UserInfo waitUser = { "Leehye123", sha256("Leehye123"), "R", sha256("960313-123123") };
			server.addValidUser(waitUser);
			Assert::IsFalse(server.isNotVaild_ID("Leehye123")); //서버에 사용자가 있고 중복되는 사용자가 있을 때
			Assert::IsTrue(server.isNotVaild_ID("Leehye111")); //서버에 사용자가 있고 중복되는 사용자가 없을 대

			//act & Assert: 유효한 사용자인지 체크하는 함수
			Assert::IsFalse(server.CheckUser("jihye", "jihye123", "RW")); //모두 틀렸을 때
			Assert::IsFalse(server.CheckUser("jihye123", "jihye123", "RW")); //id만 맞았을 때
			Assert::IsFalse(server.CheckUser("jihye123", sha256("jihye123"), "RW")); //id, password가 맞았을 때
			Assert::IsTrue(server.CheckUser("jihye123", sha256("jihye123"), "R")); //모두 맞았을 때

			//act & Assert: 관리자 코드 일치 함수
			Assert::IsFalse(server.CheckCode(sha256("")));
			Assert::IsFalse(server.CheckCode(sha256("123")));
			Assert::IsFalse(server.CheckCode(sha256("abc")));
			Assert::IsTrue(server.CheckCode(sha256("jihye123")));

			//act & Assert: 비밀번호 유효성 체크
			Assert::IsFalse(server.isVaild_Passwd("1234")); // 문자가 없어서 false
			Assert::IsFalse(server.isVaild_Passwd("abacd")); //숫자가 없어서 false
			Assert::IsFalse(server.isVaild_Passwd("abc12")); // 길이 때문에 false
			Assert::IsFalse(server.isVaild_Passwd("12abcdef")); //숫자가 먼저와서  false
			Assert::IsTrue(server.isVaild_Passwd("jihye123"));  //문자+숫자+길이8이상 -> true
			Assert::IsFalse(server.isVaild_Passwd("jihye!123")); //특수문자 X

			//act & Assert: 비밀번호에 주민번호 포함여부 체크
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "123489-234512")); 
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "981234-234512")); 
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "981314-123498"));
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "981314-981234"));
			Assert::IsTrue(server.isNotContain_iden("jihye!1234", "987654-125634"));


			//act & Assert: 주민번호 형식 체크
			Assert::IsFalse(server.isVaild_Identity("abcd12-123456"));
			Assert::IsFalse(server.isVaild_Identity("1234567123456"));
			Assert::IsTrue(server.isVaild_Identity("123456-123456"));

		}

	};
}

