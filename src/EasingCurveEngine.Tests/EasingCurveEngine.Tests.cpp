#include "pch.h"
#include "CppUnitTest.h"
#include "..\Validator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EasingCurveEngineTests
{
	TEST_CLASS(ValidatorTests)
	{
	public:

		TEST_METHOD(ValidCurveDefinition)
		{
			std::string command = "Linear, x_t0 = 100, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::VALID_CURVE;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(TooManyParameters)
		{
			std::string command = "Linear, x_t0 = 100, x_tmax = 200, duration = 1, blah = 300";
			int expectedCode = (int)ValidationCode::TOO_MANY_PARAMS;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(MissingParameters)
		{
			std::string command = "Linear, x_t0 = 100, x_tmax = 200";
			int expectedCode = (int)ValidationCode::MISSING_PARAMS;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(IncorrectParameters)
		{
			std::string command = "Linear, Not = 100, A = 200, Parameter = 1";
			int expectedCode = (int)ValidationCode::MISSING_PARAMS;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(BadValuesString)
		{
			std::string command = "Linear, x_t0 = bad, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::BAD_VALUE;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(BadValuesFloat)
		{
			std::string command = "Linear, x_t0 = 5.5, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::BAD_VALUE;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(ValidQuery)
		{
			std::string command = "1.0";
			int expectedCode = (int)ValidationCode::VALID_QUERY;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(InvalidQuery)
		{
			std::string command = "1.0.0";
			int expectedCode = (int)ValidationCode::BAD_QUERY;
			int actualCode = (int)ValidateCommand(command);

			Assert::AreEqual(expectedCode, actualCode);
		}
	};
}
