#include "pch.h"
#include "CppUnitTest.h"
#include"../include/main.h"
#include<vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		
		TEST_METHOD(calculateTest)
		{
			line A(0.0, 1.0);
			line B(2.0, 3.0);
			struct dot testDot = calculate(A, B);
			Assert::AreEqual(testDot.x, -1.0);
			Assert::AreEqual(testDot.y, 1.0);
		}
		TEST_METHOD(level2EquationTest)
		{
			std::vector<double> test = { 1, -4, 3 };
			std::vector<double> solution = level2Equation(test);
			Assert::AreEqual(solution[0], 3.0);
			Assert::AreEqual(solution[1], 1.0);
		}
		TEST_METHOD(getEquationForLCTest)
		{
			circle TestC(0, 0, 1);
			line TestL(0, 0);
			vector<double> test = getEquationForLC(TestL, TestC);
			Assert::AreEqual(test[0], 1.0);
			Assert::AreEqual(test[1], 0.0);
			Assert::AreEqual(test[2], -1.0);
		}
		TEST_METHOD(getCircleLineTest)
		{
			circle A(0, 0, 1);
			circle B(1, 1, 1);
			line* test = get2CircleLine(A, B);
			Assert::IsNotNull(test);
			Assert::AreEqual(test->k, -1.0);
			Assert::AreEqual(test->b, 1.0);
		}
	};
}
