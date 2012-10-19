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

const string LangHandler :: COMMAND_ERROR =  "Wrong command. Please try again.\n";

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
		
		throw (  COMMAND_ERROR );
	}
}

// Seperates user input's string into 2 parts, the input and the string to be processed
void LangHandler::separate(string userInput)
{
	stringstream tempHolder;
	string rawString;
	string encodedString;
	char blankSpaceEater;
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
	bool isDatePart = false;
	int decodedMonth;

	ostringstream date ( "");
	string hour = "";
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
		if ((temp.size() <= 10) && (temp.size() >= 8) && (temp[2] == '/') && (temp[5] == '/'))
		{
			date << temp;
		}
		else if (isDatePart)
		{
			time_t t= time(NULL);
			tm* now=localtime(&t);
			int year = now->tm_year + 1900;

			date << temp << "/" << decodedMonth << "/" << year;
			isDatePart = false;
		}
		else if (isMonth(temp, &decodedMonth))
		{
			isDatePart = true;
		}
		else if ((temp.size() == 11)&&( temp[2]==':' ) && ( temp[5] == '-' ) && ( temp[8] == ':') )
		{
			hour = temp;
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
	formattedInput = date.str()+"#"+hour+"#"+eventDetails+"#"+location+"#"+priority;

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

//Breaks the encoded string to different fields format
void LangHandler::breakString(string* date, string* time, string* details, string* location, string* priority)
{

}

LangHandler::~LangHandler()
{
}