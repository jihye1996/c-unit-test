#include "pch.h"
#include "CppUnitTest.h"
#include "../Calculator/Calculator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		Calculator cal;

		TEST_METHOD(TestAdd)
		{
			Assert::AreEqual(8, cal.add(3, 5));
			Assert::AreEqual(8, cal.add(3.0, 5.0));
			Assert::AreEqual(8, cal.add(3.3, 5.5));
			Assert::AreEqual(8, cal.add(3.5, 5.5)); 

			Assert::AreEqual(-8, cal.add(-3, -5));
			Assert::AreEqual(-8, cal.add(-3.0, -5.0));
			Assert::AreEqual(-8, cal.add(-3.3, -5.5));
			Assert::AreEqual(-8, cal.add(-3.5, -5.5));

		}

		TEST_METHOD(TestSub)
		{
			Assert::AreEqual(-2, cal.sub(3, 5));
			Assert::AreEqual(-2, cal.sub(3.0, 5.0));
			Assert::AreEqual(-2, cal.sub(3.3, 5.5));
			Assert::AreEqual(-2, cal.sub(3.5, 5.5));

			Assert::AreEqual(2, cal.sub(5, 3));
			Assert::AreEqual(2, cal.sub(5.0, 3.0));
			Assert::AreEqual(2, cal.sub(5.3, 3.5));
			Assert::AreEqual(2, cal.sub(5.5, 3.5));
		}

		TEST_METHOD(TestDiv)
		{
			Assert::AreEqual(2, cal.div(4, 2));
			Assert::AreEqual(0, cal.div(4, 5));
			Assert::AreEqual(0, cal.div(0, -1));

			try
			{
				cal.div(4, 0);
			}
			catch (int e)
			{
				
				Assert::AreEqual(e, 0);
			}

		}

		TEST_METHOD(TestMul)
		{
			Assert::AreEqual(6, cal.mult(2, 3));
			Assert::AreEqual(-6, cal.mult(-2, 3));
			Assert::AreEqual(-6, cal.mult(2, -3));
			Assert::AreEqual(6, cal.mult(-2, -3));

			Assert::AreEqual(6, cal.mult(2.0, 3.0));
			Assert::AreEqual(-6, cal.mult(-2.0, 3.0));
			Assert::AreEqual(-6, cal.mult(2.0, -3.0));
			Assert::AreEqual(6, cal.mult(-2.0, -3.0));

			Assert::AreEqual(0, cal.mult(0, 0));
		}

		TEST_METHOD(TestFactorial)
		{
			Assert::AreEqual(3*2*1, cal.factorial(3));
			Assert::AreEqual(1, cal.factorial(1));
			Assert::AreEqual(1, cal.factorial(0));
			Assert::AreEqual(-1, cal.factorial(-1));
		}
	};
}
