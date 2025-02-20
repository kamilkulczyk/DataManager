#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Record.h"
#include "DynamicRecord.h"
#include "RecordSchema.h"

#include<vector>
#include <memory>
#include<map>

class DatabaseManager
{
public:
	std::map<int, std::unique_ptr<Record>> records;
	std::map<std::string, RecordSchema> recordSchemas;

	DatabaseManager() = default;

	bool addRecord(int it, const std::string& type, const std::string& name, const std::vector<std::string>& properties);

	Record* getRecord(int id);

	bool deleteRecord(int id);

	void defineNewType(
		const std::string& typeName,
		const std::vector<std::string>& fields,
		const std::vector<std::string>& primaryKeys,
		const std::vector<ForeignKey>& foreignKeys);

	void listAllTypes() const;

	void listAllRecords() const;

	bool saveToFile(const std::string& fileName) const;

	void loadFromFile(const std::string& fileName);

	bool validatePrimaryKey(const std::string& typeName, const std::vector<std::string>& values);
	
	bool validateForeignKey(const std::string& typeName, const std::vector<std::string>& values);

	bool checkPrimaryKeyExists(const std::string& type, const std::string& pkField, const std::string& pkValue);

	bool checkForeignKeyExists(const ForeignKey& fk, const std::string& fkValue);
};

#endif