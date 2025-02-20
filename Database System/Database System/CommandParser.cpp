#include "CommandParser.h"

const std::unordered_map<std::string, CommandType> CommandParser::commandMap = {
            {"add", CommandType::ADD},
            {"delete", CommandType::DELETE},
            {"define", CommandType::DEFINE},
            {"list_types", CommandType::LISTTYPES},
            {"list_records", CommandType::LISTRECORDS},
            {"save", CommandType::SAVE},
            {"load", CommandType::LOAD},
            {"exit", CommandType::EXIT}
};