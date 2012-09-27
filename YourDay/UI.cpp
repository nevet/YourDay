#include "UI.h"

void UI::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

void UI::clearStatus()
{
	status = CLEAR;
}

UI::UI()
{
}

Signal UI::getStatus()
{
	return status;
}

void UI::startingScreenDisplay()
{

}

void UI::mainScreenDisplay()
{

}

UI::~UI()
{
}