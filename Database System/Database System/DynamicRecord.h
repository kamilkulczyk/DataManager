#ifndef DYNAMICRECORD_H
#define DYNAMICRECORD_H

#include "Record.h"
#include "RecordSchema.h"
#include <vector>

class DynamicRecord : public Record
{
public:
    const RecordSchema* schemaPtr;

    DynamicRecord(
        int assignedId,
        const std::string& recordType,
        const std::vector<std::string>& properties,
        const RecordSchema* schemaPtr)
        : Record(assignedId, recordType, properties), schemaPtr(schemaPtr) { }

    void display() override;
};

#endif
