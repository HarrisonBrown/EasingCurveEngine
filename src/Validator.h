#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Validator.h"
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

ValidationCode ValidateCommand(std::string command)
{
    if (command.empty())
        return ValidationCode::EMTPY_COMMAND;

    std::size_t commaPos = command.find(',');
    if (commaPos == std::string::npos)
    {
        // No comma found, is this a valid query (i.e. a float)?
        if (isFloat(command))
            return ValidationCode::VALID_QUERY;
        else
            return ValidationCode::BAD_QUERY;
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
            return parameters.size() < 4 ? ValidationCode::MISSING_PARAMS : ValidationCode::TOO_MANY_PARAMS;
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
                            isValid = true;
                        }
                    }
                    if (!isValid)
                    {
                        return ValidationCode::BAD_PARAM;
                    }
                }
                else
                {
                    return ValidationCode::BAD_PARAM;
                }

                if (paramValue.empty() || !isInt(paramValue))
                {
                    return ValidationCode::BAD_VALUE;
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
                    }
                }
                if (!goodType)
                {
                    return ValidationCode::BAD_CURVETYPE;
                }

                numCurveTypes++;
            }
        }
        if (validParametersFound.size() < 3)
            return ValidationCode::MISSING_PARAMS;
        if (numCurveTypes < 1)
            return ValidationCode::MISSING_CURVETYPE;

        // Getting to this point indicates the command is a valid curve definition
        return ValidationCode::VALID_CURVE;
    }
}
