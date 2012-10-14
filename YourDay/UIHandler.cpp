/**
* UIHandler is the main handler in the UI component and will be called in main(). UIHandler knows the IO and UI classes
* UIHandler controls the screen displaying and input/output process
* For screen displaying tasks: UIHandler has 2 public APIs startingScreenDisplay():void and mainScreenDisplay():void
* For input/output tasks: UIHandler has APIs getInput():void, retrieveInput():string and displayMessage():void
* UIHandler also has APIs setStatus() and clearStatus() to get and clear status signal
* After each process, UIHandler will set the success/error signal to inform the main()
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

void UIHandler::setUIStatus(Signal statusSignal)
{
	UIstatus = statusSignal;
}

void UIHandler::setStatus()
{
	status = UIstatus;
}

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

void UIHandler::getInput()
{
	input = io.getText();
	Signal ioStatus = io.getStatus();
	
	if (input == "")
	{
		setUIStatus(ERROR);
	}
	else
	{
		setUIStatus( ioStatus);
	}
}

void UIHandler::displayMessage(Signal outSignal)
{
	string outMessage = "";
	
	outMessage = interpreteSignal(outSignal);
	io.displayMessage(outMessage);

	if (outMessage == "")
	{
		setUIStatus(DISPLAY_E);
	}
	else
	{
		setUIStatus(SUCCESS);
	}

}

void UIHandler::startingScreenDisplay()
{
	ui.startingScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setUIStatus(uiStatus);
}

void UIHandler::mainScreenDisplay()
{
	ui.mainScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setUIStatus(uiStatus);
}

string UIHandler::retrieveInput()
{
	return input;
}

Signal UIHandler::getStatus()
{
	return UIstatus;
}

void UIHandler::clearStatus()
{
	UIstatus = CLEAR;
}

UIHandler::~UIHandler()
{
}