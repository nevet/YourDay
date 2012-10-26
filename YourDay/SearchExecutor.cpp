#include "SearchExecutor.h"

SearchExecutor::SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details)
{
	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;
	_matchedEntryList = matchedEntryList;

	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
	_undoMatchedEntryList = *matchedEntryList;
}

void SearchExecutor::execute()
{
	_matchedEntryList->clear();

	string curRaw;
	string lowerCasecurRaw ;
	string decodedEntry;
	string kewWord = extractDescription(_details);
	string lowerCaseKeyWord = kewWord;
	transform(kewWord.begin(), kewWord.end(), lowerCaseKeyWord.begin(), tolower);

	for(int i = 0; i < _generalEntryList->size(); i++)
	{
		curRaw =_generalEntryList->at(i);
		lowerCasecurRaw = curRaw;
		transform(curRaw.begin(), curRaw.end(), lowerCasecurRaw.begin(), tolower);
		if(std::string::npos != lowerCasecurRaw.find(lowerCaseKeyWord))
		{
			_matchedEntryList->push_back(curRaw);
		}
	}

	for(int i = 0; i < _calendarEntryList->size(); i++)
	{
		curRaw =_calendarEntryList->at(i);
		lowerCasecurRaw = curRaw;
		transform(curRaw.begin(), curRaw.end(), lowerCasecurRaw.begin(), tolower);
		if(std::string::npos != lowerCasecurRaw.find(lowerCaseKeyWord))
		{
			_matchedEntryList->push_back(curRaw);
		}
	}

	if(_matchedEntryList->size() ==  0)
	{
		throw string ("No result matched\n");
	}
}

void SearchExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}