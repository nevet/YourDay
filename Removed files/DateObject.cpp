#include "DateObject.h"



DateObject :: DateObject() :Object(ENTRY_DATE)
{	
}

DateObject :: DateObject(string inputDay, string inputMonth, string inputYear) : Object(ENTRY_DATE)
{
	day = inputDay;
	month = inputMonth;
	year = inputYear;
}

string DateObject :: getDate()
{
	return day + " " + month + " " + year;
}

string DateObject :: getDay()
{
	return day;
}

string DateObject :: getMonth()
{
	return month;
}

string DateObject :: getYear()
{
	return year;
}

void DateObject :: setDay(const string inputDay)
{
	day = inputDay;
}

void DateObject :: setMonth(const string inputMonth)
{
	month = inputMonth;
}

void DateObject :: setYear(const string inputYear)
{
	year = inputYear;
}

void DateObject :: setDate(const string inputDay,const string inputMonth,const string inputYear)
{
	setDay(inputDay);
	setMonth(inputMonth);
	setYear(inputYear);
}

DateObject :: ~DateObject()
{
}