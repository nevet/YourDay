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

IO::IO()
{
	textObject = NULL;
}

void IO::getInput()
{
	string inString;
	getline(cin, inString);
	createObject(inString);

	setStatus(SUCCESS);
}

void IO::printOutput(TextObject* output)
{
	cout << output->getText();
	deleteObject();

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

TextObject* IO::retreiveObject()
{
	return textObject;
}

IO::~IO()
{
}