#include "Executor.h"

Executor::Executor()
{
	status = CLEAR;
}

int Executor :: findBlockIndex(string details, int blockLocation)
{
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
	string tempDescription = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, DESCRIPTION_BLOCK_LOCATION);
	tempDescription = extractField(details, indexLocation);
	return tempDescription;
}

string Executor :: extractLocation(string details)
{
	string tempLocation = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, LOCATION_BLOCK_LOCATION);
	tempLocation = extractField(details, indexLocation);
	return tempLocation;
}

string Executor :: extractTime(string details)
{
	string tempTime = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, TIME_BLOCK_LOCATION);
	tempTime = extractField(details, indexLocation);
	return tempTime;
}

string Executor :: extractDate(string details)
{
	string tempDate = "";
	int indexLocation;
	indexLocation = findBlockIndex(details, DATE_BLOCK_LOCATION);
	tempDate = extractField(details, indexLocation);
	return tempDate;
}

int Executor :: extractPriority(string details)
{
	string tempPriority = "";
	int priority;
	int indexLocation;
	indexLocation = findBlockIndex(details, PRIORITY_BLOCK_LOCATION);
	tempPriority = extractField(details, indexLocation);
	priority= atoi(tempPriority.c_str());
	return priority;
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