#include "DatabaseManager.h"

#include <fstream>

Record* DatabaseManager::getRecord(int id)
{
	auto it = records.find(id);
	if (it != records.end())
		return it->second.get();
	return nullptr;
}

bool DatabaseManager::addRecord(int id, const std::string& type, const std::string& name, const std::vector<std::string>& properties)
{
	if (recordSchemas.find(type) == recordSchemas.end())
	{
		std::cerr << "Error: Record type not defined.\n";
		return false;
	}

	const RecordSchema& schema = recordSchemas[type];

	for (const auto& pk : schema.primaryKeys)
	{
		auto it = std::find(schema.fields.begin(), schema.fields.end(), pk);
		if (it != schema.fields.end())
		{
			int pkIndex = std::distance(schema.fields.begin(), it);
			const std::string& pkValue = properties[pkIndex];

			if (checkPrimaryKeyExists(type, pk, pkValue))
			{
				std::cerr << "Error: Duplicate primary key '" << pkValue << "' detected.\n";
				return false;
			}
		}
	}

	for (const auto& fk : schema.foreignKeys)
	{
		auto it = std::find(schema.fields.begin(), schema.fields.end(), fk.fieldName);
		if (it != schema.fields.end())
		{
			int fkIndex = std::distance(schema.fields.begin(), it);
			const std::string& fkValue = properties[fkIndex];

			if (!checkForeignKeyExists(fk, fkValue))
			{
				std::cerr << "Error: Foreign key constraint failed. '" << fkValue
					<< "' not found in referenced record type '" << fk.referencedType << "'.\n";
				return false;
			}
		}
	}

	auto record = std::make_unique<DynamicRecord>(id, name, type, properties);
	records[record->getId()] = std::move(record);

	return true;
}

bool DatabaseManager::deleteRecord(int id)
{
	auto it = records.find(id);
	if (it == records.end())
		return false;
	records.erase(it);
	return true;
}

void DatabaseManager::defineNewType(
	const std::string& typeName,
	const std::vector<std::string>& fields,
	const std::vector<std::string>& primaryKeys,
	const std::vector<ForeignKey>& foreignKeys)
{
	if (recordSchemas.find(typeName) != recordSchemas.end())
	{
		std::cerr << "Error: Record type '" << typeName << "' already exists.\n";
		return;
	}

	recordSchemas[typeName] = { typeName, fields, primaryKeys, foreignKeys };
}

void DatabaseManager::listAllTypes() const
{
	std::cout << "Available Record Types:\n";
	for (const auto& pair : recordSchemas)
	{
		const RecordSchema& schema = pair.second;
		std::cout << "- " << schema.typeName << " (";

		for (size_t i = 0; i < schema.fields.size(); i++)
		{
			std::cout << schema.fields[i];
			if (i < schema.fields.size() - 1) std::cout << ", ";
		}

		std::cout << ")\n";

		if (!schema.primaryKeys.empty())
		{
			std::cout << "  PK: ";
			for (size_t i = 0; i < schema.primaryKeys.size(); i++)
			{
				std::cout << schema.primaryKeys[i];
				if (i < schema.primaryKeys.size() - 1) std::cout << ", ";
			}
			std::cout << "\n";
		}

		if (!schema.foreignKeys.empty())
		{
			std::cout << "  FK: ";
			for (const auto& fk : schema.foreignKeys)
				std::cout << fk.fieldName << " → " << fk.referencedType << "." << fk.referencedField << "; ";
			std::cout << "\n";
		}
	}
}


void DatabaseManager::listAllRecords() const
{
	if (records.empty())
	{
		std::cout << "Database is empty." << std::endl;
		return;
	}

	for (const auto& pair : records)
	{
		int id = pair.first;
		const std::unique_ptr<Record>& record = pair.second;
		std::cout << "-----------------" << std::endl;
		record->display();
	}
	std::cout << "-----------------" << std::endl;
}

bool DatabaseManager::saveToFile(const std::string& fileName) const
{
	std::ofstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file for writing.\n";
		return false;
	}

	for (const auto& pair : records)
	{
		int id = pair.first;
		const std::unique_ptr<Record>& record = pair.second;
		file << record->toString();
	}

	file.close();
	return true;
}

void DatabaseManager::loadFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file for reading.\n";
		return;
	}

	int maxId = 0;
	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string type, name, value;
		int id;
		std::vector<std::string> properties;

		ss >> id;
		ss.ignore(1, ';');
		std::getline(ss, type, ';');
		std::getline(ss, name, ';');

		if (recordSchemas.find(type) == recordSchemas.end())
		{
			std::cerr << "Error: Undefined record type '" << type << "'. Skipping...\n";
			continue;
		}

		while (std::getline(ss, value, ';'))
			properties.push_back(value);

		addRecord(id, type, name, properties);
	}

	file.close();
	std::cout << "Records successfully loaded from " << fileName << std::endl;
}

bool DatabaseManager::validatePrimaryKey(const std::string& typeName, const std::vector<std::string>& values)
{
	const auto& schema = recordSchemas[typeName];

	for (const auto& pair : records) 
	{
		if (pair.second->getRecordType() == typeName)
		{
			for (size_t i = 0; i < schema.primaryKeys.size(); i++)
			{
				if (pair.second->getProperties()[i] == values[i])
				{
					std::cerr << "Error: Duplicate Primary Key for " << typeName << ".\n";
					return false;
				}
			}
		}
	}
	return true;
}

bool DatabaseManager::validateForeignKey(const std::string& typeName, const std::vector<std::string>& values)
{
	const auto& schema = recordSchemas[typeName];

	for (const auto& fk : schema.foreignKeys)
	{
		bool found = false;
		for (const auto& pair : records)
		{
			if (pair.second->getRecordType() == fk.referencedType)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			std::cerr << "Error: Foreign Key reference to missing " << fk.referencedType << ".\n";
			return false;
		}
	}
	return true;
}

bool DatabaseManager::checkPrimaryKeyExists(const std::string& type, const std::string& pkField, const std::string& pkValue)
{
	for (const auto& pair : records)
	{
		if (pair.second->getRecordType() == type)
		{
			if (pkField == "id" && std::to_string(pair.first) == pkValue)
				return true;
			const auto& props = pair.second->getProperties();
			const auto& fields = recordSchemas[type].fields;

			auto it = std::find(fields.begin(), fields.end(), pkField);
			if (it != fields.end() && props[std::distance(fields.begin(), it)] == pkValue)
				return true;
		}
	}
	return false;
}


bool DatabaseManager::checkForeignKeyExists(const ForeignKey& fk, const std::string& fkValue)
{
	for (const auto& pair : records)
	{
		if (pair.second->getRecordType() == fk.referencedType)
		{
			if (fk.referencedField == "id" && std::to_string(pair.first) == fkValue)
				return true;
			const auto& props = pair.second->getProperties();
			const auto& fields = recordSchemas[fk.referencedType].fields;

			auto it = std::find(fields.begin(), fields.end(), fk.referencedField);
			if (it != fields.end() && props[std::distance(fields.begin(), it)] == fkValue)
				return true;
		}
	}
	return false;
}
