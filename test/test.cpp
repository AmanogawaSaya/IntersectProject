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
			line A(2.0, -1.0, 2.0);
			line B(4.0, -1.0, 1.0);
			struct dot testDot = calculate(A, B);
			Assert::AreEqual(testDot.x, 0.5);
			Assert::AreEqual(testDot.y, 3.0);
		}

		TEST_METHOD(calculateTest2)
		{
			line A(2.0, -1.0, 2.0);
			line B(2.0, -1.0, 1.0);
			struct dot testDot = calculate(A, B);
			Assert::AreEqual(testDot.x, 0.0);
			Assert::AreEqual(testDot.y, 0.0);
		}

		TEST_METHOD(calculateTest3)
		{
			line A(1.0, 0.0, -1.0);
			line B(2.0, -1.0, 1.0);
			struct dot testDot = calculate(A, B);
			Assert::AreEqual(testDot.x, 1.0);
			Assert::AreEqual(testDot.y, 3.0);
		}
		TEST_METHOD(level2EquationTest)
		{
			std::vector<double> test = { 1, -4, 3 };
			std::vector<double> solution = level2Equation(test);
			Assert::AreEqual(solution[0], 3.0);
			Assert::AreEqual(solution[1], 1.0);
		}

		TEST_METHOD(level2EquationTest2)
		{
			std::vector<double> test = { 1, 1, 3 };
			std::vector<double> solution = level2Equation(test);
			Assert::AreEqual(solution.size(), (size_t)0);
		}

		TEST_METHOD(level2EquationTest3)
		{
			std::vector<double> test = { 1, -2, 1 };
			std::vector<double> solution = level2Equation(test);
			Assert::AreEqual(solution.size(), (size_t)1);
			Assert::AreEqual(solution[0], 1.0);
		}
		TEST_METHOD(getEquationForLCTest)
		{
			circle TestC(0, 0, 1);
			line TestL(0, 1, 0);
			vector<double> test = getEquationForLC(TestL, TestC);
			Assert::AreEqual(test[0], 1.0);
			Assert::AreEqual(test[1], 0.0);
			Assert::AreEqual(test[2], -1.0);
		}

		TEST_METHOD(getEquationForLCTest2)
		{
			circle TestC(1, 1, 1);
			line TestL(1, 1, -1);
			vector<double> test = getEquationForLC(TestL, TestC);
			Assert::AreEqual(test[0], 2.0);
			Assert::AreEqual(test[1], -2.0);
			Assert::AreEqual(test[2], 0.0);
		}
		TEST_METHOD(getCircleLineTest)
		{
			circle A(0, 0, 1);
			circle B(1, 1, 1);
			line* test = get2CircleLine(A, B);
			double k = -test->a / test->b;
			double b = -test->c / test->b;
			Assert::IsNotNull(test);
			Assert::AreEqual(k, -1.0);
			Assert::AreEqual(b, 1.0);
		}

		TEST_METHOD(getCircleLineTest2)
		{
			circle A(-1, 1, 1);
			circle B(1, 2, 1);
			line* test2 = get2CircleLine(A, B);
			Assert::IsNull(test2);
		}
		TEST_METHOD(getCircleLineTest3)
		{
			circle A(-1, 1, 1);
			circle B(1, 1, 1);
			line* test2 = get2CircleLine(A, B);
			Assert::IsNotNull(test2);
			Assert::AreEqual(test2->a, 4.0);
			Assert::AreEqual(test2->b, 0.0);
			Assert::AreEqual(test2->c, 0.0);
		}
		TEST_METHOD(getCircleLineTest4)
		{
			circle A(-2, 1, 2);
			circle B(-1, 1, 1);
			line* test2 = get2CircleLine(A, B);
			Assert::IsNotNull(test2);
			Assert::AreEqual(test2->a, 2.0);
			Assert::AreEqual(test2->b, 0.0);
			Assert::AreEqual(test2->c, 0.0);
		}
		TEST_METHOD(getCircleLineTest5)
		{
			circle A(-2, 2, 2);
			circle B(-2, 2, 1);
			line* test2 = get2CircleLine(A, B);
			Assert::IsNull(test2);
		}
	};
}
