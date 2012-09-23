#include "DateObject.h"



DateObject :: DateObject() :Object(ENTRY_DATE) {
	
}
DateObject :: DateObject(string inputDay, string inputMonth, string inputYear) : Object(ENTRY_DATE) {
	day=inputDay;
	month=inputMonth;
	year=inputYear;
}

string DateObject :: getDate() {
	return day+" "+month+" "+year;
}

string DateObject :: getDay() {
	return day;
}

string DateObject :: getMonth() {
	return month;
}

string DateObject :: getYear() {
	return year;
}

DateObject :: ~DateObject() {
}