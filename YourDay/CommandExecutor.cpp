#include <assert.h>
#include "CommandExecutor.h"

//set the status signal of command execution process
void CommandExecutor::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

//add an entry as a pure string to the entry list vector
void CommandExecutor::addEntry(vector<string> * entryList, string detail)
{
	if (detail == "")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		entryList -> push_back(detail);
	}
}

void CommandExecutor::deleteEntry(vector<string>* entryList, string entry)
{
}

void CommandExecutor::searchEntry(vector<string>* entryList, string keyWord)
{
}

void CommandExecutor::updateEntry(vector<string>* entryList, string entry)
{
}

CommandExecutor::CommandExecutor()
{
	//clearStatus();
}

//get the command execution process status
Signal CommandExecutor::getStatus()
{
	return status;
}

//clear the command execusion status to default CLEAR signal
void CommandExecutor::clearStatus()
{
	status = CLEAR;
}

void CommandExecutor::executeCommand(vector <string> * entryList, Signal type, string detail)
{
	switch (type)
	{
	case ADD_COMMAND:
		{
			addEntry(entryList, detail);
			break;
		}
	case DELETE_COMMAND:
		{
			deleteEntry(entryList, detail);
			break;
		}
	case SEARCH_COMMAND:
		{
			searchEntry(entryList, detail);
			break;
		}
	case EDIT_COMMAND:
		{
			updateEntry(entryList, detail);
			break;
		}
	default:
		{
			setStatus(COMMAND_E);
			break;
		}
	}
}

CommandExecutor::~CommandExecutor()
{
}