#include "DeleteExecutor.h"
#include <cassert>

DeleteExecutor::DeleteExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details, Signal focusingField)
{
	assert(details!="");
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(focusingField!=GENERAL || focusingField!=CALENDAR);

	_undoEnable = true;

	switch (focusingField)
	{
		case GENERAL:
			_focusingEntryList = generalEntryList;
			_undoFocusingEntryList = *generalEntryList;
			
			break;
		
		case CALENDAR:
			_focusingEntryList = calendarEntryList;
			_undoFocusingEntryList = *calendarEntryList;
			
			break;
			
		default:
			break;
	}

	_details = details;
}

void DeleteExecutor::execute()
{
	int index;
	
	vector<string>::iterator position;
	
	index=extractIndex(_details);

	if(index < 0)
	{
		throw string ("index is not existing\n");
	}
	else if(index >= (_focusingEntryList->size()))
	{
		throw string ("index is larger than list size\n");
	}
	else 
	{
		position = _focusingEntryList->begin() + index ;
		_focusingEntryList->erase(position);
	
	}
}

void DeleteExecutor::undo()
{
	*_focusingEntryList = _undoFocusingEntryList;
}