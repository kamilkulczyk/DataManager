#include "Record.h"

int Record::generalId = 0;

std::string Record::toString() const
{
    std::ostringstream out;
    out << recordType << ";" << id << ";" << name;
    for (const auto& prop : properties)
    {
        out << ";" << prop;
    }
    out << std::endl;
    return out.str();
}