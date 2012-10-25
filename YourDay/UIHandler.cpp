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

//set output strings for error feedback signals on user input
const string UIHandler::COMMAND_ERROR_MESSAGE = "Wrong command\n";
const string UIHandler::LENGTH_EXCEED_ERROR_MESSAGE = "Command length exceeded the valid range\n";
const string UIHandler::LENGTH_ZERO_ERROR_MESSAGE = "Cannot enter command with empty detail\n";
const string UIHandler::INDEX_ERROR_MESSAGE = "Please enter an index\n";
const string UIHandler::INVALID_DATE_ERROR_MESSAGE = "Invalid date\n";
const string UIHandler::INVALID_TIME_ERROR_MESSAGE = "Invalid time\n";
const string UIHandler::UNDO_ERROR_MESSAGE = "Nothing to undo\n";

//set output strings for error feedback signals on displaying UI
const string UIHandler::DISPLAY_ERROR_MESSAGE = "Display error\n";

//set output strings for error feedback signals on executing commands
const string UIHandler::NULL_EXECUTOR_ERROR_MESSAGE = "Executor pointer is NULL\n";
const string UIHandler::ADD_FAILED_MESSAGE = "Add failed\n";
const string UIHandler::DELETE_FAILED_MESSAGE = "Delete failed\n";
const string UIHandler::SEARCH_FAILED_MESSAGE = "Cannot find the key word\n";
const string UIHandler::UPDATE_FAILED_MESSAGE = "Update failed\n";

void UIHandler::setUIStatus(Signal statusSignal)
{
	UIstatus = statusSignal;
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
	case  UPDATE_S:
		{
			outString = UPDATE_SUCCESSFUL_MESSAGE;
			break;
		}
	case  COMMAND_E:
		{
			outString = COMMAND_ERROR_MESSAGE;
			break;
		}
	case  LENGTH_X_E:
		{
			outString = LENGTH_EXCEED_ERROR_MESSAGE;
			break;
		}
	case  LENGTH_Z_E:
		{
			outString = LENGTH_ZERO_ERROR_MESSAGE;
			break;
		}
	case  INDEX_E:
		{
			outString = INDEX_ERROR_MESSAGE;
			break;
		}
	case  DATE_E:
		{
			outString = INVALID_DATE_ERROR_MESSAGE;
			break;
		}
	case  TIME_E:
		{
			outString = INVALID_TIME_ERROR_MESSAGE;
			break;
		}
	case  DISPLAY_E:
		{
			outString = DISPLAY_ERROR_MESSAGE;
			break;
		}
	case  UNDO_E:
		{
			outString = UNDO_ERROR_MESSAGE;
			break;
		}
	case  EXENULL_E:
		{
			outString = NULL_EXECUTOR_ERROR_MESSAGE;
			break;
		}
	case  ADD_F:
		{
			outString = ADD_FAILED_MESSAGE;
			break;
		}
	case  DELETE_F:
		{
			outString = DELETE_FAILED_MESSAGE;
			break;
		}
	case  SEARCH_F:
		{
			outString = SEARCH_FAILED_MESSAGE;
			break;
		}
	case  UPDATE_F:
		{
			outString = UPDATE_FAILED_MESSAGE;
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

UIHandler::UIHandler(vector<string>* calendarEntryList, vector<string>* generalEntryList)
{
	input = "";
	startingScreenDisplay();
	mainScreenDisplay(calendarEntryList,generalEntryList);
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
	string decodedRow;
	ui.setNormal();
	ui.didUKnowBox();
	for (int i=0; i< size; i++)
	{
		string row;
		ostringstream outMessage;

		row = result->at(i) ;
		ui.coloredDisplayFormattedString(i+1,row);
		
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

void UIHandler::mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList)
{
	ui.mainScreenDisplay(calendarEntryList,generalEntryList);
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