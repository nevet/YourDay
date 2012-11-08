#include<cassert>

#include "SearchExecutor.h"

//@author A0088455R
const int SearchExecutor::MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int SearchExecutor::PERFECT_MATCH = 3;
const int SearchExecutor::MEDIOCORE_MATCH = 1;

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
	int hour, minute;

	return sscanf(time.c_str(), "%d:%d", &hour, &minute) == 2;
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
	int hour, minute;

	bool flag = true;

	sscanf(time.c_str(), "%d:%d", &hour, &minute);

	if (hour > 23 || hour < 0)
	{
		flag = false;
	} else
	if (minute > 59 || minute < 0)
	{
		flag = false;
	}

	return flag;
}
//@author A0088455R
int SearchExecutor::extractDay(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return day;
}

int SearchExecutor::extractMonth(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return month;
}

int SearchExecutor::extractHour(string time)
{
	int hour, minute;
	sscanf(time.c_str(), "%d:%d", &hour, &minute);
	return hour;
}

int SearchExecutor::extractMinute(string time)
{
	int hour, minute;
	sscanf(time.c_str(), "%d:%d", &hour, &minute);
	return minute;
}

void SearchExecutor::splitStartEndTime(string* start, string* end, string timeRange)
{
	*start=timeRange.substr(0,5);
	*end=timeRange.substr(6,5);
}

void SearchExecutor::initializeVectors(int totalSize, vector<int>* score, vector<int>* rank)
{
	int i;
	score->clear();
	rank->clear();
	for(i=0;i<totalSize;i++)
	{
		score->push_back(0);
		rank->push_back(0);
	}
	
}

void SearchExecutor::searchDate(string keyword, vector<int>* rank)
{
	assert(keyword!="");

	int i;

	string toBeCompared;
	int entryDay;
	int keywordDay;
	int entryMonth;
	int keywordMonth;

	int _generalSize = _generalEntryList->size();
	int _calendarSize = _calendarEntryList->size();
	for (i=0;i<_calendarSize;i++)
	{
		toBeCompared= extractDate((*_calendarEntryList)[i]);

		//same month score = 1
		//same day score = 1
		//same year score = 0
		// same date score =3
		entryDay = extractDay(toBeCompared);
		entryMonth = extractMonth(toBeCompared);
		keywordDay = extractDay(keyword);
		keywordMonth = extractMonth(keyword);
		if (entryDay == keywordDay)
		{
			if (entryMonth == keywordMonth)
			{
				(*rank)[i] +=3;
			}
			else
			{
				(*rank)[i] +=1;
			}
		}
		else if (entryMonth == keywordMonth)
		{
			(*rank)[i] += 1;
		}

	}
}

void SearchExecutor::searchTime(string keyword, vector<int>* rank)
{
	assert(keyword!="");

	int i;

	string entryTimeRange;
	string entryStartTime;
	string entryEndTime;

	int entryStartHour;
	int entryEndHour;
	int entryStartMinute;
	int entryEndMinute;
	int keywordHour;
	int keywordMinute;

	int _generalSize = _generalEntryList->size();
	int _calendarSize = _calendarEntryList->size();

	for (i=0;i<_calendarSize;i++)
	{
		entryTimeRange=extractTime((*_calendarEntryList)[i]);
		splitStartEndTime(&entryStartTime, &entryEndTime, entryTimeRange);
		entryStartHour = extractHour(entryStartTime);
		entryEndHour = extractHour(entryEndTime);
		entryStartMinute = extractMinute(entryStartTime);
		entryEndMinute = extractMinute(entryEndTime);
		keywordHour = extractHour(keyword);
		keywordMinute = extractMinute(keyword);
		if (entryStartHour == keywordHour)
		{
			if (entryStartMinute <= keywordMinute)
			{
				(*rank)[i] += 3;
			}
			else
			{
				(*rank)[i] += 1;
			}
		}
		else if (entryEndHour == keywordHour)
		{
			if (entryEndMinute >= keywordMinute)
			{
				(*rank)[i] += 3;
			}
			else
			{
				(*rank)[i] += 1;
			}
		}
		else if ((entryStartHour < keywordHour) && (entryEndHour > keywordHour))
		{
			(*rank)[i] += 3;
		}
	}
	
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
	
	initializeVectors(totalEntries,&score,&rank);
	
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