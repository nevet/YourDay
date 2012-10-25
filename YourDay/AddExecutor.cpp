#include "AddExecutor.h"

AddExecutor::AddExecutor(vector<string>* entryList, string details)
{
	_entryList = entryList;
	_details = details;

	//a local copy of entry list for undo using
	_undoEntryList = *entryList;
}

void AddExecutor::execute()
{
	_entryList -> push_back(_details);

	status = ADD_S;
}

void AddExecutor::undo()
{
	*_entryList = _undoEntryList;
}