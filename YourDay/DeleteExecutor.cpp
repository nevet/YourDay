#include "DeleteExecutor.h"

DeleteExecutor::DeleteExecutor(vector<string>* entryList, string details)
{
	_entryList = entryList;
	_details = details;

	_undoEntryList = *entryList;
}

void DeleteExecutor::execute()
{
	int index;
	
	vector<string>::iterator position;
	
	index=extractIndex(_details);
	if(index > _entryList->size())
	{
		throw string ("index is larger than list size\n");
	}
	else 
	{
		position = _entryList->begin() + index - 1;
		_entryList->erase(position);
		
		status = DELETE_S;
	}
}

void DeleteExecutor::undo()
{
	*_entryList = _undoEntryList;
}