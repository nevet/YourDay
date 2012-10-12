#ifndef DATEOBJECT_H
#define DATEOBJECT_H
#include "Object.h"

#include <iostream>
#include <string>

using namespace std;

class DateObject : public Object
{
private:
	string day;
	string month;
	string year;
public:
	DateObject();
	DateObject(string inputDay, string inputMonth, string inputYear);
	string getDate();
	string getDay();
	string getMonth();
	string getYear();
	void setDay(const string inputDay);
	void setMonth(const string inputMonth);
	void setYear(const string inputYear);
	void setDate(const string inputDay,const string inputMonth,const string inputYear);
	~DateObject();
};

#endif