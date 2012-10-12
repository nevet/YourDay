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