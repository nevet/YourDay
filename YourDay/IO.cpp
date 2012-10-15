/**
* IO class is a part of UI part. It is known by UIHandler class
* IO class is used to get user input through command line and pass it to UIHandler as a pure string,
* and show feedback message string passed by UIHandler to user
* IO class has APIs getText():string to be called in the UIHandler to retrieve user input string
* and displayMessage(string):void to be called in the UIHandler to display feedback message string
*/

#include "IO.h"

void IO::setInput(string inText)
{
	input = inText;
}

void IO::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

IO::IO()
{
}

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

void IO::displayMessage(string output)
{
	cout << output;

	setStatus(SUCCESS);
}

void IO::clearStatus()
{
	status = CLEAR;
}

Signal IO::getStatus()
{
	return status;
}

IO::~IO()
{
}