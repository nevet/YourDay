#include <assert.h>
#include "CommandExecutor.h"

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
		setStatus(ADD_S);
	}
}

void CommandExecutor::deleteEntry(vector<string>* entryList, string number)
{
	int index;
	
	vector<string>::iterator position;
	
	if ( number =="")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		index=atoi(number.c_str());
		if(index>entryList->size())
			setStatus(DELETE_F);
		else 
		{
			position=entryList->begin()+index-1;
			entryList->erase(position);
			setStatus(DELETE_S);
		}
	}
}

void CommandExecutor::searchEntry(vector<string>* entryList, string keyWord, vector<string>* matchedEntryList)
{
	string temp;

	matchedEntryList->clear();
	if ( keyWord =="")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		for(int i=0;i<entryList->size();i++)
		{
			temp=entryList->at(i);
			if(std::string::npos != temp.find(keyWord))
			{
				matchedEntryList->push_back(temp);
			}
		}
	}
}

void CommandExecutor::updateEntry(vector<string>* entryList, string entry)
{
}

CommandExecutor::CommandExecutor()
{
	//clearStatus();
}

Signal CommandExecutor::getStatus()
{
	return status;
}

void CommandExecutor::clearStatus()
{
	status = CLEAR;
}

void CommandExecutor::executeCommand(vector <string> * entryList, Signal type, string detail, vector<string>* result)
{
	vector <string> tempVector;
	vector <string> * matchedEntryList;
	string temp;
	int choice;
	char enterEater;

	matchedEntryList=&tempVector;

	switch (type)
	{
	case ADD_COMMAND:
		{
			addEntry(entryList, detail);
			break;
		}
	case DELETE_COMMAND:
		{
			deleteEntry(entryList,detail);
			break;
		}
	case SEARCH_COMMAND:
		{
			searchEntry(entryList, detail, result);
			break;
		}
	case EDIT_COMMAND:
		{
			updateEntry(entryList, detail);
			break;
		}
	case EXIT_COMMAND:
		{
			setStatus(EXIT_COMMAND);
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