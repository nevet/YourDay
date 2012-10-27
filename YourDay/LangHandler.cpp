/**
    YourDay
    LangHandler.cpp
    Purpose: Encodes user's input and decodes stored entry

    @author a0088455r
    @version 0.1 10/13/2012
*/
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <map>
#include <ctime>

#include "LangHandler.h"

const int LangHandler::MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const string LangHandler::NULL_STRING = "";
const string LangHandler::PRIORITY_INDICATOR = " priority ";
const string LangHandler::LOCATION_INDICATOR = " at ";
const string LangHandler::SPACE_BAR = " ";
const string LangHandler::DELIMINATOR = "#";

bool LangHandler::leap(int year)
{
	bool flag = false;
	
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
		{
			flag = true;
		}
	} else
	{
		if (year % 4 == 0)
		{
			flag = true;
		}
	}

	return flag;
}

bool LangHandler::isDate(string date)
{
	int year, month, day;

	return sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) == 3;
}

bool LangHandler::isTime(string time)
{
	int h1, h2, m1, m2;

	return sscanf(time.c_str(), "%d:%d-%d:%d", &h1, &m1, &h2, &m2) == 4;
}

bool LangHandler::isInt(string inx)
{
	int x;

	return sscanf(inx.c_str(), "%d", &x) == 1;
}

bool LangHandler::isLogicDate(string date)
{
	int year, month, day;

	bool flag = true;

	//extract year, month and day from the string
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	if (year > 9999 || year < 1000)
	{
		flag = false;
	} else
	if (month > 12 || month < 1)
	{
		flag = false;
	} else
	if (day < 1)
	{
		flag = false;
	} else
	{
		if (!leap(year))
		{
			if (day > MONTH[month - 1])
			{
				flag = false;
			}
		} else
		if (month == 2 && day > 29)
		{
			flag = false;
		}
	}

	return flag;
}

bool LangHandler::isLogicTime(string time)
{
	int h1, h2, m1, m2;

	bool flag = true;

	sscanf(time.c_str(), "%d:%d-%d:%d", &h1, &m1, &h2, &m2);

	if (h1 > 23 || h1 < 0 || h2 > 23 || h2 < 0)
	{
		flag = false;
	} else
	if (m1 > 59 || m1 < 0 || m2 > 59 || m1 < 0)
	{
		flag = false;
	} else
	{
		if (h1 > h2)
		{
			flag = false;
		} else
		if (h1 == h2 && m1 > m2)
		{
			flag = false;
		}
	}

	return flag;
}

bool LangHandler::isLogicPriority(string priority)
{
	return (priority == "high") || (priority == "mid") || (priority == "low");
}

void LangHandler::encoder(string input, CommandType command)
{
	stringstream tempHolder(input);
	
	string date = NULL_STRING;
	string time = NULL_STRING;
	string index = NULL_STRING;
	string description = NULL_STRING;
	string location = NULL_STRING;
	string priority = NULL_STRING;

	string temp;

	size_t pos;

	//if empty string is entered by user, LENGTH_Z_E will be set and no more
	//operation should be entertained
	if (input == NULL_STRING && command != EXIT_COMMAND && command != UNDO_COMMAND)
	{
		langStatus = LENGTH_Z_E;
	} else
	{
		//input format is different for different command
		switch (command)
		{
			//format will be "[date] [time] description [at location] [priority [high, mid, low]]"
			case ADD_COMMAND:
				//check whether we have priority
				pos = input.rfind(PRIORITY_INDICATOR);
				//contains priority info
				if (pos != string::npos)
				{
					priority = input.substr(pos + PRIORITY_INDICATOR.length());
					//get rid of priority info
					input = input.substr(0, pos);
				}

				//check whether we have location
				pos = input.rfind(LOCATION_INDICATOR);
				//contains location info
				if (pos != string::npos)
				{
					location = input.substr(pos + LOCATION_INDICATOR.length());
					//get rid of location info
					input = input.substr(0, pos);
				}

				//extract potential date information and exmaine it
				pos = input.find(SPACE_BAR);
				date = input.substr(0, pos);
				
				if (isDate(date))
				{
					input = input.substr(pos + 1);
					
					pos = input.find(SPACE_BAR);
					time = input.substr(0, pos);

					if (isTime(time))
					{
						input = input.substr(pos + 1);
					} else
					{
						time = NULL_STRING;
					}
				} else
				{
					//it might be a time, so we need to exmaine it
					time = date;
					date = NULL_STRING;

					if (isTime(time))
					{
						input = input.substr(pos + 1);
					} else
					{
						time = NULL_STRING;
					}
				}

				description = input;

				//after have done separating, we need to exmaine each field
				//to make sure they are logic, if applicable
				if (priority != NULL_STRING && !isLogicPriority(priority))
				{
					throw string ("priority error\n");
				} else
				if (date != NULL_STRING && !isLogicDate(date))
				{
					throw string ("date error\n");					
				} else
				if (time != NULL_STRING && !isLogicTime(time))
				{
					throw string ("time error\n");
				}

				break;

			//format will be "index"
			case DELETE_COMMAND:
				pos = input.find(SPACE_BAR);
				index = input.substr(0, pos - 1);
				
				if (!isInt(index))
				{
					index = NULL_STRING;
					throw string ("Index error\n");
				}
				
				break;

			//format will be "description"
			case EDIT_COMMAND:
				break;

			//format will be "index description"
			case SEARCH_COMMAND:
				description = input;
				break;

			default:
				break;
		}

		if (!sh.error(langStatus))
		{
			details = DELIMINATOR + index + DELIMINATOR + description + DELIMINATOR + 
					  location + DELIMINATOR + time + DELIMINATOR + date + DELIMINATOR + priority + DELIMINATOR;
		}
	}
}

