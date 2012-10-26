#include "DeleteExecutor.h"

DeleteExecutor::DeleteExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details)
{
	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;

	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

void DeleteExecutor::execute()
{
	int index;
	
	vector<string>::iterator position;
	
	index=extractIndex(_details);

	if(index < 1)
	{
		throw string ("index is not existing\n");
	}
	else if(index > (_generalEntryList->size() + _calendarEntryList->size()))
	{
		throw string ("index is larger than list size\n");
	}
	else 
	{
		if(index <= _generalEntryList->size())
		{
			position = _generalEntryList->begin() + index - 1;
			_generalEntryList->erase(position);
		}
		else 
		{
			position = _calendarEntryList->begin() + index - _generalEntryList->size() -1;
			_calendarEntryList->erase(position);
		}
		status = DELETE_S;
	}
}

void DeleteExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
}