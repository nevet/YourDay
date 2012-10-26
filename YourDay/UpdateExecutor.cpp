#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor(vector<string>* entryList, string details)
{
	_entryList = entryList;
	_details = details;

	_undoEntryList = *entryList;
}

void UpdateExecutor::execute()
{
}

void UpdateExecutor::undo()
{
	*_entryList = _undoEntryList;
}