void LangHandler::setCommand(string userCommand)
{	
	//if user command is valid, set corresponding command type
	if ( userCommand == "add" )
	{
		command = ADD_COMMAND;
	}
	else
	if ( userCommand == "delete" )
	{
		command = DELETE_COMMAND;
	}
	else
	if ( userCommand == "edit" )
	{
		command = EDIT_COMMAND;
	}
	else
	if ( userCommand == "search" )
	{
		command = SEARCH_COMMAND;
	}
	else
	if (userCommand == "undo" )
	{
		command = UNDO_COMMAND;
	}
	else
	if (userCommand == "exit" )
	{
		command = EXIT_COMMAND;
	}
	else
	{
		//if user command is invalid, command error signal should be set
		throw string ("Command error\n");
	}
}

LangHandler::LangHandler()
{
	//set default value for language handler status
	langStatus = CLEAR;
}

Signal LangHandler::getStatus()
{
	return langStatus;
}

void LangHandler::separate(string userInput) throw (string)
{
	stringstream tempHolder(userInput);

	string userCommand;
	string rawString;

	char dummySpace;

	//first we extract user command
	tempHolder >> userCommand;
	setCommand(userCommand);
	
	//if set command fails, no other operation should be entertained
	if (sh.error(langStatus))
	{
		throw string ("No such command!\n");
	} else
	{
		//to get rid of leading space
		tempHolder.get(dummySpace);
		getline(tempHolder, rawString);

		encoder(rawString, command);

		//if no error threw by encoder, langStatus should be set to SUCCESS
		if (!sh.error(langStatus))
		{
			langStatus = SUCCESS;
		}
	}
}

Executor* LangHandler::pack(bool* quit, vector<string>* generalEntryList,
										vector<string>* calendarEntryList,
										vector<string>* diduknowBoxList,
										StorageHandler* store)
{
	Executor* exe;
	
	switch (command)
	{
		case ADD_COMMAND:
			exe = new AddExecutor(generalEntryList, calendarEntryList, details);
			break;

		case DELETE_COMMAND:
			exe = new DeleteExecutor(generalEntryList, calendarEntryList, details);
			break;

		case SEARCH_COMMAND:
			exe = new SearchExecutor(generalEntryList, calendarEntryList, diduknowBoxList, details);
			break;

		case EDIT_COMMAND:
			exe = new UpdateExecutor(generalEntryList, calendarEntryList, details);
			break;

		case EXIT_COMMAND:
			exe = new ExitExecutor(generalEntryList, calendarEntryList, store, quit);
			break;

		case UNDO_COMMAND:
			exe = NULL;
			break;

		default:
			break;
	}

	return exe;
}

LangHandler::~LangHandler()
{
}