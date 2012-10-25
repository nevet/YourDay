#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor(vector<string>* entryList, string details)
{
	_entryList = entryList;
	_details = details;

	_undoEntryList = *entryList;
}

void UpdateExecutor::execute()
{/*
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
	}	*/
}

void UpdateExecutor::undo()
{
	*_entryList = _undoEntryList;
}