#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<iostream>
#include<string>

#include "Signal.h"

//@author A0088455R
const int INDEX_BLOCK_LOCATION			= 1;  
const int DESCRIPTION_BLOCK_LOCATION	= 2;
const int LOCATION_BLOCK_LOCATION		= 3;
const int TIME_BLOCK_LOCATION			= 4;
const int DATE_BLOCK_LOCATION			= 5;
const int PRIORITY_BLOCK_LOCATION		= 6;


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
	* Decodes the encoded string and retreives the priority field
	*
	* @param details
	*			is a encoded string that needs to be decoded
	* @return priority
	*			is the priority field of retrieved from encoded 
	* 
	* if priority field is empty
	* e.g.
	* encoded	= "#cs2103 meeting#biz canteen####"
	* priority will be returned as 0.
	* 
	* explanation:
	*
	* if priority field is specified, the return will be the priority otherwise
	* 0 will be returned.
	*/
	int extractPriority(string details);
	
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