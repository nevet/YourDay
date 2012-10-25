#include "Executor.h"

Executor::Executor()
{
	status = CLEAR;
}

int Executor::extractIndex(string details)
{
	int blockCounter = 0;
	int i;
	string tempIndex="";
	int index;
	for (i=0;i<details.size();i++)
	{
		if (details[i]=='#')
		{
			blockCounter++;
		}
		if (blockCounter==INDEX_BLOCK_LOCATION)
		{
			break;
		}
	}
	while (details[++i]!='#')
	{
		tempIndex+=details[i];
	}
	index = atoi(tempIndex.c_str());
	return index;
}

string Executor::extractDescription(string details)
{
	int blockCounter = 0;
	int i;
	string tempDescription="";
	for (i=0;i<details.size();i++)
	{
		if (details[i]=='#')
		{
			blockCounter++;
		}
		if (blockCounter==DESCRIPTION_BLOCK_LOCATION)
		{
			break;
		}
	}
	while (details[++i]!='#')
	{
		tempDescription+=details[i];
	}
	return tempDescription;
}

string Executor::extractLocation(string details)
{
	int blockCounter = 0;
	int i;
	string tempLocation="";
	for (i=0;i<details.size();i++)
	{
		if (details[i]=='#')
		{
			blockCounter++;
		}
		if (blockCounter==LOCATION_BLOCK_LOCATION)
		{
			break;
		}
	}
	while (details[++i]!='#')
	{
		tempLocation+=details[i];
	}
	return tempLocation;
}

string Executor::extractTime(string details)
{
	int blockCounter = 0;
	int i;
	string tempTime="";
	for (i=0;i<details.size();i++)
	{
		if (details[i]=='#')
		{
			blockCounter++;
		}
		if (blockCounter==TIME_BLOCK_LOCATION)
		{
			break;
		}
	}
	while (details[++i]!='#')
	{
		tempTime+=details[i];
	}
	return tempTime;
}

string Executor::extractDate(string details)
{
	int blockCounter = 0;
	int i;
	string tempDate="";
	for (i=0;i<details.size();i++)
	{
		if (details[i]=='#')
		{
			blockCounter++;
		}
		if (blockCounter==DATE_BLOCK_LOCATION)
		{
			break;
		}
	}
	while (details[++i]!='#')
	{
		tempDate+=details[i];
	}
	return tempDate;
}

int Executor::extractPriority(string details)
{
	int blockCounter = 0;
	int i;
	string tempPriority="";
	int priority;
	for (i=0;i<details.size();i++)
	{
		if (details[i]=='#')
		{
			blockCounter++;
		}
		if (blockCounter==PRIORITY_BLOCK_LOCATION)
		{
			break;
		}
	}
	while (details[++i]!='#')
	{
		tempPriority+=details[i];
	}
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