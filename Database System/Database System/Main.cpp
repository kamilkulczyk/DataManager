#include <iostream>
#include "DatabaseManager.h"
#include "CommandParser.h"
#include "TerminalInterface.h"

int main()
{
    DatabaseManager* manager = new DatabaseManager();
    TerminalInterface::getInstance(manager)->start();
 
    delete manager;

    return 0;
}
