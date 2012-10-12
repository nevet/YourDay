#include "IO.h"

void IO::setText(string inText)
{
	text = inText;
}

void IO::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

IO::IO()
{
	text = "";
}

void IO::getInput()
{
	string inString;
	getline(cin, inString);
	setText(inString);

	setStatus(SUCCESS);
}

void IO::printOutput(string output)
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

string IO::getText()
{
	return text;
}

IO::~IO()
{
}