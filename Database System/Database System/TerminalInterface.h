#ifndef TERMINALINTERFACE_H
#define TERMINALINTERFACE_H

#include "CommandParser.h"
#include "DatabaseManager.h"

#include <string>

class TerminalInterface {
public:
    TerminalInterface(const TerminalInterface&) = delete;
    TerminalInterface& operator=(const TerminalInterface&) = delete;

    static TerminalInterface* getInstance(DatabaseManager* manager);
    void start();

private:
    TerminalInterface(DatabaseManager* manager);
    ~TerminalInterface() = default;

    DatabaseManager* dbManager;

    static TerminalInterface* instance;
};

#endif
