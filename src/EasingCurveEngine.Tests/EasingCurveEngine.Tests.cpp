#include "pch.h"
#include "CppUnitTest.h"
#include "..\Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EasingCurveEngineTests
{
	TEST_CLASS(ValidatorTests)
	{
	public:

		TEST_METHOD(ValidCurveDefinition)
		{
			ValidationCode returnCode;
			std::string command = "Linear, x_t0 = 100, x_tmax = 200, duration = 1";
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int expectedCode = (int)ValidationCode::VALID_CURVE;
			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(ValidCurveDefinitionDifferentOrder)
		{
			ValidationCode returnCode;
			std::string command = "x_t0 = 100, x_tmax = 200, Linear, duration = 1";
			int expectedCode = (int)ValidationCode::VALID_CURVE;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(TooManyParameters)
		{
			ValidationCode returnCode;
			std::string command = "Linear, x_t0 = 100, x_tmax = 200, duration = 1, blah = 300";
			int expectedCode = (int)ValidationCode::TOO_MANY_PARAMS;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(MissingParameters)
		{
			ValidationCode returnCode;
			std::string command = "Linear, x_t0 = 100, x_tmax = 200";
			int expectedCode = (int)ValidationCode::MISSING_PARAMS;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(MissingParametersAllx_t0)
		{
			ValidationCode returnCode;
			std::string command = "Linear, x_t0 = 100, x_t0 = 200, x_t0 = 300";
			int expectedCode = (int)ValidationCode::MISSING_PARAMS;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(IncorrectParameters)
		{
			ValidationCode returnCode;
			std::string command = "Linear, Not = 100, A = 200, Parameter = 1";
			int expectedCode = (int)ValidationCode::BAD_PARAM;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(BadParam)
		{
			ValidationCode returnCode;
			std::string command = "Linear, Not = 100, A = 200, Parameter = 1";
			int expectedCode = (int)ValidationCode::BAD_PARAM;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(BadValuesString)
		{
			ValidationCode returnCode;
			std::string command = "Linear, x_t0 = bad, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::BAD_VALUE;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(BadValuesFloat)
		{
			ValidationCode returnCode;
			std::string command = "Linear, x_t0 = 5.5, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::BAD_VALUE;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(MissingCurveType)
		{
			ValidationCode returnCode;
			std::string command = "x_t0 = 100, x_t0 = 100, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::MISSING_CURVETYPE;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(BadCurveType)
		{
			ValidationCode returnCode;
			std::string command = "NotACurve, x_t0 = 100, x_tmax = 200, duration = 1";
			int expectedCode = (int)ValidationCode::BAD_CURVETYPE;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(ValidQuery)
		{
			ValidationCode returnCode;
			std::string command = "1.0";
			int expectedCode = (int)ValidationCode::VALID_QUERY;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(InvalidQuery)
		{
			ValidationCode returnCode;
			std::string command = "1.0.0";
			int expectedCode = (int)ValidationCode::BAD_QUERY;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}

		TEST_METHOD(EmptyCommand)
		{
			ValidationCode returnCode;
			std::string command = "";
			int expectedCode = (int)ValidationCode::EMTPY_COMMAND;
			std::vector<Parameter> returnedParams = ParseCommand(command, returnCode);

			int actualCode = (int)returnCode;
			Assert::AreEqual(expectedCode, actualCode);
		}
	};
}
