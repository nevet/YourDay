#include <iostream>
#include <string>

#include "EntryObject.h"

using namespace std;

EntryObject :: EntryObject() : Object(ENTRY_FULL_INFO) {
}

EntryObject :: EntryObject(DateObject inputDate, TimeObject inputTime, DetailsObject inputDetails) {
	entryDate=inputDate;
	entryTime=inputTime;
	entryDetails=inputDetails;
}

DateObject EntryObject :: getEntryDate() {
	return entryDate;
}

TimeObject EntryObject :: getEntryTime() {
	return entryTime;
}

DetailsObject EntryObject :: getEntryDetails() {
	return entryDetails;
}

string EntryObject :: getEntryEvent() {
	return entryDetails.getEvent();
}

string EntryObject :: getEntryLocation() {
	return entryDetails.getLocation();
}

int EntryObject :: getEntryPriority() {
	return entryDetails.getPriority();
}