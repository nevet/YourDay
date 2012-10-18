/**
* UIHandler is the main handler in the UI component and will be called in main(). UIHandler knows the IO and UI classes
* UIHandler controls the screen displaying and input/output process
* For screen displaying tasks: UIHandler has 2 public APIs startingScreenDisplay():void and mainScreenDisplay():void
* For input/output tasks: UIHandler has APIs getInput():void, retrieveInput():string and displayMessage():void
* UIHandler also has APIs setStatus() and clearStatus() to get and clear status signal
* After each process, UIHandler will set the success/error signal to inform the main()
*/
#include <sstream>
#include <iostream>
#include "UIHandler.h"

//Set output strings for successful feedback signals
const string UIHandler::CLEAR_SIGNAL_MESSAGE = "Command done\n";
const string UIHandler::ADD_SUCCESSFUL_MESSAGE = "Added successfully\n";
const string UIHandler::UPDATE_SUCCESSFUL_MESSAGE = "Updated successfully\n";
const string UIHandler::DELETE_SUCCESSFUL_MESSAGE = "Deleted successfully\n";

//set output strings for error feedback signals
const string UIHandler::DISPLAY_ERROR_MESSAGE = "Display error\n";
const string UIHandler::COMMAND_ERROR_MESSAGE = "Command error\n";
const string UIHandler::OPTION_ERROR_MESSAGE = "Option error\n";

const string UIHandler::DELETE_FAILED_MESSAGE = "No such entry\n";

const string UIHandler::DELETE_ASK_MESSAGE = "Which one do you want to delete?\n";



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
	case DELETE_F:
		{
			outString = DELETE_FAILED_MESSAGE;
			break;
		}
	case DELETE_A:
		{
			outString = DELETE_ASK_MESSAGE;
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
		setUIStatus(ERR);
	}
	else
	{
		setUIStatus( ioStatus);
	}
}

void UIHandler::displayMessage(Signal outSignal)
{
	string outMessage = "";
	
	ui.setNormal();
	ui.didUKnowBox();
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
	ui.drawBox();
	
}

void UIHandler::displayMessage(vector<string>* result)
{
	int size = result ->size();

	ui.setNormal();
	ui.didUKnowBox();
	for (int i=0; i< size; i++)
	{
		string row;
		ostringstream outMessage;

		row = result->at(i) ;
		outMessage << i+1 << ". " << row <<endl;
		displayMessage(outMessage.str());
	}

	ui.drawBox();

}

void UIHandler::displayMessage(string result)
{
	io.displayMessage(result);
}

void UIHandler::startingScreenDisplay()
{
	ui.setScreenSize();
	ui.startingScreenDisplay();
	Signal uiStatus = ui.getStatus();

	setUIStatus(uiStatus);
}

void UIHandler::mainScreenDisplay(vector<string>* entryList)
{
	ui.mainScreenDisplay(entryList);
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