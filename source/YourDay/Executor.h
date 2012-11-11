#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<iostream>
#include<string>

#include "Log.h"
#include "Signal.h"

//@author A0088455R

/**
* These are the predefined values of the block locations for each
* field inside the encoded string
* format: "#index#description#location#time#date#priority#"
*/


using namespace std;

/**
* This class is used to do the execusion of corresponding command. Specific
* executor will derive from this super class. We can easily execute specific
* command by doing dynamic binding.
*/
class Executor
{
//we set status as protected variable so that subclass is able to make change
protected:
	Signal status;

	/**
	* These are the predefined values of the block locations for each
	* field inside the encoded string
	* format: "#index#description#location#time#date#priority#"
	*/
	const static int INDEX_BLOCK_LOCATION;  
	const static int DESCRIPTION_BLOCK_LOCATION;
	const static int LOCATION_BLOCK_LOCATION;
	const static int TIME_BLOCK_LOCATION;
	const static int DATE_BLOCK_LOCATION;
	const static int MARK_BLOCK_LOCATION;
	const static int NO_INDEX_IN_DESCRIPTION;

	Log log;
	
	/**
	* Decodes the encoded string and retreives the index
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @param blockLocation
	*			is the block location of the required field
	* @return index
	*			is the starting index of block that needs to be retreived
	*
	* if block location is 2 and the string is as follows 
	*
	* "#1#cs2103 meeting#biz canteen####" (details of the encoded string can be
	* found on LangHandler::encoder())
	*
	* index will be returned as 3.
	*
	* explanation:
	*
	* the method will try to find the second '#' occurance and returns
	* the index where the '#' found 
	*/
	int findBlockIndex(string details, int blockLocation);

	/**
	* Decodes the encoded string and retreives the index
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @param startLocation
	*			is the start index of the required field
	* @return extracted string
	*			is the extracted string from required field
	*	
	* if start location is 2 and the string is as follows
	*
	* "#1#cs2103 meeting#biz canteen####"
	* the extracted string will be "cs2103 meeting"
	*
	* explanation:
	*
	* the method will try to find the next '#' occurance and returns
	* string between the '#'s
	*/
    string extractField(string details, int startLocation);

	/**
	* Decodes the encoded string and retreives the index
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @return index
	*			is the index field of retrived from encoded 	
	*		
	* if index field is empty
	* e.g.
	* encoded	= "#cs2103 meeting#biz canteen####"
	* index will be returned as 0.
	*
	* explaination:
	*
	* if index field is specified, the return will be the index number otherwise
	* 0 will be returned.
	*/
	int extractIndex(string details);

	/**
	* Decodes the encoded string and retreives the description field
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @return description
	*			is the description field of retrieved encoded  string
	*		
	* if description field is empty
	* e.g.
	* encoded	= "#1##biz canteen#13:00-14:00###"
	* description will be returned as empty string.
	*
	* explaination:
	*
	* if description field is specified, the return will be the description
	* otherwise empty string.
	*/
	string extractDescription(string details);

	/**
	* Decodes the encoded string and retreives the location field
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @return location
	*			is the location field of retrieved encoded  string
	* #index#description#location#time#date#priority#
	*		
	* if location field is empty
	* e.g.
	* encoded	= "#1#meeting with professor##13:00-14:00###"
	* description will be returned as empty string.
	*
	* explanation:
	*
	* if location field is specified, the return will be the location
	* otherwise it returns an empty string.
	*/
	string extractLocation(string details);

	/**
	* Decodes the encoded string and retreives the time field
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @return time
	*			is the time field of retrieved encoded string
	* 
	* if time field is empty
	* e.g.
	* encoded	= "#1##biz canteen##21/10/2012##"
	* time field will be returned as empty string.
	* 
	* explanation:
	*
	* if time field is specified, the return will be the time field
	* otherwise it will return an empty string.
	*/
	string extractTime(string details);

	/**
	* Decodes the encoded string and retreives the date field
	*
	* @param details
	*			is a encoded string that needs to be decoded
	*			format DD/MM/YYYY
	* @return date
	*			is the description of retrieved encoded  string
	* 
	* if date field is empty
	* e.g.
	* encoded	= "#1##biz canteen#13:00-14:00###"
	* date will be returned as an empty string.
	*
	* explanation:
	*
	* if date field is specified, the return will be the date field
	* otherwise it will return an empty string.
	*/
	string extractDate(string details);

	/**
	* Decodes the encoded string and retreives the "Mark as important" field
	*
	* @param details
	*			is a encoded string that needs to be decoded	
	*			format DD/MM/YYYY
	* @return priority
	*			is the mark as important field of retrieved from encoded 
	* 
	* if priority field is empty
	* e.g.
	* encoded	= "#cs2103 meeting#biz canteen####"
	* mark will be returned as blank.
	* 
	* explanation:
	*
	* if mark as important field is specified, the return will be the priority otherwise
	* blank will be returned.
	*/
	string extractMark(string details);
	
	/**
	* Extracts the day from a date string
	*
	* @param date
	*			is properly formated date string that needs to be decoded
	*			format DD/MM/YYYY
	* @return day number
	*			is the day from date string
	* e.g
	* if input = "27/10/2012"
	* the return will be 27
	*/
	int extractDay(string date);

	/**
	* Extracts the month from a date string
	*
	* @param date
	*			is properly formated date string that needs to be decoded
	* @return month
	*			is the month from date string 
	* e.g
	* if input = "27/10/2012"
	* the return will be 10
	*/
	int extractMonth(string date);

	/**
	* Extracts the Year from a date string
	*
	* @param date
	*			is properly formated date string that needs to be decoded
	*			format DD/MM/YYYY
	* @return Year
	*			is the year from date string 
	* e.g
	* if input = "27/10/2012"
	* the return will be 2012
	*/
	int extractYear(string date);

	/**
	* Extracts the hour from a time string
	*
	* @param time
	*			is properly formated time string that needs to be decoded
	*			format: HH:MM
	* @return hour
	*			is the hout from time string 
	* e.g
	* if input = "15:00"
	* the return will be 15
	*/
	int extractHour(string time);

	/**
	* Extracts the minute from a time string
	*
	* @param time
	*			is properly formated time string that needs to be decoded
	*			format: HH:MM
	* @return minute
	*			is the minute from time string 
	* e.g
	* if input = "15:00"
	* the return will be 0
	*/
	int extractMinute(string time);

	/**
	* Extracts the hour from a time string
	*
	* @param start
	*			is the container for properly formated start time string
	*			format: HH:MM
	* @param end
	*			is the container for properly formated end time string
	*			format: HH:MM
	* @param time range
	*			is properly formated time range string that needs to be decoded
	*			format: HH:MM-HH:MM
	* @return void
	* e.g
	* if input = "15:00-14:00"
	* the start will be "15:00" and end will be "14:00"
	*/
	void splitStartEndTime(string* start, string* end, string timeRange);

	int extractIndexFromDescription(string description);

public:
	/**
	* Note that different subclass may take in different parameter, so this
	* function should be overridden by its subclass.
	*/
	Executor();

	/**
	* This operation should be overwriten by its sub-class. The operation does
	* the execution of the command. Specific behaviour will be defined in
	* corresponding subclass.
	*/
	virtual void execute();
	virtual void undo();
	Signal getStatus();
};

#endif