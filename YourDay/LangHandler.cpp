/**
    YourDay
    LangHandler.cpp
    Purpose: Calculates the total of 6 checks

    @author a0088455
    @version 0.1 10/13/2012
*/
#include <sstream>
#include <string>

#include "LangHandler.h"

LangHandler::LangHandler()
{
}

// Sets the status of the language handler after input processing
void LangHandler::setStatus()
{
	if ( userCommand == "add" )
	{
		status = ADD_COMMAND;
	}
	else if ( userCommand == "delete" )
	{
		status = DELETE_COMMAND;
	}
	else if ( userCommand == "edit" )
	{
		status = EDIT_COMMAND;
	}
	else if ( userCommand == "search" )
	{
		status = SEARCH_COMMAND;
	}
	else if (userCommand == "undo" )
	{
		status = UNDO_COMMAND;
	}
	else
	{
		status = COMMAND_E;
	}
}

// Seperates user input's string into 2 parts, the input and the string to be processed
void LangHandler::seperate(string userInput)
{
	stringstream tempHolder;
	string rawString;
	string encodedString;
	char blankSpaceEater=' ';
	tempHolder << userInput;
	tempHolder >> userCommand;
	//ignore the blankSapce
	tempHolder.get(blankSpaceEater);
	
	setStatus();

	getline( tempHolder, rawString );
	if ( userCommand == "add" )
	{
		encodedString = encoder(rawString);
	}
	else
	{
		encodedString = rawString;
	}
	
	details= encodedString;
}


// Encodes the raw string into the correct saving format
string LangHandler::encoder(string input)
{
	stringstream tempHolder;
	string temp;
	string date = "";
	string time = "";
	string details = "";
	string location = "";
	string priority = "";

	if ( input == "" )
	{
		return "";
	}

	tempHolder << input;
	


	while (tempHolder >> temp)
	{
		if ((temp[2] == '/') && (temp[5] == '/') && ((temp.size() == 10) || (temp.size() == 8)))
		{
			date = temp;
		}
		else if (( temp[2]==':' ) && ( temp[5] == '-' ) && ( temp[8] == ':') && (temp.size() == 11))
		{
			time = temp;
		}
		else if ( temp == "at" )
		{
			while ( tempHolder >> temp )
			{
				if ( temp == "priority" )
				{
					tempHolder >> priority;					
					break;
				}
				else
				{
					location += temp;
					location += " ";
				}
			}
		}
		else 
		{
			details += temp;
			details += " ";
		}
	} 
	formattedInput = date+"#"+time+"#"+details+"#"+location+"#"+priority;

	return formattedInput;
}

// Retrieves the processed string pointer after seperation method
string LangHandler::retrieve()
{
	return details;
}

LangHandler::~LangHandler()
{
}