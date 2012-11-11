#include<cassert>

#include "Executor.h"

//@author A0088455R

Executor::Executor()
{
	status = CLEAR;
}

const int Executor::INDEX_BLOCK_LOCATION		= 1;  
const int Executor::DESCRIPTION_BLOCK_LOCATION	= 2;
const int Executor::LOCATION_BLOCK_LOCATION		= 3;
const int Executor::TIME_BLOCK_LOCATION			= 4;
const int Executor::DATE_BLOCK_LOCATION			= 5;
const int Executor::PRIORITY_BLOCK_LOCATION		= 6;
const int Executor::NO_INDEX_IN_DESCRIPTION		= -1;

int Executor :: findBlockIndex(string details, int blockLocation)
{
	assert(details!="");

	//block counter will be used to count the number of # occurences
	int blockCounter = 0;
	int index;
	//this loop will iterate through the string and stops when the block
	//location is found
	for (index = 0; index<details.size(); index++)
	{
		if (details[index] == '#')
		{
			blockCounter++;
		}
		if (blockCounter == blockLocation)
		{
			break;
		}
	}
	return index;
}

string Executor :: extractField(string details, int startLocation)
{
	assert(details!="");

	int index = startLocation;
	string extracted = "";
	// this loop will extract characters by characters of the field between
	// 2 '#'s
	while (details[++index] != '#')
	{
		extracted += details[index];
	}
	return extracted;
}

int Executor :: extractIndex(string details)
{
	assert(details!="");

	string tempIndex = "";
	int index;
	int indexLocation;
	indexLocation = findBlockIndex(details, INDEX_BLOCK_LOCATION);
	tempIndex = extractField(details, indexLocation);
	index = atoi(tempIndex.c_str());
	return index;
}

string Executor :: extractDescription(string details)
{
	assert(details!="");
	string tempDescription = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, DESCRIPTION_BLOCK_LOCATION);
	tempDescription = extractField(details, indexLocation);
	return tempDescription;
}

string Executor :: extractLocation(string details)
{
	assert(details!="");
	string tempLocation = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, LOCATION_BLOCK_LOCATION);
	tempLocation = extractField(details, indexLocation);
	return tempLocation;
}

string Executor :: extractTime(string details)
{
	assert(details!="");
	string tempTime = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, TIME_BLOCK_LOCATION);
	tempTime = extractField(details, indexLocation);
	return tempTime;
}

string Executor :: extractDate(string details)
{
	assert(details!="");
	string tempDate = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, DATE_BLOCK_LOCATION);
	tempDate = extractField(details, indexLocation);
	return tempDate;
}

string Executor :: extractPriority(string details)
{
	assert(details!="");
	string priority = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, PRIORITY_BLOCK_LOCATION);
	priority = extractField(details, indexLocation);
	return priority;
}

int Executor::extractDay(string date)
{
	assert(date!="");
	int year, month, day;

	assert(sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year)==3);
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return day;
}

int Executor::extractMonth(string date)
{
	assert(date!="");
	int year, month, day;

	assert(sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year)==3);
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return month;
}

int Executor::extractYear(string date)
{
	assert(date!="");
	int year, month, day;
	
	assert(sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year)==3);

	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return year;
}

int Executor::extractHour(string time)
{
	int hour, minute;
	sscanf(time.c_str(), "%d:%d", &hour, &minute);
	return hour;
}

int Executor::extractMinute(string time)
{
	int hour, minute;
	sscanf(time.c_str(), "%d:%d", &hour, &minute);
	return minute;
}

void Executor::splitStartEndTime(string* start, string* end, string timeRange)
{
	*start=timeRange.substr(0,5);
	*end=timeRange.substr(6,5);
}

//@author A0091734
int Executor :: extractIndexFromDescription(string description)
{
	assert(description!="");
	char * cstr;
	char * firstWord;
	int length;
	int index;
	bool isAllNumber = true;


	int size=description.size();
	cstr = new char [description.size()+1];
	strcpy (cstr, description.c_str());	

	// cstr now contains a c-string copy of description
	firstWord=strtok (cstr," ");

	string mystring(firstWord);
	length = mystring.size();

	for(int i=0;i<length;i++)
	{
		if(!(firstWord[i]<='9' && firstWord[i]>='0'))
		{
			isAllNumber = false;
		}
	}
	


	if(isAllNumber)
	{
		index = atoi(firstWord);
		delete[] cstr;  
		return index;
	}
	else
	{
		delete[] cstr;  
		return NO_INDEX_IN_DESCRIPTION;
	}
}

void Executor::execute()
{
}

void Executor::undo()
{
}

Signal Executor::getStatus()
{
	return status;
}