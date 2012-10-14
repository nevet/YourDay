/**
Your Day
IO.h

* This class is used to retrieve user input and display feedback message
* @author: Nhu Thao
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

	/**
	set the private input string to store user input

	@param user input entered through command line
	@return void
	*/
	void setInput(string textInput);

	/**
	set the status signal of IO process

	@param the success/error signal to be set to
	@return void
	*/
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