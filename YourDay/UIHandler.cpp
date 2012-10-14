/**
Your Day
UIHandler.cpp

* This class is used to handle user interface displaying and input/output processes
* Control UI class to display user interface
* Store and pass the user input string passed from IO class
* Control IO class to display feedback message

* @author: Nhu Thao
*/

#include "UIHandler.h"

//Set output strings for successful feedback signals
const string UIHandler::CLEAR_SIGNAL_MESSAGE = "Command done";
const string UIHandler::ADD_SUCCESSFUL_MESSAGE = "Added successfully";
const string UIHandler::UPDATE_SUCCESSFUL_MESSAGE = "Updated successfully";
const string UIHandler::DELETE_SUCCESSFUL_MESSAGE = "Deleted successfully";

//set output strings for error feedback signals
const string UIHandler::DISPLAY_ERROR_MESSAGE = "Display error";
const string UIHandler::COMMAND_ERROR_MESSAGE = "Command error";
const string UIHandler::OPTION_ERROR_MESSAGE = "Option error";

//set the status of UIHandler process
void UIHandler::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

//inteprete success/error signal to a string message
string UIHandler::interpreteSignal(Signal outSignal)
{
	string outString;

	switch (outSignal)
	{
	case CLEAR:
		{
			outString = CLEAR_SIGNAL_MESSAGE;
			break;
		}
	case ADD_S:
		{
			outString = ADD_SUCCESSFUL_MESSAGE;
			break;
		}
	case UPDATE_S:
		{
			outString = UPDATE_SUCCESSFUL_MESSAGE;
			break;
		}
	case  DELETE_S:
		{
			outString = DELETE_SUCCESSFUL_MESSAGE;
			break;
		}
	case DISPLAY_E:
		{
			outString = DISPLAY_ERROR_MESSAGE;
			break;
		}
	case  COMMAND_E:
		{
			outString = COMMAND_ERROR_MESSAGE;
			break;
		}
	case  OPTION_E:
		{
			outString = OPTION_ERROR_MESSAGE;
			break;
		}
	default:
		{
			outString = "";
			break;
		}
	}

	return outString;
}

UIHandler::UIHandler()
{
	input = "";
}

//get the user input through IO
void UIHandler::getInput()
{
	io.getInput();
	input = io.getText();
	Signal ioStatus = io.getStatus();

	if (input == "")
	{
		setStatus(ERROR);
	}
	else
	{
		setStatus( ioStatus);
	}
}

//display feedback message to user through IO
void UIHandler::displayMessage(Signal outSignal)
{
	string outMessage = "";
	
	outMessage = interpreteSignal(outSignal);
	io.displayMessage(outMessage);

	if (outMessage == "")
	{
		setStatus(DISPLAY_E);
	}
	else
	{
		setStatus(SUCCESS);
	}

}

//display starting screen to user at the beginning through UI
void UIHandler::startingScreenDisplay()
{
	ui.startingScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setStatus(uiStatus);
}

//display main screen of the program to user through UI
void UIHandler::mainScreenDisplay()
{
	ui.mainScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setStatus(uiStatus);
}

//return the user input
string UIHandler::retrieveInput()
{
	return input;
}

//return the status of UIHandler process
Signal UIHandler::getStatus()
{
	return status;
}

//clear status to default CLEAR signal
void UIHandler::clearStatus()
{
	status = CLEAR;
}

UIHandler::~UIHandler()
{
}