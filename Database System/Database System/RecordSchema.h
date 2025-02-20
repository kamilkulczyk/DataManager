#ifndef RECORDSCHEMA_H
#define RECORDSCHEMA_H

#include <string>
#include <vector>

struct ForeignKey
{
    std::string fieldName;
    std::string referencedType;
    std::string referencedField;
};

struct RecordSchema
{
    std::string typeName;
    std::vector<std::string> fields;
    std::vector<std::string> primaryKeys;
    std::vector<ForeignKey> foreignKeys;

    RecordSchema() = default;

    RecordSchema(
        const std::string& name,
        const std::vector<std::string>& userFields,
        const std::vector<std::string>& userPrimaryKeys,
        const std::vector<ForeignKey>& userForeignKeys)
        : typeName(name), fields(userFields), primaryKeys(userPrimaryKeys), foreignKeys(userForeignKeys)
    {
        // Every record has id and it is always a primary key.
        if (std::find(this->primaryKeys.begin(), this->primaryKeys.end(), "id") == this->primaryKeys.end())
            this->primaryKeys.insert(this->primaryKeys.begin(), "id");
    }
};

#endif