#include <iostream>
#include <string>

#include "DetailsObject.h"

using namespace std;

DetailsObject :: DetailsObject() : Object(ENTRY_DETAILS) {
}

DetailsObject :: DetailsObject(string inputEvent, string inputLocation, int inputPriority) : Object(ENTRY_DETAILS) {
	eventDetails=inputEvent;
	location=inputLocation;
	priority=inputPriority;
}

string DetailsObject :: getEvent() {
	return eventDetails;
}

string DetailsObject :: getLocation() {
	return location;
}

int DetailsObject :: getPriority() {
	return priority;
}

void DetailsObject :: setEvent(const string inputEvent)
{
	eventDetails = inputEvent;
}

void DetailsObject :: setLocation(const string inputLocation)
{
	location = inputLocation;
}

void DetailsObject :: setPriority(const int inputPriority)
{
	priority = inputPriority;
}

void DetailsObject :: setDetails(const string inputEvent, const string inputLocation, const int inputPriority)
{
	setEvent(inputEvent);
	setLocation(inputLocation);
	setPriority(inputPriority);
}

DetailsObject :: ~DetailsObject() {
}