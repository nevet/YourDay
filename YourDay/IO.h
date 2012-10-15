/**
* IO class is a part of UI part. It is known by UIHandler class
* IO class is used to get user input through command line and pass it to UIHandler as a pure string,
* and show feedback message string passed by UIHandler to user
* IO class has APIs getText():string to be called in the UIHandler to retrieve user input string
* and displayMessage(string):void to be called in the UIHandler to display feedback message string
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
	* This operation is used to get user input through command line
	*/
	void getRawInput();

	/**
	* This operation is used to retrieve user input string and will be called in UIHandler
	* It calls getRawInput() to get user input through command line and return it to UIHandler
	* @return: raw input string
	*/
	string getText();

	/**
	* This operation is used to display feedback message string sof the system to user and will be called in UIHandler
	* @param outputmessage 
						is the feedback message string to display to user, passed by UIHandler
	*/
	void displayMessage(string output);

	void clearStatus();
	Signal getStatus();

	~IO();

};

#endif