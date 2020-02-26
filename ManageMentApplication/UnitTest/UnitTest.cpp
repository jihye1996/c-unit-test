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
			�׽�Ʈ �Լ� 1��
			bool CheckPermission(); ����� ���� üũ, RW�� W�� ��츸 TRUE
									�����׽�Ʈ��Ʈ ��ȣ 14, 15, 16
			*/

			//arrange, ������ �ٸ� 4���� �����
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
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());//�� üũ
			Assert::IsFalse(userM.CheckPermission()); //������ R�϶�, false

			server.setCurrentUser(wUser);
			userM.setCurrentUser(server.getcurrentUserP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());// ���� �� üũ
			Assert::IsTrue(userM.CheckPermission()); //������ W�϶�, true

			server.setCurrentUser(rwUser);
			userM.setCurrentUser(server.getcurrentUserP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());// ���� �� üũ
			Assert::IsTrue(userM.CheckPermission()); //������ RW�϶�, true

			server.setCurrentUser(otherUser);
			userM.setCurrentUser(server.getcurrentUserP());
			Logger::WriteMessage(userM.getCurrentUser()->auth.c_str());// ���� �� üũ
			Assert::IsFalse(userM.CheckPermission()); //�� �� ���� ������ ��, false
		}

		TEST_METHOD(adminModeFunctions)
		{
			/*
			bool CheckChangedDisk(): ��ũ �߰� Ƚ�� Ȯ��: �����׽�Ʈ��Ʈ ��ȣ 24
			*/

			//arrange
			Server server = Server();
			AdminMode adminM = AdminMode(server.getAdminInfoP(), server.getServerInfoP(), NULL, NULL);//�׽�Ʈ �� �ΰ��� ���ڸ� �־ OK

			//act & Assert
			Assert::IsTrue(adminM.CheckChangedDisk()); //disk �߰� Ƚ��: 0

			adminM.UpdateServerInfo();//disk �߰� Ƚ��: 1
			Assert::IsTrue(adminM.CheckChangedDisk()); //disk �߰� Ƚ��: 1

			adminM.UpdateServerInfo();//disk �߰� Ƚ��: 2
			Assert::IsTrue(adminM.CheckChangedDisk()); //disk �߰� Ƚ��: 2

			adminM.UpdateServerInfo();//disk �߰� Ƚ��: 3
			Assert::IsFalse(adminM.CheckChangedDisk()); //disk �߰� Ƚ��: 3

			adminM.UpdateServerInfo();//disk �߰� Ƚ��: 4
			Assert::IsFalse(adminM.CheckChangedDisk()); //disk �߰� Ƚ��: 
		}

		TEST_METHOD(server)
		{
			/*
			bool CheckUser: ����� �Է� id, passwd, auth ��ġ ���� üũ, ���� �׽�Ʈ��Ƽ: 8 ~12
			bool CheckCode: ������ �ڵ� ��: ���� �׽�Ʈ��Ƽ 20

			bool isNotVaild_ID: ���̵� �ߺ� üũ: ���� �׽�Ʈ��Ƽ 32 33
			bool isNotWait_ID: ��� �� ���� ���̵�� �ߺ� üũ: ���� �׽�Ʈ��Ƽ 32 33
			bool isVaild_Passwd: ��й�ȣ ��ȿ�� üũ: ���� �׽�Ʈ��Ƽ36, 37
			bool isNotContain_iden: ��й�ȣ�� �ֹι�ȣ ���ԵǾ��ִ��� Ȯ��: ���� �׽�Ʈ��Ƽ37
			bool isVaild_Identity: �ֹι�ȣ ���� üũ�ϱ�: ���� �׽�Ʈ��Ƽ 34 35
			*/

			//arrange
			Server server = Server();


			//act & Assert: ��ȿ�� ����ڿ� �ߺ��Ǵ� id ���� üũ�ϴ� �Լ�
			Assert::IsTrue(server.isNotVaild_ID("jihye123")); //������ ��ȿ�� ����ڰ� ���� �� 
			UserInfo validUser = { "jihye123", sha256("jihye123"), "R", sha256("960313-123123") };
			server.addValidUser(validUser);
			Assert::IsFalse(server.isNotVaild_ID("jihye123")); //������ ����ڰ� �ְ� �ߺ��Ǵ� ����ڰ� ���� ��
			Assert::IsTrue(server.isNotVaild_ID("jihye111")); //������ ����ڰ� �ְ� �ߺ��Ǵ� ����ڰ� ���� ��

			//act & Assert: ������� ����ڿ� �ߺ��Ǵ� id ���� üũ�ϴ� �Լ�
			Assert::IsTrue(server.isNotWait_ID("Leehye123")); //������ ������� ����ڰ� ���� �� 
			UserInfo waitUser = { "Leehye123", sha256("Leehye123"), "R", sha256("960313-123123") };
			server.addValidUser(waitUser);
			Assert::IsFalse(server.isNotVaild_ID("Leehye123")); //������ ����ڰ� �ְ� �ߺ��Ǵ� ����ڰ� ���� ��
			Assert::IsTrue(server.isNotVaild_ID("Leehye111")); //������ ����ڰ� �ְ� �ߺ��Ǵ� ����ڰ� ���� ��

			//act & Assert: ��ȿ�� ��������� üũ�ϴ� �Լ�
			Assert::IsFalse(server.CheckUser("jihye", "jihye123", "RW")); //��� Ʋ���� ��
			Assert::IsFalse(server.CheckUser("jihye123", "jihye123", "RW")); //id�� �¾��� ��
			Assert::IsFalse(server.CheckUser("jihye123", sha256("jihye123"), "RW")); //id, password�� �¾��� ��
			Assert::IsTrue(server.CheckUser("jihye123", sha256("jihye123"), "R")); //��� �¾��� ��

			//act & Assert: ������ �ڵ� ��ġ �Լ�
			Assert::IsFalse(server.CheckCode(sha256("")));
			Assert::IsFalse(server.CheckCode(sha256("123")));
			Assert::IsFalse(server.CheckCode(sha256("abc")));
			Assert::IsTrue(server.CheckCode(sha256("jihye123")));

			//act & Assert: ��й�ȣ ��ȿ�� üũ
			Assert::IsFalse(server.isVaild_Passwd("1234")); // ���ڰ� ��� false
			Assert::IsFalse(server.isVaild_Passwd("abacd")); //���ڰ� ��� false
			Assert::IsFalse(server.isVaild_Passwd("abc12")); // ���� ������ false
			Assert::IsFalse(server.isVaild_Passwd("12abcdef")); //���ڰ� �����ͼ�  false
			Assert::IsTrue(server.isVaild_Passwd("jihye123"));  //����+����+����8�̻� -> true
			Assert::IsFalse(server.isVaild_Passwd("jihye!123")); //Ư������ X

			//act & Assert: ��й�ȣ�� �ֹι�ȣ ���Կ��� üũ
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "123489-234512")); 
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "981234-234512")); 
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "981314-123498"));
			Assert::IsFalse(server.isNotContain_iden("jihye!1234", "981314-981234"));
			Assert::IsTrue(server.isNotContain_iden("jihye!1234", "987654-125634"));


			//act & Assert: �ֹι�ȣ ���� üũ
			Assert::IsFalse(server.isVaild_Identity("abcd12-123456"));
			Assert::IsFalse(server.isVaild_Identity("1234567123456"));
			Assert::IsTrue(server.isVaild_Identity("123456-123456"));

		}

	};
}

