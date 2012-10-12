#include <assert.h>
#include "Command.h"

void Command::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

void Command::addEntry(string* detail)
{
	assert(detail != NULL);
	if (*detail == "")
	{
		status = EMPTY_ENTRY_E;
	}
	else
	{
		entryList -> push_back(detail);
	}
}

void Command::deleteEntry(string* entry)
{
}

void Command::searchEntry(string* keyWord)
{
}

void Command::updateEntry(string* entry)
{
}

Command::Command(vector<string*> * inEntryList)
{
	entryList = inEntryList;
	status = CLEAR;
}

Signal Command::getStatus()
{
	return status;
}

void Command::clearStatus()
{
	status = CLEAR;
}

void Command::executeCommand(CommandType type, string* detail)
{
	switch (type)
	{
	case ADD:
		{
			addEntry(detail);
			break;
		}
	case DELETE:
		{
			deleteEntry(detail);
			break;
		}
	case SEARCH:
		{
			searchEntry(detail);
			break;
		}
	case UPDATE:
		{
			updateEntry(detail);
			break;
		}
	default:
		{
			status = COMMAND_E;
			break;
		}
	}
}

Command::~Command()
{
}