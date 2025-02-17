#include "DatabaseManager.h"

#include <fstream>

Record* DatabaseManager::Get(int id)
{
	auto it = records.find(id);
	if (it != records.end())
		return it->second.get();
	return nullptr;
}

void DatabaseManager::Add(const std::string& type, const std::string& name, const std::vector<std::string>& properties)
{
	if (recordSchemas.find(type) == recordSchemas.end())
	{
		std::cerr << "Error: Record type not defined.\n";
		return;
	}

	auto record = std::make_unique<DynamicRecord>(name, type, properties);
	records[record->getId()] = std::move(record);
}


bool DatabaseManager::Delete(int id)
{
	auto it = records.find(id);
	if (it == records.end())
		return false;
	records.erase(it);
	return true;
}

void DatabaseManager::DefineNewType(const std::string& typeName, const std::vector<std::string>& fields)
{
	if (recordSchemas.find(typeName) != recordSchemas.end())
	{
		std::cerr << "Type already exists!\n";
		return;
	}

	recordSchemas[typeName] = fields;
	std::cout << "New record type '" << typeName << "' defined successfully!\n";
}

void DatabaseManager::ListTypes() const {
	std::cout << "Available Record Types:\n";
	for (const auto& pair : recordSchemas) {
		std::cout << "- " << pair.first << " (";
		for (const auto& field : pair.second) {
			std::cout << field << " ";
		}
		std::cout << ")\n";
	}
}

void DatabaseManager::ListAllRecords() const
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

void DatabaseManager::SaveToFile(const std::string& fileName) const
{
	std::ofstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file for writing.\n";
		return;
	}

	for (const auto& pair : records)
	{
		int id = pair.first;
		const std::unique_ptr<Record>& record = pair.second;
		file << record->toString();
	}

	file.close();
	std::cout << "Records successfully saved to " << fileName << std::endl;
}

void DatabaseManager::LoadFromFile(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file for reading.\n";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string type, name, value;
		int id;
		std::vector<std::string> properties;

		std::getline(ss, type, ';');
		std::getline(ss, name, ';');

		if (recordSchemas.find(type) == recordSchemas.end()) {
			std::cerr << "Error: Undefined record type '" << type << "'. Skipping...\n";
			continue;
		}

		while (std::getline(ss, value, ';')) {
			properties.push_back(value);
		}

		Add(type, name, properties);
	}

	file.close();
	std::cout << "Records successfully loaded from " << fileName << std::endl;
}

