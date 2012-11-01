#include <cassert>

#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details)
{
	assert(details!="");
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

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