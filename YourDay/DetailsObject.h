#ifndef DETAILSOBJECT_H
#define DETAILSOBJECT_H

#include <iostream>
#include <string>

#include "Object.h"

using namespace std;

class DetailsObject : public Object {
private:
	string eventDetails;
	string location;
	int priority;
public:
	DetailsObject();
	DetailsObject(string inputEvent, string inputLocation, int priority);
	string getEvent();
	string getLocation();
	int getPriority();
	~DetailsObject();
};

#endif