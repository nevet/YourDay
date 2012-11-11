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

//@author A0088455R
/**
* Manipulates the entry string date and returns it in YYYY/MM/DDHH:MM format
* This is done through extraction of each field then reverse the fields using
* os stream
**/
string AddExecutor::manipulateEntryDate(string entry)
{
	assert(entry != "");

	ostringstream dateContender;
	ostringstream monthContender;
	ostringstream output;

	string timeRange = extractTime(entry);
	string entryDate = extractDate(entry);

	int entryDay = extractDay(entryDate);
	int entryMonth = extractMonth(entryDate);
	int entryYear = extractYear(entryDate);	

	if (entryDay < 10)
	{
		dateContender<<"0"<<entryDay;
	}
	else
	{
		dateContender<<entryDay;
	}
	
	if (entryMonth < 10)
	{
		monthContender<<"0"<<entryMonth;
	}
	else
	{
		monthContender<<entryMonth;
	}

	output<<entryYear<<monthContender.str()<<dateContender.str()<<timeRange;
	return output.str();
}

/**
* Checks whether the entry is earlier than entry 2.
* first the entries will be manipulated then checked
**/
bool AddExecutor::isEarlier(string &entry1, string &entry2)
{
	assert(entry1 != "");
	assert(entry2 != "");

	string entry1Date = manipulateEntryDate(entry1);
	string entry2Date = manipulateEntryDate(entry2);

	

	return entry1Date < entry2Date;
}
/**
* This method calls the binary search functions to find the correct index
* where does the user's encoded input should be added
* if the list size is 0, it simply returns 0 (the first index)
**/
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

/**
* This is the implementation of the binary search
* The algorithm is an optimized version of binary search
* The implementation is using the nonrecursive version to support larger
* batch processing
**/
int AddExecutor::binarySearch(vector<string>* _entryList, string key, int imin, int imax)
{
	assert(_entryList != NULL);
	assert(key != "");

	int imid;

	//First we find the mid point
	imid = (imin + imax) / 2;

	//To have a correct index, we ned to add 1 if imin+imax is not
	// dividable by 2
	if ((( imin + imax) % 2 ) == 1)
	{
		imid += 1;
	}
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

		//Repeat the imid division process
		imid = (imin + imax) / 2;
		if ((( imin + imax) % 2 ) == 1)
		{
			imid += 1;
		}
	}
	return imid;
}

void AddExecutor::shiftList(vector<string>* _entryList, int index)
{
		int i;
		int listSize = _entryList->size();

		for (i = (listSize - 1); i > index; i--)
		{
			(*_entryList)[i] = (*_entryList)[i-1];
		}
}
/**
* Adds the encoded input to the correct position
* if the vector size is 0, we simly push the input
* other wise we shift the entry from index position by 1
* then adds the string at the position
**/
void AddExecutor::addToPosition(vector<string>* _entryList, int index, string input)
{
	assert(_entryList != NULL);
	assert(input != "");
	int listSize = _entryList->size();

	if (listSize == 0)
	{
		_entryList -> push_back(input);
	}
	else
	{
		string dummyString = "";
		shiftList(_entryList, index);
		_entryList -> push_back(dummyString);
		
		(*_entryList)[index] = input;
	}
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