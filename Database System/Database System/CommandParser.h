#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "CommandType.h"
#include <string>
#include <sstream>
#include <unordered_map>

class CommandParser
{
public:
    static const std::unordered_map<std::string, CommandType> commandMap;
    static CommandType ParseCommand(const std::string& command)
    {
        auto it = commandMap.find(command);
        return (it != commandMap.end()) ? it->second : CommandType::UNKNOWN;
    }

    static inline const std::string& getCommandString()
    {
        static std::string commandString = []() -> std::string
        {
            std::ostringstream oss;
            for (auto it = CommandParser::commandMap.begin(); it != CommandParser::commandMap.end(); ++it)
            {
                oss << it->first;
                if (std::next(it) != CommandParser::commandMap.end())
                    oss << ", ";
            }
            return oss.str();
        }();
        return commandString;
    }
};

#endif
