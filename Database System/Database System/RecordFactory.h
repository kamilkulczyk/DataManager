#ifndef RECORDFACTORY_H
#define RECORDFACTORY_H

#include "RecordFactoryAbstract.h"
#include "PersonRecord.h"
#include "CompanyRecord.h"

class RecordFactory : public RecordFactoryAbstract
{
public:
    std::unique_ptr<Record> CreateRecord(const std::vector<std::string>& fields)
    {
        if (fields.size() < 3)
            return nullptr;  // Invalid record

        std::string type = fields[0];
        int id = std::stoi(fields[1]);
        std::string name = fields[2];

        if (type == "Person" && fields.size() == 5)
        {
            return std::make_unique<PersonRecord>(name, fields[3], fields[4]);
        }
        else if (type == "Company" && fields.size() == 5)
        {
            return std::make_unique<CompanyRecord>(name, fields[3], fields[4]);
        }

        return nullptr;  // Unknown record type
    }
};

#endif