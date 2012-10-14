/**
* IO class is in the UI part. It is used to get user input and output feedback message through command line.
* IO is known by UIHandler
* IO has the following main APIs to be called:
* getText(): string to get in user input througg command line
* displayMessage(string):void to display feedback string to user
* retrieveInput():string to return the user input string
*/

#include "IO.h"

//set the private user input string
void IO::setInput(string inText)
{
	input = inText;
}

//set the status of IO process
void IO::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

IO::IO()
{
}

//get the user input through command line
void IO::getRawInput()
{
	string inString = "";
	getline(cin, inString);
	setInput(inString);

	setStatus(SUCCESS);
}

string IO::getText()
{
	return input;
}

//display feedback message
void IO::displayMessage(string output)
{
	cout << output;

	setStatus(SUCCESS);
}

//clear the status of IO process to default CLEAR signal
void IO::clearStatus()
{
	status = CLEAR;
}

//get the status of IO process
Signal IO::getStatus()
{
	return status;
}

//return the string of user input
string IO::retrieveInput()
{
	return input;
}

IO::~IO()
{
}