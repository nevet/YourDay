/**
* UI class is used to display User Interface. It is known by UIHandler
* UI has APIs:
*	startingScreenDisplay(): void to display the starting screen at the beginning of the program
*	mainScreenDisplay(): void to display the main screen to interact with the user
*/

#include "UI.h"

void UI::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

UI::UI()
{
}

Signal UI::getStatus()
{
	return status;
}

void UI::clearStatus()
{
	UIstatus = CLEAR;
}

void UI::startingScreenDisplay()
{
	setStatus(SUCCESS);
}

void UI::mainScreenDisplay()
{
	setStatus(SUCCESS);
}

UI::~UI()
{
}