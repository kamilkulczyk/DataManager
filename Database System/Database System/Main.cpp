#include <iostream>
#include "DatabaseManager.h"
#include "CommandParser.h"

int main()
{
    DatabaseManager* manager = new DatabaseManager();
    std::string command;

    while (true)
    {
        std::cout << "\nCommands: define, add, delete, list_types, list_records, save, load, exit\n";
        std::cout << "Enter command: ";
        std::cin >> command;

        CommandType commandType = CommandParser::ParseCommand(command);

        switch (commandType)
        {
            case CommandType::DEFINE:
            {
                std::string typeName;
                int numFields;
                std::vector<std::string> fields;

                std::cout << "Enter new record type name: ";
                std::cin >> typeName;
                std::cout << "How many fields? ";
                std::cin >> numFields;

                for (int i = 0; i < numFields; i++)
                {
                    std::string fieldName;
                    std::cout << "Enter field " << i + 1 << ": ";
                    std::cin >> fieldName;
                    fields.push_back(fieldName);
                }

                manager->DefineNewType(typeName, fields);
                break;
            }
            case CommandType::ADD:
            {
                std::string type, name;
                std::vector<std::string> values;

                std::cout << "Enter record type: ";
                std::cin >> type;

                if (manager->recordSchemas.find(type) == manager->recordSchemas.end())
                {
                    std::cerr << "Type not found!\n";
                    continue;
                }

                std::cout << "Enter name: ";
                std::cin >> name;

                for (const auto& field : manager->recordSchemas[type])
                {
                    std::string value;
                    std::cout << "Enter value for " << field << ": ";
                    std::cin.ignore();
                    std::getline(std::cin, value);
                    values.push_back(value);
                }

                manager->Add(type, name, values);
                std::cout << "Record added!\n";
                break;
            }
            case CommandType::LISTTYPES:
            {
                manager->ListTypes();
                break;
            }
            case CommandType::LISTRECORDS:
            {
                manager->ListAllRecords();
                break;
            }
            case CommandType::SAVE:
            {
                std::string filePath;
                std::cout << "Enter file path: ";
                std::cin >> filePath;
                manager->SaveToFile(filePath);
                break;
            }
            case CommandType::LOAD:
            {
                std::string filePath;
                std::cout << "Enter file path: ";
                std::cin >> filePath;
                manager->LoadFromFile(filePath);
                break;
            }
            case CommandType::EXIT:
                std::cout << "Exiting program...\n";
                return 0;
            default:
                std::cout << "Unknown command!\n";
                break;
        }
    }
 
    delete manager;

    return 0;
}
