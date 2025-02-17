#ifndef DYNAMICRECORD_H
#define DYNAMICRECORD_H

#include "Record.h"
#include <vector>

class DynamicRecord : public Record {
public:
    DynamicRecord(const std::string& name, const std::string& recordType, const std::vector<std::string>& properties)
        : Record(name, recordType, properties) {
    }

    void display() override {
        std::cout << "ID: " << getId() << ", Type: " << recordType << ", Name: " << name << std::endl;
        for (size_t i = 0; i < properties.size(); ++i) {
            std::cout << "Property " << i + 1 << ": " << properties[i] << std::endl;
        }
    }
};

#endif
