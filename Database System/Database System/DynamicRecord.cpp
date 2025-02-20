#include "DynamicRecord.h"

void DynamicRecord::display()
{
    std::cout << "ID: " << getId() << ", Type: " << recordType << std::endl;

    if (schemaPtr != nullptr)
    {
        for (size_t i = 0; i < properties.size() && i < schemaPtr->fields.size(); ++i)
            std::cout << schemaPtr->fields[i] << ": " << properties[i] << std::endl;
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
    else
        std::cerr << "Errod: Missing schema.\n";
}
