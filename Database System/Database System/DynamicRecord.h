#ifndef DYNAMICRECORD_H
#define DYNAMICRECORD_H

#include "Record.h"
#include <vector>

class DynamicRecord : public Record
{
public:
    DynamicRecord(int assignedId, const std::string& name, const std::string& recordType, const std::vector<std::string>& properties)
        : Record(assignedId, name, recordType, properties) { }

    void display() override
    {
        std::cout << "ID: " << getId() << ", Type: " << recordType << ", Name: " << name << std::endl;
        for (size_t i = 0; i < properties.size(); ++i)
            std::cout << "Property " << i + 1 << ": " << properties[i] << std::endl;
        if (!primaryKeys.empty())
        {
            std::cout << "Primary Keys: ";
            for (const auto& pk : primaryKeys)
                std::cout << pk << " ";
            std::cout << std::endl;
        }
        if (!foreignKeys.empty())
        {
            std::cout << "Foreign Keys: ";
            for (const auto& fk : foreignKeys)
                std::cout << fk.first << " -> " << fk.second << " ";
            std::cout << std::endl;
        }
    }
};

#endif
