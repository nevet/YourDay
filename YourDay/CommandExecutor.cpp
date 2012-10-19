#include <assert.h>
#include <algorithm>
#include <sstream>
#include "CommandExecutor.h"

void CommandExecutor::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

void CommandExecutor::updateRaw(string* raw, string* updateDetails)
{
	string updatedRaw = "";
	string oldDetail;
	string newDetail;
	string tempRaw = *raw + "#";
	string tempUpdateRaw = *updateDetails + "#";
	int tempRawLength = tempRaw.length();
	int tempUpdateLength = tempUpdateRaw.length();
	int i = 0;					//This iteration is used to trace tempRaw
	int j = 0;					//This iteration is used to trace tempUpdateRaw	

	while (i < tempRawLength && j<tempUpdateLength)
	{
		oldDetail = "";
		newDetail = "";
		while (tempRaw[i] != '#' && i < tempRawLength)
		{
			oldDetail += tempRaw[i];
			i++;
		}
		while (tempUpdateRaw[j]!= '#' && j<tempUpdateLength)
		{
			newDetail += tempUpdateRaw[j];
			j++;
		}

		if (newDetail == "")
		{
			updatedRaw += oldDetail;
		}
		else
		{
			updatedRaw += newDetail;
		}

		updatedRaw += "#";

		i++;
		j++;
	}
	
	updatedRaw = updatedRaw.substr(0, updatedRaw.size()-1);
	*raw = updatedRaw;
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
	matchedEntryList->clear();

	if ( keyWord =="")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		string curRaw;
		string lowerCaseKeyWord = keyWord;
		transform(keyWord.begin(), keyWord.end(), lowerCaseKeyWord.begin(), tolower);

		for(int i=0;i<entryList->size();i++)
		{
			curRaw=entryList->at(i);
			if(std::string::npos != curRaw.find(lowerCaseKeyWord))
			{
				matchedEntryList->push_back(curRaw);
			}
		}
	}
}

void CommandExecutor::updateEntry(vector<string>* entryList, string updateDetails)
{
	istringstream input(updateDetails);
	int index;
	string number;
	char space;
	string updateString;

	input >> number;
	input.get(space);
	getline(input, updateString);

	if ( number =="" || updateString == "")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		index=atoi(number.c_str());
		updateRaw(&entryList->at(index-1), &updateString);
	}	
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