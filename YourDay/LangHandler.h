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
#include "StatusHandler.h"

using namespace std;

class LangHandler : public Handler
{
private:
	StatusHandler sh;

	Signal command;
	Signal langStatus;

	string details;	
	string formattedInput;

	bool isDate(string date);
	bool isTime(string time);

	/**
	* Encodes the raw string into the correct saving format
	*
	* @param input
	*			is a raw string that needs to be encoded
	* @param command
	*			is the command type
	* @return encoded string, format of the string is:
	* 
	* #index#description#location#time#date#priority#
	*
	* index:
	*		this field contains index information required by delete and update
	*		functions.
	* description:
	*		this field contains description of the task required by add, search
	*		and update functions.
	* location:
	*		this field contains location information required by add and search
	*		functions.
	* time:
	*		this field contains time information required by add and search
	*		functions.
	* date:
	*		this field contains date information required by add and search
	*		functions.
	* priority:
	*		this field contains priority information required by add and search
	*		functions.
	*		
	* Note that some fields are not necessarily required. However, if one field
	* if not required for a certain function, that field should not be OMITTED.
	*
	* e.g
	*
	* userInput = "add CS2103 TUT at COM on Friday"
	* encoded	= "##CS2103 TUT#COM##Friday##"
	*
	* explaination:
	*
	* since index field, time field and priority field are missing,
	* corresponding fields should be left as "blank".
	*
	* userInput = "delete 1"
	* encoded	= "#1######"
	*
	* explaination:
	*
	* only index field is specified, so other fields should be "blank".
	*/
	string encoder(string input, Signal command);

	/**
	* This operation will set command type using userCommand. If userCommand
	* took from the user is invalid, COMMAND_E Signal will be set.
	*/
	void setCommand(string userCommand);

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

	~LangHandler();
};


#endif