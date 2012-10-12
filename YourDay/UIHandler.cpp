#include "UIHandler.h"

const string UIHandler::ADD_SUCCESSFUL_MESSAGE = "Added successfully";
const string UIHandler::UPDATE_SUCCESSFUL_MESSAGE = "Updated successfully";
const string UIHandler::DELETE_SUCCESSFUL_MESSAGE = "Deleted successfully";

const string UIHandler::DISPLAY_ERROR_MESSAGE = "Display error";
const string UIHandler::COMMAND_ERROR_MESSAGE = "Command error";
const string UIHandler::OPTION_ERROR_MESSAGE = "Option error";

void UIHandler::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

string UIHandler::interpreteSignal(Signal outSignal)
{
	string outString;

	switch (outSignal)
	{
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

void UIHandler::displayMessage(Signal outSignal)
{
	string outMessage = "";
	
	outMessage = interpreteSignal(outSignal);
	io.printOutput(outMessage);

	if (outMessage == "")
	{
		setStatus(DISPLAY_E);
	}
	else
	{
		setStatus(SUCCESS);
	}

}

void UIHandler::startingScreenDisplay()
{
	ui.startingScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setStatus(uiStatus);
}

void UIHandler::mainScreenDisplay()
{
	ui.mainScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setStatus(uiStatus);
}

string UIHandler::retrieveInput()
{
	return input;
}

Signal UIHandler::getStatus()
{
	return status;
}

void UIHandler::clearStatus()
{
	status = CLEAR;
}

UIHandler::~UIHandler()
{
}