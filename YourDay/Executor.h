#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<iostream>
#include<string>

#include "Signal.h"


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
	//#index#description#location#time#date#priority#
	int extractIndex(string details);
	string extractDescription(string details);
	string extractLocation(string details);
	string extractTime(string details);
	string extractDate(string details);
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