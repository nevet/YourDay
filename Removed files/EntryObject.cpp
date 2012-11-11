#include <iostream>
#include <string>

#include "EntryObject.h"

using namespace std;

EntryObject :: EntryObject() : Object(ENTRY_FULL_INFO)
{
}

EntryObject :: EntryObject(DateObject inputDate, TimeObject inputTime, DetailsObject inputDetails): Object(ENTRY_FULL_INFO)
{
	entryDate = inputDate;
	entryTime = inputTime;
	entryDetails = inputDetails;
}

DateObject EntryObject :: getEntryDate()
{
	return entryDate;
}

TimeObject EntryObject :: getEntryTime()
{
	return entryTime;
}

DetailsObject EntryObject :: getEntryDetails()
{
	return entryDetails;
}

string EntryObject :: getEntryEvent()
{
	return entryDetails.getEvent();
}

string EntryObject :: getEntryLocation()
{
	return entryDetails.getLocation();
}

int EntryObject :: getEntryPriority()
{
	return entryDetails.getPriority();
}

void EntryObject :: setEntryTime(const TimeObject inputTime)
{
	entryTime = inputTime;
}
void EntryObject :: setEntryDate(const DateObject inputDate)
{
	entryDate = inputDate;
}

void EntryObject :: setEntryDetails(const DetailsObject inputDetails)
{
	entryDetails = inputDetails;
}

void EntryObject :: setEntry(const DateObject inputDate, const TimeObject inputTime, const DetailsObject inputDetails)
{
	setEntryDate(inputDate);
	setEntryTime(inputTime);
	setEntryDetails(inputDetails);
}