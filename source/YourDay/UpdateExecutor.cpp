#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details)
{
	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;

	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

void UpdateExecutor::execute()
{
}

void UpdateExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
}