#include "pch.h"
#include "CppUnitTest.h"
#include "../Curves.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QueryTests
{
	TEST_CLASS(LinearCurveTests)
	{
	public:

		CurveType curveType = CurveType::LINEAR;
		int x_t0 = 100;
		int x_tmax = 200;
		float duration = 1;
		CurveParameters curveParams{ curveType, x_t0, x_tmax, duration };

		TEST_METHOD(Linear_100_200_1_t02)
		{
			float t = 0.2;

			int expectedResult = 120;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(Linear_100_200_1_t05)
		{
			float t = 0.5;

			int expectedResult = 150;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(Linear_100_200_1_t05)
		{
			float t = 1.0;

			int expectedResult = 200;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}
	};
}
