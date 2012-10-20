/**
    YourDay
    LangHandler.cpp
    Purpose: Encodes user's input and decodes stored entry

    @author a0088455r
    @version 0.1 10/13/2012
*/
#include <sstream>
#include <string>
#include <map>
#include <ctime>

#include "LangHandler.h"

bool LangHandler::isMonth(string month, int* decodedMonth)
{
	bool ans;
	map<string, int> mapper;

	mapper ["JAN"] = 1;
	mapper ["FEB"] = 2;
	mapper ["MAR"] = 3;
	mapper ["APR"] = 4;
	mapper ["MAY"] = 5;
	mapper ["JUN"] = 6;
	mapper ["JUL"] = 7;
	mapper ["AUG"] = 8;
	mapper ["SEP"] = 9;
	mapper ["OCT"] = 10;
	mapper ["NOV"] = 11;
	mapper ["DEC"] = 12;
	
	if (mapper.find(month) == mapper.end())
	{
		ans = false;
	}
	else
	{
		ans = true;
		*decodedMonth = mapper[month];
	}

	return ans;
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
			case ADD_COMMAND:
				break;

			case DELETE_COMMAND:
				break;

			case EDIT_COMMAND:
				break;

			case SEARCH_COMMAND:
				break;

			default:
				break;
		}

		formattedInput = "#" + index + "#" + description + "#" + location + "#" + time + "#" + date + "#" + priority + "#";
	}

	return formattedInput;
}

string LangHandler::retrieveEncodedInfo()
{
	return details;
}

LangHandler::~LangHandler()
{
}