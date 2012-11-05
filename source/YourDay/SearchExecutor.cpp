#include<cassert>

#include "SearchExecutor.h"

const int SearchExecutor::MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

string SearchExecutor::splitFirstTerm(string* mString)
{
	stringstream tempHolder;
	string firstTerm;
	char spaceEater;
	tempHolder<<*mString;
	tempHolder>>firstTerm;
	(*mString).erase(0,firstTerm.size()+1);
	return firstTerm;
}

void SearchExecutor::formatSearchResult(int index, string result, string* formattedResult)
{
	assert(result!="");

	ostringstream ostring;
	ostring << "#" << index << result.substr(1,result.size()-1);

	*formattedResult = ostring.str();
}

bool SearchExecutor::isLeap(int year)
{
	bool flag = false;
	
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
		{
			flag = true;
		}
	} else
	{
		if (year % 4 == 0)
		{
			flag = true;
		}
	}

	return flag;
}

bool SearchExecutor::isDate(string date)
{
	int year, month, day;

	return sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) == 3;
}

bool SearchExecutor::isTime(string time)
{
	int h, m;

	return sscanf(time.c_str(), "%d:%d", &h, &m) == 2;
}


bool SearchExecutor::isLogicDate(string date)
{
	assert(date!="");
	int year, month, day;

	bool flag = true;

	//extract year, month and day from the string
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	if (year > 9999 || year < 1000)
	{
		flag = false;
	} else
	if (month > 12 || month < 1)
	{
		flag = false;
	} else
	if (day < 1)
	{
		flag = false;
	} else
	{
		if (!isLeap(year))
		{
			if (day > MONTH[month - 1])
			{
				flag = false;
			}
		} else
		if (month == 2 && day > 29)
		{
			flag = false;
		}
	}

	return flag;
}

bool SearchExecutor::isLogicTime(string time)
{
	assert(time!="");
	int h1, m1;

	bool flag = true;

	sscanf(time.c_str(), "%d:%d", &h1, &m1);

	if (h1 > 23 || h1 < 0)
	{
		flag = false;
	} else
	if (m1 > 59 || m1 < 0)
	{
		flag = false;
	}

	return flag;
}

void SearchExecutor::initializeVectors(vector<int>* score, vector<int>* rank)
{
}
void SearchExecutor::searchDate(string key, vector<int>* rank)
{
}
void SearchExecutor::searchTime(string key, vector<int>* rank)
{
}

void SearchExecutor::searchText(string key, vector<int>* rank)
{
}

SearchExecutor::SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details)
{
	assert(details!="");
	assert(matchedEntryList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

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
	string currentKey;
	vector<int> rank;
	vector<int> score;
	
	int weight = 1;
	int totalEntries = _generalEntryList->size() + _calendarEntryList->size();
	
	rank.clear();
	score.clear();
	
	//while we can still extract keywords from the input
	while (!_details.empty())
	{
		currentKey = splitFirstTerm(&_details);
		
		if (isDate(currentKey))
		{
			if (isLogicDate(currentKey))
			{
				searchDate(currentKey, &rank);
			} else
			{
				throw string ("date error\n");
				//log.writeException("date error");
			}
		} else
		if (isTime(currentKey))
		{
			if (isLogicTime(currentKey))
			{
				searchTime(currentKey, &rank);
			} else
			{
				throw string ("time error\n");
				log.writeException("time error");
			}
		} else
		{
			searchText(currentKey, &rank);
		}
		
		for (int i = 0; i < totalEntries; i++)
		{
			score[i] += rank[i] * weight;
		}
		
		weight ++;
	}
}

void SearchExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}