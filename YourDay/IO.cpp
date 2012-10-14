/**
Your Day
IO.cpp

* This class is used to retrieve user input and display feedback message
* @author: Nhu Thao
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
	getRawInput();
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