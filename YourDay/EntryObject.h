#ifndef ENTRYOBJECT_H
#define ENTRYOBJECT_H

#include "Object.h"
#include "TimeObject.h"
#include "DateObject.h"
#include "DetailsObject.h"


class EntryObject : public Object {
private:
	DateObject entryDate;
	TimeObject entryTime;
	DetailsObject entryDetails;
public:
	EntryObject();
	EntryObject(DateObject inputDate, TimeObject inputTime, DetailsObject inputDetails);
	DateObject getEntryDate();
	TimeObject getEntryTime();
	DetailsObject getEntryDetails();
	string getEntryEvent();
	string getEntryLocation();
	int getEntryPriority();
	//additional method such as get entry hours and minutes can be applied later utilizing the methods of other classes
};

#endif ENTRYOBJECT_H
