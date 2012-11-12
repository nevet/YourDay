#ifndef TIMEOBJECT_H
#define TIMEOBJECT_H

#include "Object.h"

#include <iostream>
#include <string>

using namespace std;

class TimeObject : public Object
{
private:
	string hour;
	string minute;
public:
	TimeObject();
	TimeObject(string inputHour, string inputMinutes);
	string getHour();
	string getMinutes();
	string getTime();
	void setHour(const string inputHour);
	void setMinutes(const string inputMinutes);
	void setTime(const string inputHour, const string inputMinutes);
	~TimeObject();

};

#endif