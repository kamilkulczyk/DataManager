#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Record.h"
#include "DynamicRecord.h"

#include<vector>
#include <memory>
#include<map>

class DatabaseManager
{
public:
	std::map<int, std::unique_ptr<Record>> records;
	std::map<std::string, std::vector<std::string>> recordSchemas;

	DatabaseManager() = default;

	void Add(const std::string& type, const std::string& name, const std::vector<std::string>& properties);

	Record* Get(int id);

	bool Delete(int id);

	void DefineNewType(const std::string& typeName, const std::vector<std::string>& fields);

	void ListTypes() const;

	void ListAllRecords() const;

	void SaveToFile(const std::string& fileName) const;

	void LoadFromFile(const std::string& fileName);
};

#endif