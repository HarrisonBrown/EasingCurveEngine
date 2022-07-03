#include "pch.h"
#include "CppUnitTest.h"
#include "../Curves.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QueryTests
{
	TEST_CLASS(LinearCurveTests_100_200_1)
	{
	public:

		CurveType curveType = CurveType::LINEAR;
		int x_t0 = 100;
		int x_tmax = 200;
		float duration = 1;
		CurveParameters curveParams{ curveType, x_t0, x_tmax, duration };

		TEST_METHOD(T0_2)
		{
			float t = 0.2;

			int expectedResult = 120;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T0_5)
		{
			float t = 0.5;

			int expectedResult = 150;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T1_0)
		{
			float t = 1.0;

			int expectedResult = 200;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}
	};

	TEST_CLASS(InQuadCurveTests_100_200_1)
	{
	public:

		CurveType curveType = CurveType::INQUAD;
		int x_t0 = 100;
		int x_tmax = 200;
		float duration = 1;
		CurveParameters curveParams{ curveType, x_t0, x_tmax, duration };

		TEST_METHOD(T0_2)
		{
			float t = 0.2;

			int expectedResult = 104;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T0_5)
		{
			float t = 0.5;

			int expectedResult = 125;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T1_0)
		{
			float t = 1.0;

			int expectedResult = 200;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}
	};

	TEST_CLASS(OutQuadCurveTests_100_200_1)
	{
	public:

		CurveType curveType = CurveType::OUTQUAD;
		int x_t0 = 100;
		int x_tmax = 200;
		float duration = 1;
		CurveParameters curveParams{ curveType, x_t0, x_tmax, duration };

		TEST_METHOD(T0_2)
		{
			float t = 0.2;

			int expectedResult = 136;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T0_5)
		{
			float t = 0.5;

			int expectedResult = 175;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T1)
		{
			float t = 1.0;

			int expectedResult = 200;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}
	};

	TEST_CLASS(InOutQuadCurveTests_100_200_1)
	{
	public:

		CurveType curveType = CurveType::INOUTQUAD;
		int x_t0 = 100;
		int x_tmax = 200;
		float duration = 1;
		CurveParameters curveParams{ curveType, x_t0, x_tmax, duration };

		TEST_METHOD(T0_2)
		{
			float t = 0.2;

			int expectedResult = 102;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T0_5)
		{
			float t = 0.5;

			int expectedResult = 113;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T0_7)
		{
			float t = 0.7;

			int expectedResult = 182;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}

		TEST_METHOD(T1_0)
		{
			float t = 1.0;

			int expectedResult = 200;
			int actualResult = EasingCurve::Create(curveParams)->Query(t);
			Assert::AreEqual(expectedResult, actualResult);
		}
	};
}
