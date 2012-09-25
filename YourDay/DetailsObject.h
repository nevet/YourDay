#ifndef DETAILSOBJECT_H
#define DETAILSOBJECT_H

#include <iostream>
#include <string>

#include "Object.h"

using namespace std;

class DetailsObject : public Object
{
private:
	string eventDetails;
	string location;
	int priority;
public:
	DetailsObject();
	DetailsObject(string inputEvent, string inputLocation, int inputPriority);
	string getEvent();
	string getLocation();
	int getPriority();
	void setEvent(const string inputEvent);
	void setLocation(const string inputLociation);
	void setPriority(const int inputPriority);
	void setDetails(const string inputEvent, const string inputLocation, const int inputPriority);
	~DetailsObject();
};

#endif