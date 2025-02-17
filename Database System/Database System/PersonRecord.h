#ifndef PERSONRECORD_H
#define PERSONRECORD_H

#include "Record.h"

class PersonRecord : public Record
{
public:
    PersonRecord(const std::string& name, const std::string& fullName, const std::string& role)
    : Record(name, "Person", { fullName, role }) {}

    void display() override
    {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
        std::cout << "Full Name: " << properties[0] << ", Role: " << properties[1] << std::endl;
    }
};

#endif
