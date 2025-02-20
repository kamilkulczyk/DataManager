#include "TerminalInterface.h"
#include <iostream>
#include <limits>

TerminalInterface* TerminalInterface::instance = nullptr;

TerminalInterface::TerminalInterface(DatabaseManager* manager)
    : dbManager(manager)
{ 
    if (!manager)
        throw std::runtime_error("DatabaseManager pointer cannot be null");
}

TerminalInterface* TerminalInterface::getInstance(DatabaseManager* manager)
{
    if (!instance)
        instance = new TerminalInterface(manager);
    return instance;
}

void TerminalInterface::start()
{
    std::string command;

    while (true)
    {
        std::cout << "\nCommands: " << CommandParser::getCommandString() << "\n";
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
            std::vector<std::string> primaryKeys;
            std::vector<ForeignKey> foreignKeys;

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

                char choice;
                std::cout << "Is this field a Primary Key (P), Foreign Key (F), or None (N)? ";
                std::cin >> choice;

                if (choice == 'P' || choice == 'p')
                    primaryKeys.push_back(fieldName);
                else if (choice == 'F' || choice == 'f')
                {
                    std::string referencedType, referencedField;
                    std::cout << "Referenced record type for " << fieldName << ": ";
                    std::cin >> referencedType;
                    std::cout << "Referenced field in " << referencedType << ": ";
                    std::cin >> referencedField;

                    foreignKeys.push_back({ fieldName, referencedType, referencedField });
                }
            }

            dbManager->defineNewType(typeName, fields, primaryKeys, foreignKeys);
            std::cout << "Record type '" << typeName << "' defined successfully!\n";

            break;
        }
        case CommandType::ADD:
        {
            std::string type;
            std::vector<std::string> values;

            std::cout << "Enter record type: ";
            std::cin >> type;

            if (dbManager->recordSchemas.find(type) == dbManager->recordSchemas.end())
            {
                std::cerr << "Error: Record type not found!\n";
                break;
            }

            const RecordSchema& schema = dbManager->recordSchemas[type];

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (const auto& field : schema.fields)
            {
                std::string value;
                std::cout << "Enter value for " << field << ": ";

                std::getline(std::cin, value);
                values.push_back(value);
            }

            if (dbManager->addRecord(0, type, values))
                std::cout << "Record added successfully!\n";
            else
                std::cerr << "Failed to add record due to validation errors.\n";

            break;
        }
        case CommandType::LISTTYPES:
        {
            dbManager->listAllTypes();
            break;
        }
        case CommandType::LISTRECORDS:
        {
            dbManager->listAllRecords();
            break;
        }
        case CommandType::SAVE:
        {
            std::string filePath;
            std::cout << "Enter file path: ";
            std::cin >> filePath;
            if (dbManager->saveToFile(filePath))
                std::cout << "Records successfully saved to " << filePath << std::endl;
            break;
        }
        case CommandType::LOAD:
        {
            std::string filePath;
            std::cout << "Enter file path: ";
            std::cin >> filePath;
            dbManager->loadFromFile(filePath);
            break;
        }
        case CommandType::EXIT:
            std::cout << "Exiting program...\n";
            return;
        default:
            std::cout << "Unknown command!\n";
            break;
        }
    }
}