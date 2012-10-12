/**
    YourDay
    LangHandler.cpp
    Purpose: Calculates the total of 6 checks

    @author a0088455
    @version 0.1 10/13/2012
*/
#include <sstream>

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
void LangHandler::seperate(string* userInput)
{
	stringstream tempHolder;
	char blankSpaceEater;
	tempHolder << *userInput;
	tempHolder >> userCommand;
	tempHolder >> blankSpaceEater;
	details = new string;
	getline( tempHolder, *details );

}

// Retrieves the processed string pointer after seperation method
string * LangHandler::retrieve()
{
	return details;
}

LangHandler::~LangHandler()
{
}