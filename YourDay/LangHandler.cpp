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

bool LangHandler::isDate(string date)
{
	int year, month, day;

	return sscanf(date.c_str(), "%d/%d/%d", &year, &month, &day) == 3;
}

bool LangHandler::isTime(string time)
{
	int h1, h2, m1, m2;

	return sscanf(time.c_str(), "%d:%d-%d:%d", &h1, &h2, &m1, &m2) == 4;
}

bool LangHandler::isInt(string inx)
{
	int x;

	return sscanf(inx.c_str(), "%d", x) == 1;
}

bool LangHandler::isLogicDate(string date)
{
	return true;
}

bool LangHandler::isLogicTime(string time)
{
	return true;
}

LangHandler::LangHandler()
{
	//set default value for language handler status
	langStatus = CLEAR;
}

void LangHandler::setStatus()
{
	status = langStatus;
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
		langStatus = COMMAND_E;
	}
}

void LangHandler::separate(string userInput)
{
	stringstream tempHolder(userInput);

	string userCommand;
	string rawString;
	string encodedString;

	char dummySpace;

	//first we extract user command
	tempHolder >> userCommand;
	setCommand(userCommand);

	//if set command fails, no other operation should be entertained
	if (!sh.error(langStatus))
	{
		//to get rid of leading space
		tempHolder.get(dummySpace);
		getline(tempHolder, rawString);

		encodedString = encoder(rawString, command);

		//if no error threw by encoder, langStatus should be set to SUCCESS
		if (!sh.error(langStatus))
		{
			langStatus = SUCCESS;
		}
	}

	setStatus();
}

string LangHandler::encoder(string input, Signal command)
{
	stringstream tempHolder(input);
	
	string date = "";
	string time = "";
	string index = "";
	string description = "";
	string location = "";
	string priority = "";

	string temp;

	size_t pos;

	//if empty string is entered by user, LENGTH_Z_E will be set and no more
	//operation should be entertained
	if (input == "")
	{
		langStatus = LENGTH_Z_E;
	} else
	{
		//input format is different for different command
		switch (command)
		{
			//format will be "[date] [time] description [at location]"
			case ADD_COMMAND:
				//check whether we have location
				pos = input.rfind(" at ");
				//contains location info
				if (pos != string::npos)
				{
					location = input.substr(pos + 4);
					//get rid of location info
					input = input.substr(0, pos);
				}

				//extract potential date information and exmaine it
				pos = input.find(" ");
				date = input.substr(0, pos);
				
				if (isDate(date))
				{
					input = input.substr(pos + 1);
					
					pos = input.find(" ");
					time = input.substr(0, pos);

					if (isTime(time))
					{
						input = input.substr(pos + 1);
					} else
					{
						time = "";
					}
				} else
				{
					//it might be a time, so we need to exmaine it
					time = date;
					date = "";					

					if (isTime(time))
					{
						input = input.substr(pos + 1);
					} else
					{
						time = "";
					}
				}

				description = input;

				//after have done separating, we need to exmaine date and time
				//to make sure they are logic, if applicable
				if (date != "" && !isLogicDate(date))
				{
					langStatus = DATE_E;
				} else
				if (time != "" && !isLogicTime(time))
				{
					langStatus = TIME_E;
				}

				break;

			//format will be "index"
			case DELETE_COMMAND:
				pos = input.find(" ");
				index = input.substr(0, pos - 1);
				
				if (!isInt(index))
				{
					index = "";
					langStatus = INDEX_E;
				}

				break;

			//format will be "description"
			case EDIT_COMMAND:
				break;

			//format will be "index description"
			case SEARCH_COMMAND:
				break;

			default:
				break;
		}

		if (!sh.error(langStatus))
		{
			formattedInput = "#" + index + "#" + description + "#" + location + "#" + time + "#" + date + "#" + priority + "#";
		}
	}

	return formattedInput;
}

Signal LangHandler::retrieveUserCommand()
{
	return command;
}

string LangHandler::retrieveEncodedInfo()
{
	return details;
}

LangHandler::~LangHandler()
{
}