#include "AddExecutor.h"

AddExecutor::AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details)
{
	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;

	//a local copy of entry list for undo using
	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

void AddExecutor::execute() throw (string)
{
	bool isCalendarEntry = false;

	if (_details == "")
	{
		throw string ("Cannot add an empty entry\n");
	}

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