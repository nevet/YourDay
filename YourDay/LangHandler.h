/**
    YourDay
    LangHandler.h
    Purpose: Calculates the total of 6 checks

    @author a0088455
    @version 0.1 10/13/2012
*/
#ifndef LANGHANDLER_H
#define LANGHANDLER_H

#include <iostream>

#include "Signal.h"
#include "Handler.h"

using namespace std;

class LangHandler : public Handler
{
private:
	//These are parts of a detailed event, to be used in decoder operation
	enum DetailPart
	{
		DATE, TIME, DETAILS, LOCATION, PRIORITY
	};
	static const string COMMAND_ERROR;
	string details;	
	string formattedInput;
	string userCommand;

	bool isMonth(string month, int* decodedMonth);
	bool isTime(string text);

public :
	
	LangHandler();

	/**
	Sets the status of the language handler after input processing
	
	@param void
	@return void
	*/
	void setStatus();

	/**
	Seperates user input's string into 2 parts, the input and the string to be processed
	
	@param user's input string
	@return void
	*/
	void separate(string userInput);

	/**
	Encodes the raw string into the correct saving format
	
	@param input string that needs to be encoded
	@return encoded string
	*/
	string encoder(string input);

	/**
	Retrieves the processed string pointer after separation method
	
	@param void
	@return processed string pointer
	*/

	string retrieve();

	/**
	Decodes the processed string to output format
	
	@param void
	@return processed string pointer
	*/
	string decoder(string input);

	/**
	Breaks the encoded string to different fields format
	
	@param void
	@return void
	*/
	void breakString(string* date, string* time, string* details, string* location, string* priority);

	~LangHandler();
};


#endif