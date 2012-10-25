#include "AddExecutor.h"

AddExecutor::AddExecutor(vector<string>* calendarEntryList, vector<string>* generalEntryList, string details)
{
	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;

	//a local copy of entry list for undo using
	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

void AddExecutor::execute()
{
	bool isCalendarEntry = false;
	if (extractDate(_details) == "")
	{
		_generalEntryList -> push_back(_details);
	}
	else
	{
		_calendarEntryList -> push_back(_details);
	}

	status = ADD_S;
}

void AddExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
}