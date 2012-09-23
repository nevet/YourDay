#include <iostream>
#include <string>

#include "DetailsObject.h"

using namespace std;

DetailsObject :: DetailsObject() {
}

DetailsObject :: DetailsObject(string inputEvent, string inputLocation, int inputPriority) {
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