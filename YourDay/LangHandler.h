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

	/**
	* Encodes the raw string into the correct saving format
	*
	* @param input
	*			is a raw string that needs to be encoded
	* @return encoded string
	*
	* e.g
	*
	* samples of I/O should be written here 
	*/
	string encoder(string input);

public :
	
	LangHandler();

	/**
	* Sets the status of the language handler after input processing.
	*
	* Signals will be:
	* SUCCESS		User input has been successfully proceeded;
	* Other signals should be caught later
	*/
	void setStatus();

	/**
	* Retrieve user command.
	*/
	Signal retrieveUserCommand();

	/**
	* Seperates user input's string into 2 parts, the command and the
	* encoded string.
	*
	* User command will be stored in private string userCommand;
	* Details info will be stored in private string details
	* 
	* e.g
	*
	* userInput = "add CS2103 tutorial at COM1 on Friday";
	* return = {userCommand = "add", detials = "#CS2103 tutorial#COM1#Friday#"}
	* 
	* userInput = "delete 1";
	* return = {userCommand = "delete", details = "#1###"}
	*
	* details about format of encoded string can be found in encoded().
	*/
	void separate(string userInput);

	/**
	* Retrieve the encoded user input information
	*/
	string retrieveEncodedInfo();

	/**
	* Decodes the processed string to output format
	*
	* @param input
	*			is an encoded string
	* @return decoded string
	*
	* e.g
	*
	* samples of I/O should be written here
	*/
	string decoder(string input);

	/**
	* Breaks the encoded string to different fields format
	*/
	void breakString(string* date, string* time, string* details, string* location, string* priority);

	~LangHandler();
};


#endif