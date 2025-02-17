#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "CommandType.h"
#include <string>
#include <unordered_map>

class CommandParser {
public:
    static CommandType ParseCommand(const std::string& command) {
        static const std::unordered_map<std::string, CommandType> commandMap = {
            {"add", CommandType::ADD},
            {"delete", CommandType::DELETE},
            {"define", CommandType::DEFINE},
            {"list_types", CommandType::LISTTYPES},
            {"list_records", CommandType::LISTRECORDS},
            {"save", CommandType::SAVE},
            {"load", CommandType::LOAD},
            {"exit", CommandType::EXIT}
        };

        auto it = commandMap.find(command);
        return (it != commandMap.end()) ? it->second : CommandType::UNKNOWN;
    }
};

#endif
