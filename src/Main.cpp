#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Parser.h"

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

    for (auto command : commands)
    {
        ParseCommand(command, returnCode);
        std::cout << "Command validation for \"" << command << "\" returned code: " << (int)returnCode << "\n";
    }
}
