#include "AddExecutor.h"
#include <cassert>
#include <sstream>

AddExecutor::AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details)
{
	assert(details!="");
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;

	//a local copy of entry list for undo using
	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

void AddExecutor::quickSort(vector<string> &entryList, int low, int high)
{
	int left, right;
	string entry;
	if (low >= high) return;

	left = low;
	right = high;
	entry = entryList[(low + high) /2];

	while ( left <= right )
	{
		while (isEarlier(entryList[left],entry))
		{
			left ++;
		}
		while (isEarlier(entry,entryList[right]))
		{
			right --;
		}

		if (left <= right)
		{
			swap(entryList[left], entryList[right]);
			left ++;
			right --;
		}
	}

	quickSort(entryList, low, right);
	quickSort(entryList, left, high);
}

int AddExecutor::extractDay(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return day;
}

int AddExecutor::extractMonth(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return month;
}

int AddExecutor::extractYear(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return year;
}

bool AddExecutor::isEarlier(string &entry1, string &entry2)
{
	string timeRange1;
	string timeRange2;
	timeRange1=extractTime(entry1);
	timeRange2=extractTime(entry2);
	string entryDate1;
	string entryDate2;
	entryDate1=extractDate(entry1);
	entryDate2=extractDate(entry2);
	int entryDay1 = extractDay(entryDate1);
	int entryMonth1 = extractMonth(entryDate1);
	int entryYear1 = extractYear(entryDate2);
	int entryDay2 = extractDay(entryDate2);
	int entryMonth2 = extractMonth(entryDate2);
	int entryYear2 = extractYear(entryDate2);
	ostringstream os1;
	ostringstream os2;
	os1<<entryYear1<<entryMonth1<<entryDay1<<timeRange1;
	os2<<entryYear2<<entryMonth2<<entryDay2<<timeRange2;
	return os1.str() < os2.str();
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