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

	bool Add(int it, const std::string& type, const std::string& name, const std::vector<std::string>& properties);

	Record* Get(int id);

	bool Delete(int id);

	void DefineNewType(
		const std::string& typeName,
		const std::vector<std::string>& fields,
		const std::vector<std::string>& primaryKeys,
		const std::vector<ForeignKey>& foreignKeys);

	void ListTypes() const;

	void ListAllRecords() const;

	bool SaveToFile(const std::string& fileName) const;

	void LoadFromFile(const std::string& fileName);

	bool ValidatePrimaryKey(const std::string& typeName, const std::vector<std::string>& values);
	
	bool ValidateForeignKey(const std::string& typeName, const std::vector<std::string>& values);

	bool CheckPrimaryKeyExists(const std::string& type, const std::string& pkField, const std::string& pkValue);

	bool CheckForeignKeyExists(const ForeignKey& fk, const std::string& fkValue);
};

#endif