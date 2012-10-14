/**
Your Day
UI.h

* This class is to display user interface
* Display starting screen to user at the beginning of the program
* Display main screen to interact with user
* author: Nhu Thao
*/
#include "UI.h"

//set the status of UI displaying proceess
void UI::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

UI::UI()
{
}

//get status of UI displaying process
Signal UI::getStatus()
{
	return status;
}

//clear status to default CLEAR signal
void UI::clearStatus()
{
	status = CLEAR;
}

//display the starting screen at the beginning of the program
void UI::startingScreenDisplay()
{
	setStatus(SUCCESS);
}

//display the main screen to interact with user
void UI::mainScreenDisplay()
{
	setStatus(SUCCESS);
}

UI::~UI()
{
}