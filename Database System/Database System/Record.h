#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class Record
{
protected:
    static int generalId;
    int id;
    std::string name;
    std::string recordType;
    std::vector<std::string> properties;

public:
    Record(const std::string& name, const std::string& type, std::vector<std::string> props = {})
        : id(++generalId), name(name), recordType(type), properties(std::move(props)) {}

    virtual void display() = 0;
    virtual std::string toString() const;

    int getId() const { return id; }
    std::string getRecordType() const { return recordType; }
    const std::vector<std::string>& getProperties() const { return properties; }

    virtual ~Record() = default;
};

#endif
