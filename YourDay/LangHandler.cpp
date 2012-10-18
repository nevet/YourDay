/**
    YourDay
    LangHandler.cpp
    Purpose: Calculates the total of 6 checks

    @author a0088455r
    @version 0.1 10/13/2012
*/
#include <sstream>
#include <string>

#include "LangHandler.h"

string LangHandler::decodePart(DetailPart part)
{
	string ans = "";
	switch (part)
	{
	case DATE:
		{
			ans = "On ";
			break;
		}
	case TIME:
		{
			ans = "at ";
			break;
		}
	case DETAILS:
		{
			ans = ": ";
			break;
		}
	case LOCATION:
		{
			ans = "at ";
			break;
		}
	case PRIORITY:
		{
			ans = "with priority";
			break;
		}
	default:
		{
			//use some signal here
			break;
		}
	}

	return ans;
}

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
	else if (userCommand == "exit" )
	{
		status = EXIT_COMMAND;
	}
	else
	{
		status = COMMAND_E;
	}
}

// Seperates user input's string into 2 parts, the input and the string to be processed
void LangHandler::separate(string userInput)
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
	string eventDetails = "";
	string location = "";
	string priority = "";

	if ( input == "" )
	{
		return "";
	}

	tempHolder << input;

	while (tempHolder >> temp)
	{
		if (((temp.size() == 10) || (temp.size() == 8))&&(temp[2] == '/') && (temp[5] == '/') )
		{
			date = temp;
		}
		else if ((temp.size() == 11)&&( temp[2]==':' ) && ( temp[5] == '-' ) && ( temp[8] == ':') )
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
			eventDetails += temp;
			eventDetails += " ";
		}
	} 
	formattedInput = date+"#"+time+"#"+eventDetails+"#"+location+"#"+priority;

	return formattedInput;
}

string LangHandler::decoder(string input)
{
	string decodedString = "";
	int size = input.size();
	char curChar;			//current character in input string
	DetailPart part = DATE;

	for (int i = 0; i < input.size(); i++)
	{
		curChar = input[i];
		if (curChar != '#')
		{
			decodedString += curChar;
		}
		else
		{
			if (i != input.size()-1 && input[i+1] != '#' && decodedString != "")
			{
				decodedString += ": ";
			}
		}
	}

	return decodedString;
}

// Retrieves the processed string pointer after seperation method
string LangHandler::retrieve()
{
	return details;
}

LangHandler::~LangHandler()
{
}