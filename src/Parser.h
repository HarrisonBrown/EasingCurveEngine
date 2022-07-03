#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Parser.h"
#include <set>

enum class ValidationCode
{
    VALID_CURVE = 0,
    VALID_QUERY,
    EMTPY_COMMAND,
    MISSING_PARAMS,
    TOO_MANY_PARAMS,
    MISSING_CURVETYPE,
    BAD_PARAM,
    BAD_VALUE,
    BAD_CURVETYPE,
    BAD_QUERY,
};

using Parameter = std::pair<std::string, std::string>;

std::string curveTypes[4] = { "Linear", "InQuad", "OutQuad", "InOutQuad" };
std::string validParameters[3] = { "x_t0", "x_tmax", "duration" };

bool isFloat(const std::string& str)
{
    if (str.empty())
        return false;

    char* ptr;
    strtof(str.c_str(), &ptr);
    return (*ptr) == '\0';
}

bool isInt(const std::string& str)
{
    if (str.empty())
        return false;

    char* ptr;
    strtol(str.c_str(), &ptr, 10);
    return (*ptr) == '\0';
}

std::vector<Parameter> ParseCommand(std::string command, ValidationCode& returnCode)
{
    std::vector<Parameter> returnParams;

    if (command.empty())
    {
        returnCode = ValidationCode::EMTPY_COMMAND;
        return {};
    }

    std::size_t commaPos = command.find(',');
    if (commaPos == std::string::npos)
    {
        // No comma found, is this a valid query (i.e. a float)?
        if (isFloat(command))
        {
            returnCode = ValidationCode::VALID_QUERY;
            returnParams.emplace_back(Parameter{ "Query", command });
        }
        else
        {
            returnCode = ValidationCode::BAD_QUERY;
            return {};
        }
    }
    else
    {
        // Found a comma, is this a valid curve definition?
        // Split string using ',' as a delimiter
        std::vector<std::string> parameters;
        size_t splitPos = 0;
        while ((splitPos = command.find(',')) != std::string::npos)
        {
            parameters.emplace_back(command.substr(0, splitPos));
            command.erase(0, splitPos + 1);
        }
        parameters.emplace_back(command);
        command.clear();


        // Right number of parameters?
        if (parameters.size() != 4)
        {
            returnCode = parameters.size() < 4 ? ValidationCode::MISSING_PARAMS : ValidationCode::TOO_MANY_PARAMS;
            return {};
        }

        // Loop through each parameter found, returning an error code at any necessary point
        int numCurveTypes = 0;
        std::set<std::string> validParametersFound;
        for (auto parameter : parameters)
        {
            parameter.erase(std::remove_if(parameter.begin(), parameter.end(), std::isspace), parameter.end());
            size_t eqPos = parameter.find('=');
            if (eqPos != std::string::npos)
            {
                std::string paramName = parameter.substr(0, eqPos);
                std::string paramValue = parameter.substr(eqPos + 1);
                if (!paramName.empty())
                {
                    bool isValid = false;
                    for (auto validParam : validParameters)
                    {
                        if (paramName == validParam)
                        {
                            validParametersFound.emplace(paramName);
                            returnParams.emplace_back(Parameter{ paramName, paramValue });
                            isValid = true;
                        }
                    }
                    if (!isValid)
                    {
                        returnCode = ValidationCode::BAD_PARAM;
                        return {};
                    }
                }
                else
                {
                    returnCode = ValidationCode::BAD_PARAM;
                    return {};
                }

                if (paramValue.empty() || !isInt(paramValue))
                {
                    returnCode = ValidationCode::BAD_VALUE;
                    return {};
                }
            }
            else
            {
                // No '=', must be curve type
                bool goodType = false;
                for (auto type : curveTypes)
                {
                    if (parameter == type)
                    {
                        goodType = true;
                        returnParams.emplace_back(Parameter{ "CurveType", parameter });
                    }
                }
                if (!goodType)
                {
                    returnCode = ValidationCode::BAD_CURVETYPE;
                    return {};
                }

                numCurveTypes++;
            }
        }
        if (validParametersFound.size() < 3)
        {
            returnCode = ValidationCode::MISSING_PARAMS;
            return {};
        }
        if (numCurveTypes < 1)
        {
            returnCode = ValidationCode::MISSING_CURVETYPE;
            return {};
        }

        // Getting to this point indicates the command is a valid curve definition
        returnCode = ValidationCode::VALID_CURVE;
    }

    return returnParams;
}
