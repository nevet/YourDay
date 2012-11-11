#include "AddExecutor.h"
#include <cassert>
#include <sstream>
#include <algorithm>

AddExecutor::AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* resultList, string details)
{
	assert(details!="");
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_resultList = resultList;
	_details = details;

	//a local copy of entry list for undo using
	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

int AddExecutor::searchIndex(vector<string>* _entryList, string input)
{
	assert(_entryList != NULL);
	assert(input != "");
	int listSize = _entryList->size();

	if (listSize == 0)
	{
		return 0;
	}
	else
	{
		return binarySearch(_entryList, input, 0, listSize-1);
	}
}

int AddExecutor::binarySearch(vector<string>* _entryList, string key, int imin, int imax)
{
	assert(_entryList != NULL);
	assert(key != "");
	int imid = (imin + imax) / 2;
	while (imax >= imin)
	{
		if (isEarlier((*_entryList)[imid],key))
		{
			imin = imid + 1;
		}
		else if (isEarlier(key,(*_entryList)[imid]))
		{
			imax = imid - 1;
		}
		else
		{
			return imid;
		}
		imid = (imin + imax) / 2;
	}
	return imid;
}

void AddExecutor::addToPosition(vector<string>* _entryList, int index, string input)
{
	assert(_entryList != NULL);
	assert(input != "");
	int listSize = _entryList->size();
	int i;

	if (listSize == 0)
	{
		_entryList -> push_back(input);
	}
	else
	{
		string dummyString = "";
		_entryList -> push_back(dummyString);
		listSize = _entryList->size();
		for (i = (listSize - 1); i > index; i--)
		{
			(*_entryList)[i] = (*_entryList)[i-1];
		}
		(*_entryList)[index+1] = input;
	}
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
	string timeRange1 = extractTime(entry1);
	string timeRange2 = extractTime(entry2);

	string entryDate1 = extractDate(entry1);
	string entryDate2 = extractDate(entry2);

	int entryDay1 = extractDay(entryDate1);
	int entryDay2 = extractDay(entryDate2);

	int entryMonth1 = extractMonth(entryDate1);
	int entryMonth2 = extractMonth(entryDate2);

	int entryYear1 = extractYear(entryDate2);
	int entryYear2 = extractYear(entryDate2);

	ostringstream dateContender1;
	ostringstream dateContender2;

	ostringstream monthContender1;
	ostringstream monthContender2;

	if (entryDay1 < 10)
	{
		dateContender1<<"0"<<entryDay1;
	}
	else
	{
		dateContender1<<entryDay1;
	}
	if (entryDay2 < 10)
	{
		dateContender2<<"0"<<entryDay2;
	}
	else
	{
		dateContender2<<entryDay2;
	}
	if (entryMonth1 < 10)
	{
		monthContender1<<"0"<<entryMonth1;
	}
	else
	{
		monthContender1<<entryMonth1;
	}
	if (entryMonth2 < 10)
	{
		monthContender2<<"0"<<entryMonth2;
	}
	else
	{
		monthContender2<<entryMonth2;
	}

	ostringstream os1;
	ostringstream os2;

	os1<<entryYear1<<monthContender1.str()<<dateContender1.str()<<timeRange1;
	os2<<entryYear2<<monthContender2.str()<<dateContender2.str()<<timeRange2;

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
		_generalEntryList->push_back(_details);
		_resultList->push_back(_details);
	}
	else
	{
		int index = searchIndex(_calendarEntryList, _details);
		addToPosition(_calendarEntryList, index, _details);
		addToPosition(_resultList, index, _details);
	}
}

void AddExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
	
}