/**
* UI class is a part of UI part and will be called in the UIHandler
* UI class is used to display User Interface to the screen
* UI class has 2 main APIs to do this functionality:
* startingScreenDisplay():void to diisplay starting screen to user at the beginning of the program
* mainScreenDisplay():void to display main screen to interact with user
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
	status = CLEAR;
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