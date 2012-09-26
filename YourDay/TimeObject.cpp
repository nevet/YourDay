#include "TimeObject.h"

#include <iostream>
#include <string>

using namespace std;

TimeObject :: TimeObject() : Object (ENTRY_TIME) {
}

TimeObject :: TimeObject(string inputHour, string inputMinute) : Object(ENTRY_TIME) {
	hour=inputHour;
	minute=inputMinute;
}
string TimeObject :: getHour() {
	return hour;
}
string TimeObject :: getMinutes() {
	return minute;
}

string TimeObject :: getTime() {
	return hour+":"+minute;
}

TimeObject :: ~TimeObject() {
}
