#include "pch.h"
#include "CppUnitTest.h"
#include"../include/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			struct dot testDot = calculate(0.0, 1.0, 2.0, 3.0);
			Assert::AreEqual(testDot.x, -1.0);
			Assert::AreEqual(testDot.y, 1.0);
		}
	};
}
