#include <string>
#include <iostream>
#include "IO.h"

using namespace std;

void IO::createObject(string text)
{
	textObject = new TextObject (text);
}

void IO::deleteObject()
{
	delete textObject;
	textObject = NULL;
}

void IO::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

void IO::clearStatus()
{
	status = CLEAR;
}

IO::IO()
{
	textObject = NULL;
}

void IO::getInput()
{
	clearStatus();

	string inString;
	getline(cin, inString);
	createObject(inString);

	setStatus(SUCCESS);
}

void IO::printOutput(TextObject* output)
{
	clearStatus();

	cout << output->getString();
	deleteObject();

	setStatus(SUCCESS);
}

Signal IO::getStatus()
{
	return status;
}

TextObject* IO::retreiveObject()
{
	return textObject;
}

IO::~IO()
{
}