#ifndef COMPANYRECORD_H
#define COMPANYRECORD_H

#include "Record.h"

class CompanyRecord : public Record
{
public:
    CompanyRecord(const std::string& name, const std::string& city, const std::string& category)
        : Record(name, "Company", { city, category }) {
    }

    void display() override
    {
        std::cout << "ID: " << getId() << ", Name: " << name << std::endl;
        std::cout << "City: " << properties[0] << ", Category: " << properties[1] << std::endl;
    }
};


#endif