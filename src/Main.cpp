#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Parser.h"
#include "EasingCurve.h"

std::vector<std::string> ReadFile(const std::string& filename)
{
    std::cout << "Reading input from file \"" << filename << "\".\n";
    std::ifstream inFile{ filename };

    if (!inFile)
    {
        std::cerr << "Failed to open file \"" << filename << "\" for reading.\n";
        return {};
    }

    std::vector<std::string> commands;
    while (inFile)
    {
        std::string strInput;
        std::getline(inFile, strInput);
        
        if(!strInput.empty())
            commands.emplace_back(strInput);
    }

    inFile.close();
    return commands;
}

int main()
{
    std::string testFile = "..\\input\\a.txt";
    std::vector<std::string> commands = ReadFile(testFile);
    ValidationCode returnCode;

    EasingCurve* activeCurve = nullptr;
    for (auto command : commands)
    {
        std::vector<Parameter> parsedParams = ParseCommand(command, returnCode);
        std::cout << "Command validation for \"" << command << "\" returned code: " << (int)returnCode << "\n";

        switch (returnCode)
        {
        case ValidationCode::VALID_QUERY:
            if (activeCurve != nullptr)
            {
                float t = stof(parsedParams.front().second);
                auto ans = activeCurve->Query(t);
                std::cout << ans;
            }
            break;

        case ValidationCode::VALID_CURVE:
            CurveParameters curveParams{};
            for (auto param : parsedParams)
            {
                if (param.first == "x_t0")
                {
                    curveParams.x_t0 = stoi(param.second);
                }
                else if (param.first == "x_t0")
                {
                    curveParams.x_t0 = stoi(param.second);
                }
                else if (param.first == "x_tmax")
                {
                    curveParams.x_tmax = stoi(param.second);
                }
                else if (param.first == "duration")
                {
                    curveParams.duration = stoi(param.second);
                }
                else if (param.first == "Linear")
                {
                    curveParams.type = CurveType::LINEAR;
                }
                else if (param.first == "InQuad")
                {
                    curveParams.type = CurveType::INQUAD;
                }
                else if (param.first == "OutQuad")
                {
                    curveParams.type = CurveType::OUTQUAD;
                }
                else if (param.first == "InOutQuad")
                {
                    curveParams.type = CurveType::INOUTQUAD;
                }
            }

            activeCurve = EasingCurve::Create(curveParams);
            break;
        }
    }
}
