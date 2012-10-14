/**
* IO class is in the UI part. It is used to get user input and output feedback message through command line.
* IO is known by UIHandler
* IO has the following main APIs to be called:
* getText(): string to get in user input througg command line
* displayMessage(string):void to display feedback string to user
* retrieveInput():string to return the user input string
*/

#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include "Signal.h"

using namespace std;

class IO
{
private:
	Signal status;
	string input;

	void setInput(string textInput);
	void setStatus(Signal statusSignal);
public:
	IO();

	/**
	get user input string through command line

	@param void
	@return void
	*/
	void getText();

	/**
	display feedback message string of the system to user

	@param message string to display to user
	@return void
	*/
	void displayMessage(string output);

	/**
	clear the status of IO process to default CLEAR signal

	@param void
	@return void
	*/
	void clearStatus();

	/**
	get the status of IO process

	@param void
	@return IO process signal
	*/
	Signal getStatus();

	/**
	retrieve the user input stored by IO

	@param void
	@return user input stored by IO
	*/
	string retrieveInput();

	~IO();

};

#endif