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
	
	index=atoi(_details.c_str());
	if(index>_entryList->size())
	{
		status = DELETE_F;
	}
	else 
	{
		position=_entryList->begin()+index-1;
		_entryList->erase(position);
		
		status = DELETE_S;
	}
}

void DeleteExecutor::undo()
{
	*_entryList = _undoEntryList;
}