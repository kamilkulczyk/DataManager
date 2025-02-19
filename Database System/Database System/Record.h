#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

class Record
{
protected:
    static int generalId;
    int id;
    std::string name;
    std::string recordType;
    std::vector<std::string> properties;
    std::vector<std::string> primaryKeys;
    std::map<std::string, int> foreignKeys;

public:
    Record(int assignedId, const std::string& name, const std::string& type, std::vector<std::string> props = {})
        : id(assignedId > 0 ? assignedId : ++generalId), name(name), recordType(type), properties(std::move(props))
    {
        generalId = generalId > assignedId ? generalId : assignedId;
    }

    virtual void display() = 0;
    virtual std::string toString() const;

    int getId() const { return id; }
    std::string getRecordType() const { return recordType; }
    const std::vector<std::string>& getProperties() const { return properties; }
    const std::vector<std::string>& getPrimaryKeys() const { return primaryKeys; }
    const std::map<std::string, int>& getForeignKeys() const { return foreignKeys; }

    void setPrimaryKeys(const std::vector<std::string>& keys) { primaryKeys = keys; }
    void setForeignKeys(const std::string& field, int referenceId) { foreignKeys[field] = referenceId; }

    virtual ~Record() = default;
};

#endif
