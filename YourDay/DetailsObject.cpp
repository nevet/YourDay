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

DetailsObject :: ~DetailsObject() {
}