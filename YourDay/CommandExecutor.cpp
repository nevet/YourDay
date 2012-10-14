/**
* CommandExecutor is to be accessed in the FunctionHandler class
* CommandExecutor is used to manipulate the entry list passed in by the FunctionHandler class regarding
* to the type of command specified by FunctionHandler
* The types of command are:
*		Add		: add an entry to the event list
*		Delete	: delete an entry from the event list
*		Edit	: edit an entry in the event list
*		Search	: search for an entry containing a keyword in the event list
* It has a public API executeCommand to do the logic tasks to manipulate the entry list
* and the APIs to get and clear status signal
*/
#include <assert.h>
#include "CommandExecutor.h"

void CommandExecutor::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

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
	clearStatus();
}

Signal CommandExecutor::getStatus()
{
	return status;
}

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