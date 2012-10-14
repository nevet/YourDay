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

class LangHandler : Handler
{
private:
	string* details;	
	string userCommand;
public :
	
	LangHandler();

	/**
	Sets the status of the language handler after input processing
	
	@param void
	@return void
	*/
	void setStatus();
	Signal getStatus();
	/**
	Seperates user input's string into 2 parts, the input and the string to be processed
	
	@param user's input string
	@return void
	*/
	void seperate(string userInput);

	/**
	Encodes the raw string into the correct saving format
	
	@param input string that needs to be encoded
	@return encoded string
	*/
	string encoder(string input);

	/**
	Retrieves the processed string pointer after seperation method
	
	@param void
	@return processed string pointer
	*/
	string retrieve();

	~LangHandler();
};


#endif