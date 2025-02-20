# Database System

## Overview
This is a C++-based database management system that allows users to create, store, and manage different types of records dynamically. It can be saved and loaded from the file. As for now it uses quirky structure to store schema and data. All the data is stored as text.

The project demonstrates an understanding of object-oriented programming, dynamic data structures, and smart pointers.
This is a for fun project only.

## Features
- Supports multiple dynamic record types.
- Uses `unique_ptr` for efficient memory management.
- Provides file persistence for saving and loading records.
- Implements command-line interaction to manage records dynamically.

## Usage
**Some of the available commands:**
- `add [record_type] [properties]` - Adds a new record.
- `delete [id]` - Removes a record by ID.
- `list_records` - Displays all records.
- `save [filename]` - Saves records to a file.
- `load [filename]` - Loads records from a file.

Example:
```sh
add Person 1 John Doe Developer
add Company 2 TechCorp New York IT
save database.txt
load database.txt
list_records
```

## Future Improvements
Here are some features that can be implemented next:
- Relationships Between Records: Allow records to reference other records (e.g., Employees linked to Companies).
- SQL-like Query System: Implement commands like `SELECT`, `UPDATE`, `WHERE` for searching and filtering.
- Database Indexing: Improve search performance with indexing.
- Undo/Redo Feature: Keep track of changes and allow reverting operations.
- Statistics & Reporting: Generate reports with record statistics.
- Networking Support: Turn it into a client-server model for multi-user access.
