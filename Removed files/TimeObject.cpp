#include "TimeObject.h"

#include <iostream>
#include <string>

using namespace std;

TimeObject :: TimeObject() : Object (ENTRY_TIME)
{
}

TimeObject :: TimeObject(string inputHour, string inputMinute) : Object(ENTRY_TIME)
{
	hour = inputHour;
	minute = inputMinute;
}
string TimeObject :: getHour()
{
	return hour;
}
string TimeObject :: getMinutes()
{
	return minute;
}

string TimeObject :: getTime()
{
	return hour + ":" + minute;
}

void TimeObject :: setHour(const string inputHour)
{
	hour = inputHour;
}

void TimeObject :: setMinutes(const string inputMinutes)
{
	minute = inputMinutes;
}

void TimeObject :: setTime(const string inputHour, const string inputMinutes)
{
	setHour(inputHour);
	setMinutes(inputMinutes);
}

TimeObject :: ~TimeObject() {
}
